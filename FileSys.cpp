#include <iostream>
#include "Fabrika.h"
#include "Decorator.h"


int main()
{
	//MyFabric disk(L"\\\\?\\G:");
    MyFabric disk(L"C:\\Games\\fat32.img");
	BaseFileSystem* MyFS = disk.getFileSystem(disk.decideFileSystem());
	//BYTE* pBuffer = new BYTE[MyFS->getClusterSize()];
	//BYTE* pBuffer = new BYTE[4096];

	//std::cout << "Размер кластера: " << pBuffer[20] << std::endl;
	//std::cout << pBuffer << std::endl;
	iterator iter(MyFS);
	decorator Dec(iter);
	//Dec.Next();
    //MyFS->readClusterNumber(1048578, pBuffer);
    int i =0;
	for (Dec.First(); !Dec.IsDone(); Dec.Next()) {
		std::cout << Dec.MyIter.currentCluster << std::endl;
	}
	std::cout << "THE END" << std::endl;
	std::cin.get();




	//setlocale(LC_ALL, "Russian");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
//	const WCHAR* pFileName = L"\\\\?\\I:";
//
//	try {
//		FAT32 fat32 = FAT32(pFileName);
//		std::cout << "Размер кластера: " << fat32.getClusterSize() << std::endl;
//		std::cout << "Кол-во кластеров: " << fat32.getClustersPerDisk() << std::endl;
//
//		BYTE* pBuffer = new BYTE[fat32.getClusterSize()];
//		fat32.readClusterNumber(2, pBuffer);
//
//		#pragma pack(push,1)
//		struct fs{
//			uint32_t a;
//			uint32_t b;
//			uint16_t c;
//		};
//		#pragma pack(pop)
//		fs* prov = new fs;
//		prov = (fs*)pBuffer;
//		std::cout << prov->a << std::endl;
//		std::cout << prov->b << std::endl;
//		std::cout << prov->c;
////		std::cout << "Буфер успешно прочитан! Часть буфера (до нуль-байта): " << pBuffer;
//		std::cin.get();
//
//		delete[] pBuffer;
//	}
//	catch (const char* errorMessage) {
//		std::cout << errorMessage << std::endl;
//		return -1;
//	}
//
//	const WCHAR* pFileName1 = L"\\\\?\\G:";
//	try {
//		NTFS ntfs = NTFS(pFileName1);
//		std::cout << "Размер кластера: " << ntfs.getClusterSize() << std::endl;
//		std::cout << "Кол-во кластеров: " << ntfs.getClustersPerDisk() << std::endl;
//
//		BYTE* pBuffer = new BYTE[ntfs.getClusterSize()];
//		ntfs.readClusterNumber(1, pBuffer);
//
//		#pragma pack(push,1)
//		struct fs{
//			uint32_t a;
//			uint32_t b;
//			uint16_t c;
//		};
//		#pragma pack(pop)
//		fs* prov = new fs;
//		prov = (fs*)pBuffer;
//		std::cout << prov->a << std::endl;
//		std::cout << prov->b << std::endl;
//		std::cout << prov->c;
//		//for (int i = 0; i < ntfs.getClusterSize(); i++) {
//		  //	printf("%X", pBuffer[i]);
//		//}
//		//printf("%X", *pBuffer);
//		std::cin.get();
//
//		delete[] pBuffer;
//	}
//	catch (const char* errorMessage) {
//		std::cout << errorMessage << std::endl;
//		return -1;
//	}

}