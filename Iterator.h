//---------------------------------------------------------------------------
#pragma once
#include "BaseFileSystem.h"
#include <windows.h>
#ifndef IteratorH
#define IteratorH

//---------------------------------------------------------------------------
class iterator
{
public:
	BaseFileSystem* MyFS;
	BYTE* pResultBuffer;
	ULONGLONG currentCluster;
	ULONGLONG lastCluster;
	void First();
	void Next();
	bool IsDone();
	iterator(BaseFileSystem* FS);
    iterator() = default;

	void getCurrentCluster();
};
#endif
