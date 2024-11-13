//---------------------------------------------------------------------------

#ifndef DecoratorH
#define DecoratorH
#include "Iterator.h"
#include "Forma.h"

class decorator
{
public:
    decorator(iterator iter);
	BYTE* pResultBuffer;
	BYTE* signOfExtension;
	iterator MyIter;
    int countNonZero(BYTE* array);
	void First();
	void Next();
	bool IsDone();


	void getCurrentCluster();
};
//---------------------------------------------------------------------------
#endif
