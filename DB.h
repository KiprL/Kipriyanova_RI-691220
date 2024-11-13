//---------------------------------------------------------------------------

#ifndef DBH
#define DBH
#include "sqlite3.h"
#include "windows.h"

class SQL {
public:
	SQL();
	sqlite3* myDB;
	sqlite3_stmt* mySTMT;
	void writeToDB(const wchar_t* path, ULONGLONG FoundCluster, const wchar_t* signOfChoosenExtension);
	~SQL();
};
//---------------------------------------------------------------------------
#endif
