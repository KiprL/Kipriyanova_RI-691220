//---------------------------------------------------------------------------

#ifndef ThreadDBH
#define ThreadDBH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "ThreadSearching.h"

//---------------------------------------------------------------------------
class WriteToDB : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall WriteToDB(bool CreateSuspended);
    void __fastcall treeClear();
	void __fastcall addRow();
    ULONGLONG numOfCluster;
	const wchar_t* path;
	const wchar_t* selectedExept;
	TEvent *DataReady;
	TEvent *DataCopied;
	//TEvent *DataWritten;
	ULONGLONG i;
};
//---------------------------------------------------------------------------
#endif
