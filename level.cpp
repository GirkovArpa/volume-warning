#include <iostream>
#include <Windows.h>
#include <vector>
#include <cmath>
#include <mmeapi.h>

#include "Unit1.h"
#include "Unit2.h"

using namespace std;

short int waveIn[4410];

float GetBufferData(short* buffer);
int scaleBufferData(float dB);

int level() {
    const int NUMPTS = 4410;
    int sampleRate = 44100;

    HWAVEIN hWaveIn;
    MMRESULT result;

    WAVEFORMATEX pFormat;
    pFormat.wFormatTag = WAVE_FORMAT_PCM;
    pFormat.nChannels = 1;
    pFormat.nSamplesPerSec = sampleRate;
    pFormat.nAvgBytesPerSec = sampleRate * 2;
    pFormat.nBlockAlign = 2;
    pFormat.wBitsPerSample = 16;
    pFormat.cbSize = 0;

    result = waveInOpen(&hWaveIn, WAVE_MAPPER, &pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);
    if (result == MMSYSERR_ALLOCATED) {
        Application->MessageBox(L"In function waveInOpen: Specified resource is already allocated.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }
    if (result == MMSYSERR_BADDEVICEID) {
        Application->MessageBox(L"In function waveInOpen: Specified device identifier is out of range.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }
    if (result == MMSYSERR_NODRIVER) {
        Application->MessageBox(L"In function waveInOpen: No device driver is present.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }
    if (result == MMSYSERR_NOMEM) {
        Application->MessageBox(L"In function waveInOpen: Unable to allocate or lock memory.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }
    if (result == WAVERR_BADFORMAT) {
        Application->MessageBox(L"In function waveInOpen: Attempted to open with an unsupported waveform-audio format.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }

    WAVEHDR WaveInHdr;

    WaveInHdr.lpData = (LPSTR)waveIn;
    WaveInHdr.dwBufferLength = NUMPTS * 2;
    WaveInHdr.dwBytesRecorded = 0;
    WaveInHdr.dwUser = 0L;
    WaveInHdr.dwFlags = 0L;
    WaveInHdr.dwLoops = 0L;
    waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));

    result = waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
    if (result == MMSYSERR_INVALHANDLE) {
        Application->MessageBox(L"In function waveInAddBuffer: Specified device handle is invalid.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }
    if (result == MMSYSERR_NODRIVER) {
        Application->MessageBox(L"In function waveInAddBuffer: No device driver is present.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }
    if (result == MMSYSERR_NOMEM) {
        Application->MessageBox(L"In function waveInAddBuffer: Unable to allocate or lock memory.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }
    if (result == WAVERR_UNPREPARED) {
        Application->MessageBox(L"In function waveInAddBuffer: The buffer pointed to by the pwh parameter hasn't been prepared.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }

    result = waveInStart(hWaveIn);
    if (result == MMSYSERR_INVALHANDLE) {
        Application->MessageBox(L"In function waveInStart: Specified device handle is invalid.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }
    if (result == MMSYSERR_NODRIVER) {
        Application->MessageBox(L"In function waveInStart: No device driver is present.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }
    if (result == MMSYSERR_NOMEM) {
        Application->MessageBox(L"In function waveInStart: Unable to allocate or lock memory.", L"Error", MB_OK | MB_ICONERROR);
        MyThread->Suspend();
        Application->Terminate();
    }

    Sleep(100);
    while ((WaveInHdr.dwFlags & WHDR_DONE) == 0)
        Sleep(10)

            waveInClose(hWaveIn);

    return scaleBufferData(GetBufferData(waveIn));
}

float GetBufferData(short* buffer) {
    float dB = 0;

    long long sum = 0;

    for (int i = 0; i < 4410; i++) {
        sum += abs(buffer[i]);
    }

    float avg = sum / 4410;

    short max = 0;
    for (int i = 0; i < 4410; i++) {
        if (abs(buffer[i]) > max) {
            max = abs(buffer[i]);
        }
    }
    avg = (float)max;

    dB = (avg > 0) ? 20 * log10(avg / 32768) : -1000000;

    return dB;
}

int scaleBufferData(float dB) {
    double REFERENCE = 32768;
    double MIN_DB = 20 * log10(1.0 / REFERENCE);
    double MAX_DB = 0;

    int nPos = (int)(((double)dB - MIN_DB) * 100 / (MAX_DB - MIN_DB));

    if (nPos < 0)
        return 0;

    return nPos;
}