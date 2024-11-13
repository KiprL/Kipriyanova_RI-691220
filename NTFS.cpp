#include "NTFS.h"
#include <iostream>
#include <windows.h>

NTFS::NTFS(HANDLE myHandle) : BaseFileSystem(myHandle) {
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = 0;

    // Читаем 1-й сектор
	BYTE* pBootRecordBuffer = new BYTE[512];
	readBytesFromOffset(startOffset, pBootRecordBuffer, 512);

	// Структура, которая накладывается на буфер для вытаскивания информации для определения размера кластера
	#pragma pack(push,1)
	struct myStruct {
		BYTE jump[11]; // Пропуск первых 11 байтов
		uint16_t bytesPerSector; // По смещению 0хВ 2 байта - количество байт в секторе
		uint8_t sectorsPerCluster; // По смещению 0хD 1 байт - количество секторов в кластере
		BYTE jump2[26]; // Пропуск 26 байтов
		uint64_t sectorsPerDisk; // По смещению 0х28 8 байт - число секторов на диске
	};
	#pragma pack(pop)
	// Накладываем созданную структуру на буфер
	myStruct* info = (myStruct*)pBootRecordBuffer;
	// Определяем размер кластера
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
		throw "Ошибка чтения кластера: размер кластера не определён";
	}

    // Вычисляем смещение для чтения кластера (учитывая второй кластер)
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = clusterNumber * clusterSize;

	readBytesFromOffset(startOffset, pResultBuffer, clusterSize);
}
