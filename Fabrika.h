#include <iostream>
#include <windows.h>
#include "NTFS.h"
#include "FAT32.h"
//#include "Forma.h"
#pragma once
enum class FileSystems {NTFS, FAT32, NONE};

// ���������, ������� ������������� �� ����� ��� ����������� ��
#pragma pack(push,1)
struct myStructFS {
	BYTE jump[3]; // ������� ������ 3 ������
	uint32_t bytesNTFS; // �� �������� 0�4 4 ����� - ��������� �� NTFS
	BYTE jump2[75]; // ������� 75 ������
	uint32_t bytesFAT32_1; // �� �������� 0�52 5 ���� - ��������� �� FAT32
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
