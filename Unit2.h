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
    TLabel *Label2;
    TLabel *labelFloor;
    TLabel *labelCeiling;
    TTrackBar *sliderFloor;
    TTrackBar *sliderCeiling;
    void __fastcall TrackBar1Change(TObject *Sender);
    void __fastcall sliderFloorChange(TObject *Sender);
    void __fastcall sliderCeilingChange(TObject *Sender);

private:  // User declarations
public:   // User declarations
    __fastcall TForm2(TComponent *Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
extern int myFloor;
extern int myCeiling;
extern MyThread* myThread;
//---------------------------------------------------------------------------
#endif
