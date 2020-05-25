#include <iostream>
#include <Windows.h>
#include <vector>
#include <cmath>
using namespace std;

short int waveIn[4410];

float GetBufferData(short* buffer);
int scaleBufferData(float dB);

int level() {
    const int NUMPTS = 4410;  // 3 seconds
    int sampleRate = 44100;
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

    result = waveInOpen(&hWaveIn, WAVE_MAPPER, &pFormat,
                        0L, 0L, WAVE_FORMAT_DIRECT);

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

    // Commence sampling input
    result = waveInStart(hWaveIn);

    //cout << "recording..." << endl;

    Sleep(1 * 100.0);
    // Wait until finished recording

    waveInClose(hWaveIn);

    return scaleBufferData(GetBufferData(waveIn));

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

    dB = (avg > 0) ? 20 * log10(avg / 32768) : -1000000;

    return dB;
}

int scaleBufferData(float dB) {
    const static double REFERENCE = 32768;
    const static double MIN_DB = 20 * log10(1.0 / REFERENCE);
    const static double MAX_DB = 0;

    const int nPos = (int)(((double)dB - MIN_DB) * 100 / (MAX_DB - MIN_DB));

    return nPos;
}