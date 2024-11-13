//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ThreadSearching.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SearchingClusters::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall SearchingClusters::SearchingClusters(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall SearchingClusters::Execute()
{
	Form1->Button2->Enabled = false;
	Form1->Button2->Caption = "Идет поиск...";
    if (Form1->path == NULL)
    {
        UnicodeString path_uni = u"\\\\?\\" + Form1->Edit1->Text + u":";
        Form1->path = path_uni.c_str();
        int t = 0;
    }
    const wchar_t* i2 = Form1->path;

    const wchar_t* ii = Form1->path;
    UnicodeString i3 = Form1->Edit1->Text;
    MyFabric WHO(Form1->path);
    BaseFileSystem* MyFS = WHO.getFileSystem(WHO.decideFileSystem());
    iterator iter(MyFS);
	decorator Dec(iter);
    WriteToDB* threadDB = new WriteToDB(false);
    for (Dec.First(); !Dec.IsDone(); Dec.Next()) {
    	int a =0;
        Form1->foundCl = Dec.MyIter.currentCluster;
        int b =0;
		threadDB->DataReady->SetEvent();
        int c = 0;
		while(threadDB->DataCopied->WaitFor(INFINITE) != wrSignaled){};
		threadDB->DataCopied->ResetEvent();
		//std::cout << Dec.MyIter.currentCluster << std::endl;
	}
    ShowMessage("Поиск выполнен!");
    Form1->Button2->Caption = "Поиск";
	Form1->Button2->Enabled = true;
    Form1->Edit1->Clear();
    Form1->Edit1->Text = "Пример: С";
    Form1->RadioGroup1->ItemIndex = -1;
    Form1->path = NULL;
}
//---------------------------------------------------------------------------
