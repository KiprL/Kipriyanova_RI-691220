//---------------------------------------------------------------------------

#pragma hdrstop

#include "DB.h"

SQL::SQL()
{
	const char* filepath = "mySQLDB.sqlite3";
	sqlite3_open(filepath, &myDB); // Подключение к БД
    const char* sql = "CREATE TABLE IF NOT EXISTS clusters (number INTEGER, signature TEXT, disk TEXT)"; // SQL-запрос на создание таблицы, если она не существует
//	const char* sql = "CREATE TABLE IF NOT EXISTS clusters (id int NOT NULL AUTOINCREMENT, number int64, signature TEXT, disk TEXT)";
	sqlite3_exec(myDB, sql, NULL, NULL, NULL); // Создание таблицы, выполняя SQL-запрос
	sqlite3_prepare_v2(myDB, "INSERT INTO clusters VALUES (?, ?, ?)", -1, &mySTMT, NULL); // Подготовка SQL-запроса на вставку данных в таблицу
};

void SQL::writeToDB(const wchar_t* path, ULONGLONG FoundCluster, const wchar_t* signOfChoosenExtension)
{
	sqlite3_bind_int64(mySTMT, 1, FoundCluster); // Передача номера кластера в первый параметр запроса
	sqlite3_bind_text16(mySTMT, 2, signOfChoosenExtension, -1, SQLITE_TRANSIENT); // Передача расширения файла во второй параметр запроса
	sqlite3_bind_text16(mySTMT, 3, path, -1, SQLITE_TRANSIENT); // Передача пути в третий параметр запроса


	sqlite3_step(mySTMT); // Выполнение подготовленного запроса

    sqlite3_reset(mySTMT); // Сброс запроса для следующей записи
    sqlite3_clear_bindings(mySTMT); // Очистка привязанных значений, освобождение ресурсов

};

SQL::~SQL()
{
	sqlite3_finalize(mySTMT); // Освобождение подготовленного SQL-запроса
	sqlite3_close(myDB);
};
//---------------------------------------------------------------------------
#pragma package(smart_init)
