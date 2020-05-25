//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "level.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall MyThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall MyThread::MyThread(bool CreateSuspended) : TThread(CreateSuspended) {
}
//---------------------------------------------------------------------------
void __fastcall MyThread::Execute() {
    NameThreadForDebugging(System::String(L"VolumeWarningThread"));
    //---- Place thread code here ----
    for (int i = 0; i < 100; i++) {
        Synchronize([&]() {
            Form2->ProgressBar1->Position = level();
        });
    }
}
//---------------------------------------------------------------------------




