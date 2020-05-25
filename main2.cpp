#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

#pragma comment(lib, "winmm.lib")

short int waveIn[44100 * 1];

void PlayRecord();

void StartRecord() {
    const int NUMPTS = 44100 * 1;  // 3 seconds
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

    cout << "recording..." << endl;

    Sleep(1 * 1000);
    // Wait until finished recording

    waveInClose(hWaveIn);

    PlayRecord();
}

void PlayRecord() {
    const int NUMPTS = 44100 * 1;  // 3 seconds
    int sampleRate = 44100;
    // 'short int' is a 16-bit type; I request 16-bit samples below
    // for 8-bit capture, you'd    use 'unsigned char' or 'BYTE' 8-bit types

    HWAVEIN hWaveIn;

    WAVEFORMATEX pFormat;
    pFormat.wFormatTag = WAVE_FORMAT_PCM;      // simple, uncompressed format
    pFormat.nChannels = 1;                     //  1=mono, 2=stereo
    pFormat.nSamplesPerSec = sampleRate;       // 44100
    pFormat.nAvgBytesPerSec = sampleRate * 2;  // = nSamplesPerSec * n.Channels * wBitsPerSample/8
    pFormat.nBlockAlign = 2;                   // = n.Channels * wBitsPerSample/8
    pFormat.wBitsPerSample = 16;               //  16 for high quality, 8 for telephone-grade
    pFormat.cbSize = 0;

    // Specify recording parameters

    waveInOpen(&hWaveIn, WAVE_MAPPER, &pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);

    WAVEHDR WaveInHdr;
    // Set up and prepare header for input

    short max = 0;
    short min = 0;
    for (int i = 0; i < 44100 * 1; i++) {
        short wave = waveIn[i];
        if (wave > max)
            max = wave;
        if (wave < min)
            min = wave;
        // std::cout << waveIn[i] << std::endl;
    }

    std::cout << "MAX: " << max << std::endl;
    std::cout << "MIN: " << min << std::endl;

    WaveInHdr.lpData = (LPSTR)waveIn;
    WaveInHdr.dwBufferLength = NUMPTS * 2;
    WaveInHdr.dwBytesRecorded = 0;
    WaveInHdr.dwUser = 0L;
    WaveInHdr.dwFlags = 0L;
    WaveInHdr.dwLoops = 0L;
    waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));

    HWAVEOUT hWaveOut;
    cout << "playing..." << endl;
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &pFormat, 0, 0, WAVE_FORMAT_DIRECT);
    waveOutWrite(hWaveOut, &WaveInHdr, sizeof(WaveInHdr));  // Playing the data
    Sleep(1 * 1000);                                        //Sleep for as long as there was recorded

    waveInClose(hWaveIn);
    waveOutClose(hWaveOut);
}

int main() {
    StartRecord();
    return 0;
}