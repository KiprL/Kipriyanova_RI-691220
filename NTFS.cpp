#include "NTFS.h"
#include <iostream>
#include <windows.h>

NTFS::NTFS(HANDLE myHandle) : BaseFileSystem(myHandle) {
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = 0;

    // ������ 1-� ������
	BYTE* pBootRecordBuffer = new BYTE[512];
	readBytesFromOffset(startOffset, pBootRecordBuffer, 512);

	// ���������, ������� ������������� �� ����� ��� ������������ ���������� ��� ����������� ������� ��������
	#pragma pack(push,1)
	struct myStruct {
		BYTE jump[11]; // ������� ������ 11 ������
		uint16_t bytesPerSector; // �� �������� 0�� 2 ����� - ���������� ���� � �������
		uint8_t sectorsPerCluster; // �� �������� 0�D 1 ���� - ���������� �������� � ��������
		BYTE jump2[26]; // ������� 26 ������
		uint64_t sectorsPerDisk; // �� �������� 0�28 8 ���� - ����� �������� �� �����
	};
	#pragma pack(pop)
	// ����������� ��������� ��������� �� �����
	myStruct* info = (myStruct*)pBootRecordBuffer;
	// ���������� ������ ��������
	int clusterSize = info->bytesPerSector * info->sectorsPerCluster;
	int clusterPerDisk = info->sectorsPerDisk / info->sectorsPerCluster;
	setClusterSize(clusterSize);
    setClustersPerDisk(clusterPerDisk);

	
	delete[] pBootRecordBuffer;
}

NTFS::~NTFS() {}

void NTFS::readClusterNumber(unsigned int clusterNumber, BYTE* pResultBuffer) {
	DWORD clusterSize = getClusterSize();
	if (clusterSize == NULL) {
		throw "������ ������ ��������: ������ �������� �� ��������";
	}

    // ��������� �������� ��� ������ �������� (�������� ������ �������)
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = clusterNumber * clusterSize;

	readBytesFromOffset(startOffset, pResultBuffer, clusterSize);
}
