#include <iostream>
#include <Windows.h>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

short int waveIn[4410];

float GetBufferData(short* buffer);
int scaleBufferData(float dB);

int level() {
    while (1) {
    const int NUMPTS = 4410;  // 3 seconds
    int sampleRate = 4410;
    // 'short int' is a 16-bit type; I request 16-bit samples below
    // for 8-bit capture, you'd use 'unsigned char' or 'BYTE' 8-bit     types

    HWAVEIN hWaveIn;
    MMRESULT result;

    WAVEFORMATEX pFormat;
    pFormat.wFormatTag = WAVE_FORMAT_PCM;      // simple, uncompressed format
    pFormat.nChannels = 1;                     //  1=mono, 2=stereo
    pFormat.nSamplesPerSec = sampleRate;       // 44100
    pFormat.nAvgBytesPerSec = sampleRate * 2;  // = nSamplesPerSec * n.Channels *    wBitsPerSample/8
    pFormat.nBlockAlign = 2;                   // = n.Channels * wBitsPerSample/8
    pFormat.wBitsPerSample = 16;               //  16 for high quality, 8 for telephone-grade
    pFormat.cbSize = 0;

    // Specify recording parameters

    result = waveInOpen(&hWaveIn, WAVE_MAPPER, &pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);
    if (result == MMSYSERR_ALLOCATED) {
        std::cout << "Specified resource is already allocated." << std::endl;
    }
    if (result == MMSYSERR_BADDEVICEID) {
        std::cout << "Specified device identifier is out of range." << std::endl;
    }
    if (result == MMSYSERR_NODRIVER) {
        std::cout << "No device driver is present." << std::endl;
    }
    if (result == MMSYSERR_NOMEM) {
        std::cout << "Unable to allocate or lock memory." << std::endl;
    }
    if (result == WAVERR_BADFORMAT) {
        std::cout << "Attempted to open with an unsupported waveform-audio format." << std::endl;
    }

    WAVEHDR WaveInHdr;
    // Set up and prepare header for input
    WaveInHdr.lpData = (LPSTR)waveIn;
    WaveInHdr.dwBufferLength = NUMPTS * 2;
    WaveInHdr.dwBytesRecorded = 0;
    WaveInHdr.dwUser = 0L;
    WaveInHdr.dwFlags = 0L;
    WaveInHdr.dwLoops = 0L;
    waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));

    // Insert a wave input buffer
    result = waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
    if (result == MMSYSERR_INVALHANDLE) {
        std::cout << "Specified device handle is invalid." << std::endl;
    }
    if (result == MMSYSERR_NODRIVER) {
        std::cout << "No device driver is present." << std::endl;
    }
    if (result == MMSYSERR_NOMEM) {
        std::cout << "Unable to allocate or lock memory." << std::endl;
    }
    if (result == WAVERR_UNPREPARED) {
        std::cout << "The buffer pointed to by the pwh parameter hasn't been prepared." << std::endl;
    }

    // Commence sampling input
    result = waveInStart(hWaveIn);
    if (result == MMSYSERR_INVALHANDLE) {
        std::cout << "Specified device handle is invalid." << std::endl;
    }
    if (result == MMSYSERR_NODRIVER) {
        std::cout << "No device driver is present." << std::endl;
    }
    if (result == MMSYSERR_NOMEM) {
        std::cout << "Unable to allocate or lock memory." << std::endl;
    }

    //cout << "recording..." << endl;
 
    // do something
    auto t_start = std::chrono::high_resolution_clock::now();
    Sleep(100);
    while ((WaveInHdr.dwFlags & WHDR_DONE) == 0) {
        //std::cout << "Sleeping again ... " << std::endl;
        Sleep(10);
    }
    auto t_end = std::chrono::high_resolution_clock::now();

    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << elapsed_time_ms << std::endl;
    // Wait until finished recording

    waveInClose(hWaveIn);

    std::cout << scaleBufferData(GetBufferData(waveIn)) << std::endl;
    }

    /*
    std::cout << "dB: " << GetBufferData(waveIn) << std::endl;

    short max = 0;
    short min = 0;
    for (int i = 0; i < 44100 * 1; i++) {
        short wave = waveIn[i];
        if (wave > max)
            max = wave;
        if (wave < min)
            min = wave;
    }

    return max;
    */
}

float GetBufferData(short* buffer) {
    float dB = 0;

    long long sum = 0;

    for (int i = 0; i < 4410; i++) {
        sum += abs(buffer[i]);
    }

    float avg = sum / 4410;

    //
    short max = 0;
    for (int i = 0; i < 4410; i++) {
        if (abs(buffer[i]) > max) {
            max = abs(buffer[i]);
        }
    }
    avg = (float)max;
    //

    dB = (avg > 0) ? 20 * log10(avg / 32768) : -1000000;

    /*
    short max = 0;
    for (int i = 0; i < 4410; i++) {
        if (buffer[i] > max)
            max = buffer[i];
    }
    return ((float)max * 100) / 32768;
    */

    return dB;
}

int scaleBufferData(float dB) {
    const static double REFERENCE = 32768;
    const static double MIN_DB = 20 * log10(1.0 / REFERENCE);
    const static double MAX_DB = 0;

    int nPos = (int)(((double)dB - MIN_DB) * 100 / (MAX_DB - MIN_DB));

    if (nPos < 0)
        return 0;

    return nPos;
}