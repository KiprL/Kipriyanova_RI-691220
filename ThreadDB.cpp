//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ThreadDB.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall WriteToDB::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall WriteToDB::WriteToDB(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	DataReady = new TEvent(NULL, true, false, "", false); // �������, ���������������, ��� ������ ������ � ������
	DataCopied = new TEvent(NULL, true, false, "", false); // �������, ���������������, ��� ������ �����������
}
//---------------------------------------------------------------------------
void __fastcall WriteToDB::Execute()
{
	Synchronize(treeClear);
	SQL MyDB; // ������������� ������� ��� ������ � ��
	DataCopied->ResetEvent(); // ����� �����, ���� ������ ��������
    int selectedIndex = Form1->RadioGroup1->ItemIndex;
	selectedExept = Form1->RadioGroup1->Items->Strings[selectedIndex].c_str(); // �������� �������� ���������� ����������
	//path = Form1->Edit1->Text.c_str(); // �������� ����/����
    i = 0;

	while(!Terminated) // �������� ���� ���������� ������, ���������� �� ��������������� ����������
	{
		if(DataReady->WaitFor(INFINITE) == wrSignaled) // ����, ���� ���� DataReady �� ����� ������
		{
			DataReady->ResetEvent(); // ���������� ���� ���������� ������
			i++;                                   //������� ������ ������
            path = Form1->Edit1->Text.c_str(); // �������� ����/����
//            numOfCluster = Form1->foundCl;
            int d = 0;
			MyDB.writeToDB(path, Form1->foundCl, selectedExept);
            int f = 0;
            Synchronize(addRow); // ��������� ������ � �������

			DataCopied->SetEvent(); // ��������� ����, ��������������� � ���, ��� ������ �����������

    	}
	}
}
//---------------------------------------------------------------------------
void __fastcall WriteToDB::treeClear()
{
	Form1->VirtualStringTree1->Clear(); // ������� VirtualStringTree
}
//---------------------------------------------------------------------------
void __fastcall WriteToDB::addRow()
{
	PVirtualNode myNode = Form1->VirtualStringTree1->AddChild(Form1->VirtualStringTree1->RootNode); // ��������� �������� ���� � ��������� �������� ������ �����
	TreeNode* myData = (TreeNode*)Form1->VirtualStringTree1->GetNodeData(myNode); // �������� ������ � ������ ����, �������� ��� � ������� ������������ ���������� TreeNode
	myData->index = i;
	myData->path = Form1->Edit1->Text;
	myData->numOfCluster = Form1->foundCl;
    int selectedIndex = Form1->RadioGroup1->ItemIndex;
	myData->selectedExept = Form1->RadioGroup1->Items->Strings[selectedIndex].c_str();
}
//---------------------------------------------------------------------------
