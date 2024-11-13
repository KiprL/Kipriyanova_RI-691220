#include <windows.h>
#include "BaseFileSystem.h"
#pragma once

class NTFS : public BaseFileSystem
{
private:
    unsigned int secondClusterOffset;

public:
    void readClusterNumber(unsigned int clusterNumber, BYTE* pResultBuffer);

    NTFS(HANDLE myHandle);
    ~NTFS();
};

