#include "FAT32.h"
#include <iostream>
#include <windows.h>

FAT32::FAT32(HANDLE myHandle) : BaseFileSystem(myHandle) {
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = 0;

	// Читаем 1-й сектор
	BYTE *pBootRecordBuffer = new BYTE[512];
	readBytesFromOffset(startOffset, pBootRecordBuffer, 512);

	#pragma pack(push,1)
	struct myStruct {
		BYTE jump[11]; // Пропуск первых 11 байтов
		uint16_t bytesPerSector; // По смещению 0х0В 2 байта - количество байт в секторе
		uint8_t sectorsPerCluster; // По смещению 0х0D 1 байт - количество секторов в кластере
		uint16_t initialSector; // По смещению 0х0Е 2 байта - количество секторов зарезервированной области
		uint8_t countOfFAT; // По смещению 0х10 1 байт - количество копий таблицы FAT
		BYTE jump2[15]; // Пропуск 15 байт
		uint32_t sectorsPerDisk; // По смещению 0х20 4 байта - число секторов на диске
		uint32_t sizeOfFAT; // По смещению 0х24 4 байта - объем области FAT в секторах
	};
	#pragma pack(pop)
	// Накладываем созданную структуру на буфер
	myStruct* info = (myStruct*)pBootRecordBuffer;
	// Определяем размер кластера
	int clusterSize = info->bytesPerSector * info->sectorsPerCluster;
	int clusterPerDisk = info->sectorsPerDisk / info->sectorsPerCluster - ((info -> initialSector + info -> countOfFAT * info -> sizeOfFAT) * info -> bytesPerSector) / clusterSize;

	// Записываем размер кластера и кол-во секторов на диске
	setClusterSize(clusterSize);
	setClustersPerDisk(clusterPerDisk);

	// Вытаскиваем нужные значения, считаем и записываем смещение 2-го кластера
	secondClusterOffset = (info -> initialSector + info -> countOfFAT * info -> sizeOfFAT) * info -> bytesPerSector;

	delete[] pBootRecordBuffer;
}

FAT32::~FAT32() {}

void FAT32::readClusterNumber(unsigned int clusterNumber, BYTE *pResultBuffer) {
	DWORD clusterSize = getClusterSize();

	if (clusterSize == NULL) {
		throw "Ошибка чтения кластера: размер кластера не определён";
	}

    // Вычисляем смещение для чтения кластера (учитывая второй кластер)
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = secondClusterOffset + (clusterNumber - 2) * clusterSize;

	readBytesFromOffset(startOffset, pResultBuffer, clusterSize);
}
