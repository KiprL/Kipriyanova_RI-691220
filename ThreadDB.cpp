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
	DataReady = new TEvent(NULL, true, false, "", false); // Событие, сигнализирующее, что данные готовы к записи
	DataCopied = new TEvent(NULL, true, false, "", false); // Событие, сигнализирующее, что данные скопированы
}
//---------------------------------------------------------------------------
void __fastcall WriteToDB::Execute()
{
	Synchronize(treeClear);
	SQL MyDB; // Инициализация объекта для работы с БД
	DataCopied->ResetEvent(); // Сброс флага, если поднят случайно
    int selectedIndex = Form1->RadioGroup1->ItemIndex;
	selectedExept = Form1->RadioGroup1->Items->Strings[selectedIndex].c_str(); // Получаем значение выбранного расширения
	//path = Form1->Edit1->Text.c_str(); // Получаем путь/диск
    i = 0;

	while(!Terminated) // Основной цикл выполнения потока, работающий до принудительного завершения
	{
		if(DataReady->WaitFor(INFINITE) == wrSignaled) // Ждем, пока флаг DataReady не будет поднят
		{
			DataReady->ResetEvent(); // Сбрасываем флаг готовности данных
			i++;                                   //счетчик номера строки
            path = Form1->Edit1->Text.c_str(); // Получаем путь/диск
//            numOfCluster = Form1->foundCl;
            int d = 0;
			MyDB.writeToDB(path, Form1->foundCl, selectedExept);
            int f = 0;
            Synchronize(addRow); // Добавляем строку в таблицу

			DataCopied->SetEvent(); // Поднимаем флаг, сигнализирующий о том, что данные скопированы

    	}
	}
}
//---------------------------------------------------------------------------
void __fastcall WriteToDB::treeClear()
{
	Form1->VirtualStringTree1->Clear(); // Очищаем VirtualStringTree
}
//---------------------------------------------------------------------------
void __fastcall WriteToDB::addRow()
{
	PVirtualNode myNode = Form1->VirtualStringTree1->AddChild(Form1->VirtualStringTree1->RootNode); // Добавляем дочерний узел к корневому элементу дерева строк
	TreeNode* myData = (TreeNode*)Form1->VirtualStringTree1->GetNodeData(myNode); // Получаем доступ к данным узла, связывая его с заранее определенной структурой TreeNode
	myData->index = i;
	myData->path = Form1->Edit1->Text;
	myData->numOfCluster = Form1->foundCl;
    int selectedIndex = Form1->RadioGroup1->ItemIndex;
	myData->selectedExept = Form1->RadioGroup1->Items->Strings[selectedIndex].c_str();
}
//---------------------------------------------------------------------------
