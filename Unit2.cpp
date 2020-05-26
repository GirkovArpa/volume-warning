//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2* Form2;
MyThread* myThread;
int myFloor;
int myCeiling;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner) {
    if (!FileExists("beep.wav")) {
        Application->MessageBox(L"Audio file \"beep.wave\" not found.", L"Error", MB_OK | MB_ICONERROR);
        Application->Terminate();
    }
    MediaPlayer1->FileName = "beep.wav";
    MediaPlayer1->Open();
    myThread = new MyThread(false);
    myFloor = 0;
    myCeiling = 100;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::TrackBar1Change(TObject* Sender) {
    Form2->Label2->Caption = IntToStr(100 - Form2->TrackBar1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::sliderFloorChange(TObject* Sender) {
    Form2->labelFloor->Caption = IntToStr(100 - Form2->sliderFloor->Position);
    if (sliderFloor->Position < sliderCeiling->Position) {
        sliderCeiling->Position = sliderFloor->Position;
    }
    myFloor = 100 - sliderFloor->Position;
    myCeiling = 100 - sliderCeiling->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::sliderCeilingChange(TObject* Sender) {
    Form2->labelCeiling->Caption = IntToStr(100 - Form2->sliderCeiling->Position);
    if (sliderCeiling->Position > sliderFloor->Position) {
        sliderFloor->Position = sliderCeiling->Position;
    }
    myFloor = 100 - sliderFloor->Position;
    myCeiling = 100 - sliderCeiling->Position;
}
//---------------------------------------------------------------------------
