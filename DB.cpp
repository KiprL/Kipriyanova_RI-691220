//---------------------------------------------------------------------------

#pragma hdrstop

#include "DB.h"

SQL::SQL()
{
	const char* filepath = "mySQLDB.sqlite3";
	sqlite3_open(filepath, &myDB); // ����������� � ��
    const char* sql = "CREATE TABLE IF NOT EXISTS clusters (number INTEGER, signature TEXT, disk TEXT)"; // SQL-������ �� �������� �������, ���� ��� �� ����������
//	const char* sql = "CREATE TABLE IF NOT EXISTS clusters (id int NOT NULL AUTOINCREMENT, number int64, signature TEXT, disk TEXT)";
	sqlite3_exec(myDB, sql, NULL, NULL, NULL); // �������� �������, �������� SQL-������
	sqlite3_prepare_v2(myDB, "INSERT INTO clusters VALUES (?, ?, ?)", -1, &mySTMT, NULL); // ���������� SQL-������� �� ������� ������ � �������
};

void SQL::writeToDB(const wchar_t* path, ULONGLONG FoundCluster, const wchar_t* signOfChoosenExtension)
{
	sqlite3_bind_int64(mySTMT, 1, FoundCluster); // �������� ������ �������� � ������ �������� �������
	sqlite3_bind_text16(mySTMT, 2, signOfChoosenExtension, -1, SQLITE_TRANSIENT); // �������� ���������� ����� �� ������ �������� �������
	sqlite3_bind_text16(mySTMT, 3, path, -1, SQLITE_TRANSIENT); // �������� ���� � ������ �������� �������


	sqlite3_step(mySTMT); // ���������� ��������������� �������

    sqlite3_reset(mySTMT); // ����� ������� ��� ��������� ������
    sqlite3_clear_bindings(mySTMT); // ������� ����������� ��������, ������������ ��������

};

SQL::~SQL()
{
	sqlite3_finalize(mySTMT); // ������������ ��������������� SQL-�������
	sqlite3_close(myDB);
};
//---------------------------------------------------------------------------
#pragma package(smart_init)
