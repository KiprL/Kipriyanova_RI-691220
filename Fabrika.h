#include <iostream>
#include <windows.h>
#include "NTFS.h"
#include "FAT32.h"
//#include "Forma.h"
#pragma once
enum class FileSystems {NTFS, FAT32, NONE};

// Структура, которая накладывается на буфер для определения ФС
#pragma pack(push,1)
struct myStructFS {
	BYTE jump[3]; // Пропуск первых 3 байтов
	uint32_t bytesNTFS; // По смещению 0х4 4 байта - указатель на NTFS
	BYTE jump2[75]; // Пропуск 75 байтов
	uint32_t bytesFAT32_1; // По смещению 0х52 5 байт - указатель на FAT32
	uint8_t bytesFAT32_2;
};
#pragma pack(pop)

class MyFabric
{
public:

	FileSystems decideFileSystem();
	BaseFileSystem* getFileSystem(FileSystems FS);
	MyFabric(const wchar_t* path);
	HANDLE MyHandle;
    myStructFS* infoFS;
};
