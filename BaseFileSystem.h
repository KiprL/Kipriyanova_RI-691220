#pragma once
#include <windows.h>
#pragma once

class BaseFileSystem
{
private:
	unsigned int clusterSize;
	unsigned int clustersPerDisk;
    HANDLE fileHandle;

protected:
	void readBytesFromOffset(LARGE_INTEGER startOffset, BYTE *pResultBuffer, DWORD bytesToRead);
	void setClusterSize(unsigned int clSize);
	void setClustersPerDisk(unsigned int clasDisk);

public:
	virtual unsigned int getClusterSize();
	virtual void readClusterNumber(unsigned int clusterNumber, BYTE* pResultBuffer) = 0;
	virtual unsigned int getClustersPerDisk();

    BaseFileSystem(HANDLE myHandle);
    ~BaseFileSystem();
};
