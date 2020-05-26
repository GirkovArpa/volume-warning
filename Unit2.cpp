//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2* Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner) {
    MediaPlayer1->FileName = "beep.wav";
	MediaPlayer1->Open();
	MyThread* myThread = new MyThread(false);
}
//---------------------------------------------------------------------------




void __fastcall TForm2::TrackBar1Change(TObject *Sender)
{
	Form2->Label2->Caption = IntToStr(100 - StrToInt(Form2->TrackBar1->Position));
}
//---------------------------------------------------------------------------

