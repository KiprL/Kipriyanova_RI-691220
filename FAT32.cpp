#include "FAT32.h"
#include <iostream>
#include <windows.h>

FAT32::FAT32(HANDLE myHandle) : BaseFileSystem(myHandle) {
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = 0;

	// ������ 1-� ������
	BYTE *pBootRecordBuffer = new BYTE[512];
	readBytesFromOffset(startOffset, pBootRecordBuffer, 512);

	#pragma pack(push,1)
	struct myStruct {
		BYTE jump[11]; // ������� ������ 11 ������
		uint16_t bytesPerSector; // �� �������� 0�0� 2 ����� - ���������� ���� � �������
		uint8_t sectorsPerCluster; // �� �������� 0�0D 1 ���� - ���������� �������� � ��������
		uint16_t initialSector; // �� �������� 0�0� 2 ����� - ���������� �������� ����������������� �������
		uint8_t countOfFAT; // �� �������� 0�10 1 ���� - ���������� ����� ������� FAT
		BYTE jump2[15]; // ������� 15 ����
		uint32_t sectorsPerDisk; // �� �������� 0�20 4 ����� - ����� �������� �� �����
		uint32_t sizeOfFAT; // �� �������� 0�24 4 ����� - ����� ������� FAT � ��������
	};
	#pragma pack(pop)
	// ����������� ��������� ��������� �� �����
	myStruct* info = (myStruct*)pBootRecordBuffer;
	// ���������� ������ ��������
	int clusterSize = info->bytesPerSector * info->sectorsPerCluster;
	int clusterPerDisk = info->sectorsPerDisk / info->sectorsPerCluster - ((info -> initialSector + info -> countOfFAT * info -> sizeOfFAT) * info -> bytesPerSector) / clusterSize;

	// ���������� ������ �������� � ���-�� �������� �� �����
	setClusterSize(clusterSize);
	setClustersPerDisk(clusterPerDisk);

	// ����������� ������ ��������, ������� � ���������� �������� 2-�� ��������
	secondClusterOffset = (info -> initialSector + info -> countOfFAT * info -> sizeOfFAT) * info -> bytesPerSector;

	delete[] pBootRecordBuffer;
}

FAT32::~FAT32() {}

void FAT32::readClusterNumber(unsigned int clusterNumber, BYTE *pResultBuffer) {
	DWORD clusterSize = getClusterSize();

	if (clusterSize == NULL) {
		throw "������ ������ ��������: ������ �������� �� ��������";
	}

    // ��������� �������� ��� ������ �������� (�������� ������ �������)
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = secondClusterOffset + (clusterNumber - 2) * clusterSize;

	readBytesFromOffset(startOffset, pResultBuffer, clusterSize);
}
