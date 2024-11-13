//---------------------------------------------------------------------------

#pragma hdrstop
#include <iostream>
#include "Decorator.h"

decorator::decorator(iterator iter)
{
	this -> MyIter = iter; // Сохраняем итератор для доступа к кластерам
	int ChoosenExtension = Form1->RadioGroup1->ItemIndex; // Сохраняем выбранное расширение в форме
	if (ChoosenExtension == 0)   // EXE
	{
		signOfExtension = new BYTE[4]{ 0x4D, 0x5A };
    }
	else if (ChoosenExtension == 1)  // PDF
	{
		signOfExtension = new BYTE[5]{ 0x25, 0x50, 0x44, 0x46, 0x2D };
	}
	else if (ChoosenExtension == 2)   // ZIP
	{
		signOfExtension = new BYTE[4] { 0x50, 0x4B, 0x03, 0x04 };
	}
	else if (ChoosenExtension == 3)   // DEB
	{
		signOfExtension = new BYTE[21]{ 0x21, 0x3C, 0x61, 0x72, 0x63, 0x68, 0x3E, 0x0A, 0x64, 0x65, 0x62, 0x69, 0x61, 0x6E, 0x2D, 0x62, 0x69, 0x6E, 0x61, 0x72, 0x79 };
	}
	else {signOfExtension = NULL;}
}
// С помощью данного метода обрезаем нулевые байты в массиве для дальнейшего определения размера массива с расширением
int decorator::countNonZero(BYTE* array) {
    int count = 0;
    for (int i = 0; i < sizeof(array); ++i) {
        if (array[i] != 0) {
            ++count;
        }
    }
    return count;
}

void decorator::First() {MyIter.First(); Next();}

bool decorator::IsDone() {return MyIter.IsDone();}

void decorator::Next()
{
	int b = 0;
	MyIter.getCurrentCluster(); // Получаем текущий кластер
	bool match = false;
	//size_t razm=sizeof(*signOfExtension);
	int razm=countNonZero(signOfExtension); // Получаем длину сигнатуры без нулевых байтов
	//int razm = 2;
	while (!match && !IsDone()) // Выполняем до нахождения совпадения или завершения итерации
	{
		MyIter.Next();
		MyIter.getCurrentCluster();
		int comp = memcmp(MyIter.pResultBuffer, signOfExtension, razm);
		if (comp == 0) // Установка флага, если сигнатура найдена
		{
			match = true;
		}
		else {
			match = false;
			//MyIter.Next();
		}
//		for (int i = 0; i < sizeof(*signOfExtension); i++)
//		{
//			if (MyIter.pResultBuffer[i] == signOfExtension[i])
//			{
//				match = true;
//			}
//			else
//			{
//				match = false;
//			}
//		}
		//MyIter.Next();
	}
	//MyIter.Next();
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
