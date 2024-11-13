#include <iostream>
#include <windows.h>
#include <string.h>
#include "Fabrika.h"



MyFabric::MyFabric(const wchar_t* path)
{
    BYTE* pBootRecordBuffer = new BYTE[512]; // Создаем буфер для чтения 1 сектора
	//(startOffset, pBootRecordBuffer, 512);
	MyHandle = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(MyHandle, pBootRecordBuffer, 512, 0, NULL); // Читаем первый сектор (512 байт) в буфер
	infoFS = (myStructFS*)pBootRecordBuffer; // Преобразуем считанные данные в структуру для анализа
    int c = 0;
}

FileSystems MyFabric::decideFileSystem() // Определение ФС по сигнатуре
{
	if (infoFS->bytesNTFS == 0x5346544E)
	{
		return FileSystems::NTFS;
	}
	else if (infoFS->bytesFAT32_1 == 0x33544146 && infoFS->bytesFAT32_2 == 0x32)
	{
		return FileSystems::FAT32;
	}
	else return FileSystems::NONE;
}

BaseFileSystem* MyFabric::getFileSystem(FileSystems FS) // Создание объекта ФС
{
	if (FS == FileSystems::NTFS)
	{
		return new NTFS(MyHandle);
	}
	else if (FS == FileSystems::FAT32)
	{
		return new FAT32(MyHandle);
	}
    else return NULL;
}

