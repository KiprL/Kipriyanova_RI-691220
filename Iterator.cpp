//---------------------------------------------------------------------------

#pragma hdrstop

#include "Iterator.h"

iterator::iterator(BaseFileSystem* FS)
{
	MyFS = FS; // Сохраняем указатель на ФС
	currentCluster = 0;
	lastCluster = FS -> getClustersPerDisk();
	pResultBuffer = new BYTE[FS -> getClusterSize()]; // Создаем буфер для хранения данных кластера
}

void iterator::First()
{
	currentCluster = 0; // Сброс текущего кластера на начальный
}

void iterator::Next()
{
	currentCluster++; // Увеличиваем индекс текущего кластера на 1
}

bool iterator::IsDone()
{
	return currentCluster >= lastCluster; // Возвращает true, если текущий кластер больше или равен последнему
}

void iterator::getCurrentCluster()
{
    if (!IsDone()) {
    	MyFS->readClusterNumber(currentCluster, pResultBuffer); // Чтение данных кластера в буфер
    }

}
//---------------------------------------------------------------------------
#pragma package(smart_init)
