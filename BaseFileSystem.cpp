#include "BaseFileSystem.h"

BaseFileSystem::BaseFileSystem(HANDLE MyHandle) {
	clusterSize = NULL; // Инициализация размера кластера
	fileHandle = MyHandle; // Присваиваем путь файла
}

BaseFileSystem::~BaseFileSystem() {
	CloseHandle(fileHandle);
}

void BaseFileSystem::readBytesFromOffset(LARGE_INTEGER startOffset, BYTE *pResultBuffer, DWORD bytesToRead) {
    // Устанавливается позиция указателя файла на заданное смещение (startOffset)
	ULONGLONG filePointer = SetFilePointer(fileHandle, startOffset.LowPart, &startOffset.HighPart, FILE_BEGIN);
	if (filePointer == INVALID_SET_FILE_POINTER) {
		throw "Ошибка установки filePointer";
	}

	DWORD bytesRead;
    // Чтение данных в pResultBuffer из файла, начиная с указанного смещения
	bool readResult = ReadFile(fileHandle, pResultBuffer, bytesToRead, &bytesRead, NULL);
	if (!readResult || bytesRead != bytesToRead) {
		throw "Ошибка чтения readResult";
	}
}

void BaseFileSystem::setClusterSize(unsigned int clSize) {
	clusterSize = clSize; // Установка размера кластера
}

unsigned int BaseFileSystem::getClusterSize() {
	return clusterSize; // Возвращение размера кластера
}

void BaseFileSystem::setClustersPerDisk(unsigned int clasDisk) {
	clustersPerDisk = clasDisk; // Установка кол-ва кластеров
}

unsigned int BaseFileSystem::getClustersPerDisk() {
	return clustersPerDisk; // Возвращает кол-во кластеров
}

//void BaseFileSystem::readClusterNumber() {}
