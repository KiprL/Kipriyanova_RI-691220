//---------------------------------------------------------------------------

#ifndef FormaH
#define FormaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.AncestorVCL.hpp"
#include "VirtualTrees.BaseAncestorVCL.hpp"
#include "VirtualTrees.BaseTree.hpp"
#include "VirtualTrees.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "ThreadSearching.h"
//---------------------------------------------------------------------------

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TVirtualStringTree *VirtualStringTree1;
	TEdit *Edit1;
	TLabel *Label1;
	TButton *Button2;
	TRadioGroup *RadioGroup1;
	TButton *Button3;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    const wchar_t* path;
    ULONGLONG foundCl;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
typedef struct {
ULONGLONG index;
UnicodeString path;
ULONGLONG numOfCluster;
UnicodeString selectedExept;
} TreeNode;
#endif
