#include <windows.h>
#include <mmdeviceapi.h>
#include "endpointvolume.h"
#include <iostream>
//#include <mmeapi.h>

int main() {
    float audiolevel = 0.0;
    IMMDeviceEnumerator* pEnumerator = NULL;
    IMMDevice* pDevice = NULL;
    IAudioMeterInformation* pMeterInfo = NULL;
    CoInitialize(NULL);
    CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    pDevice->Activate(__uuidof(IAudioMeterInformation), CLSCTX_ALL, NULL, (void**)&pMeterInfo);
    pMeterInfo->GetPeakValue(&audiolevel);
    while (1) {
        std::cout << audiolevel << std::endl;
        pMeterInfo->GetPeakValue(&audiolevel);
    }
}