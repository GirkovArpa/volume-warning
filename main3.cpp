#include <windows.h>
#include <mmdeviceapi.h>
#include "endpointvolume.h"
#include <iostream>

int main() {
    CoInitialize(NULL);
    IMMDeviceEnumerator *pEnum = NULL;
    IMMDevice *pDevice = NULL;
    IAudioMeterInformation *pMeter = NULL;
    float peak;

    HRESULT hr;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
                          NULL,
                          CLSCTX_INPROC_SERVER,
                          __uuidof(IMMDeviceEnumerator),
                          (void **)&pEnum);

    hr = pEnum->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

    pDevice->Activate(__uuidof(IAudioMeterInformation),
                      CLSCTX_ALL,
                      NULL,
                      (void **)&pMeter);

    pMeter->GetPeakValue(&peak);  // I need this value
}