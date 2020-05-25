//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm {
    __published :  // IDE-managed Components
                   TTrackBar *TrackBar1;
    TProgressBar *ProgressBar1;

private:  // User declarations
public:   // User declarations
    __fastcall TForm2(TComponent *Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif

