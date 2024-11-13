//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <Dialogs.hpp>

#include "Forma.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "VirtualTrees.AncestorVCL"
#pragma link "VirtualTrees.BaseAncestorVCL"
#pragma link "VirtualTrees.BaseTree"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    VirtualStringTree1->NodeDataSize=sizeof(TreeNode); // ��������� ������ �� ���� ������
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Edit1->Enabled = False;
    TOpenDialog *OpenDialog = new TOpenDialog(this); // ����� ���� ���������� ��� ������ ������ �����
    OpenDialog->Filter = "Image Files (*.img;*.vmdk;*.dd;*.vhd;*.vhdx)|*.img;*.vmdk;*.dd;*.vhd;*.vhdx|All Files (*.*)|*.*"; // ������ ��� ������
    OpenDialog->Title = "�������� ���� ������";

    if (OpenDialog->Execute())
    {
        String selectedFile = OpenDialog->FileName;
        //ShowMessage("��������� ����: " + selectedFile);
        Edit1->Clear();
        Edit1->Text = selectedFile.c_str();
        path = selectedFile.c_str();
    }

    delete OpenDialog; // ����������� ������
}

//---------------------------------------------------------------------------






void __fastcall TForm1::Button2Click(TObject *Sender)
{
//    if (Edit1->Text.Length() == 1)
//    {
//        UnicodeString path_uni = u"\\\\?\\" + Edit1->Text + u":";
//        path = path_uni.c_str();
//        int t = 0;
//    }
    SearchingClusters* thread1 = new SearchingClusters(false); // ������ ������� ������
//    Button2->Enabled = false;
//	Button2->Caption = "���� �����...";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
    Edit1->Enabled = True; // ������ ��������� ��� ������ ���� ����� ����� ����������� ����
    Edit1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
	// ��������� ������� Backspace
    if (Key == VK_BACK)
    {
        return;
    }

    // ��������, ��� ������ � ��������� ����� ����������� ��������
    if (!(Key >= 'A' && Key <= 'Z'))
    {
        Key = 0;
        return;
    }

    // ��������, ��� � ���� ��� ������ ��������, ���� ��� ������ ������ - ���������� �����
    if (Edit1->Text.Length() >= 1)
    {
        Key = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if (!Node) return; // ��������, ��� ���� ����������

	TreeNode* myData = (TreeNode*)Sender->GetNodeData(Node); // ��������� ������, ��������� � �����, � �������� �� � ���� TreeNode

     // ����������� ������������� ������ � ����������� �� �������
	switch (Column)
	{
 case 0: CellText = myData->index; break;
 case 1: CellText = myData->path; break;
 case 2: CellText = myData->selectedExept; break;
 case 3: CellText = myData->numOfCluster; break;
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

