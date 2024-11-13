#include "BaseFileSystem.h"

BaseFileSystem::BaseFileSystem(HANDLE MyHandle) {
	clusterSize = NULL; // ������������� ������� ��������
	fileHandle = MyHandle; // ����������� ���� �����
}

BaseFileSystem::~BaseFileSystem() {
	CloseHandle(fileHandle);
}

void BaseFileSystem::readBytesFromOffset(LARGE_INTEGER startOffset, BYTE *pResultBuffer, DWORD bytesToRead) {
    // ��������������� ������� ��������� ����� �� �������� �������� (startOffset)
	ULONGLONG filePointer = SetFilePointer(fileHandle, startOffset.LowPart, &startOffset.HighPart, FILE_BEGIN);
	if (filePointer == INVALID_SET_FILE_POINTER) {
		throw "������ ��������� filePointer";
	}

	DWORD bytesRead;
    // ������ ������ � pResultBuffer �� �����, ������� � ���������� ��������
	bool readResult = ReadFile(fileHandle, pResultBuffer, bytesToRead, &bytesRead, NULL);
	if (!readResult || bytesRead != bytesToRead) {
		throw "������ ������ readResult";
	}
}

void BaseFileSystem::setClusterSize(unsigned int clSize) {
	clusterSize = clSize; // ��������� ������� ��������
}

unsigned int BaseFileSystem::getClusterSize() {
	return clusterSize; // ����������� ������� ��������
}

void BaseFileSystem::setClustersPerDisk(unsigned int clasDisk) {
	clustersPerDisk = clasDisk; // ��������� ���-�� ���������
}

unsigned int BaseFileSystem::getClustersPerDisk() {
	return clustersPerDisk; // ���������� ���-�� ���������
}

//void BaseFileSystem::readClusterNumber() {}
