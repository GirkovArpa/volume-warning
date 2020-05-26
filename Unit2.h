//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.MPlayer.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm {
    __published :  // IDE-managed Components
                   TTrackBar *TrackBar1;
	TLabel *Label1;
	TImage *Image1;
	TMediaPlayer *MediaPlayer1;

private:  // User declarations
public:   // User declarations
    __fastcall TForm2(TComponent *Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif

