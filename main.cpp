#include <windows.h>
#include <mmsystem.h>
#include <iostream>

// EDITED s.b
#include <stdio.h>

using namespace std;

// CHANGED s.b int DeviceManager::getAudioInputVolumn( const std::string &deviceName)
int getAudioInputVolumn() {
    MMRESULT rc;
    HMIXER hMixer;
    MIXERLINE mxl;
    MIXERLINECONTROLS mxlc;
    MIXERCONTROL mxc;

    for (int deviceID = 0; true; deviceID++) {
        rc = mixerOpen(&hMixer, deviceID, 0, 0, MIXER_OBJECTF_MIXER);

        if (MMSYSERR_NOERROR != rc) {
            break;
        }

        ZeroMemory(&mxl, sizeof(MIXERLINE));

        mxl.cbStruct = sizeof(MIXERLINE);
        mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;

        rc = mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE);
        if (rc != MMSYSERR_NOERROR) {
            continue;
        }

        DWORD dwConnections = mxl.cConnections;
        DWORD dwLineID = -1;
        // EDITED s.b  for( DWORD i=0 ; i<dwconnections;>  {
        for (DWORD i = 0; i < dwConnections;) {
            mxl.dwSource = i;
            rc = mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_SOURCE);

            if (MMSYSERR_NOERROR == rc) {
                if (mxl.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE) {
                    dwLineID = mxl.dwLineID;
                    break;
                }
            }
        }
        if (dwLineID == -1) {
            continue;
        }

        ZeroMemory(&mxc, sizeof(MIXERCONTROL));

        mxc.cbStruct = sizeof(mxc);

        ZeroMemory(&mxlc, sizeof(MIXERLINECONTROLS));

        mxlc.cbStruct = sizeof(mxlc);
        mxlc.dwLineID = dwLineID;
        mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
        mxlc.cControls = 1;
        mxlc.pamxctrl = &mxc;
        mxlc.cbmxctrl = sizeof(mxc);

        rc = mixerGetLineControls((HMIXEROBJ)hMixer, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);

        if (MMSYSERR_NOERROR == rc) {
            MIXERCONTROLDETAILS mxcd;
            MIXERCONTROLDETAILS_SIGNED volStruct;

            ZeroMemory(&mxcd, sizeof(mxcd));

            mxcd.cbStruct = sizeof(mxcd);
            mxcd.dwControlID = mxc.dwControlID;
            mxcd.paDetails = &volStruct;
            mxcd.cbDetails = sizeof(volStruct);
            mxcd.cChannels = 1;

            rc = mixerGetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_GETCONTROLDETAILSF_VALUE);

            if (MMSYSERR_NOERROR == rc) {
                long step = (mxc.Bounds.lMaximum - mxc.Bounds.lMinimum) / 100;

                int index = (volStruct.lValue - mxc.Bounds.lMinimum) / step;
                //          printf("volume:%X", volStruct.lValue);
                return index;
            }
        }
    }

    return -1;
}

int main() {
    printf("Mic volume: %d\n", getAudioInputVolumn());
}