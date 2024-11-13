//---------------------------------------------------------------------------

#pragma hdrstop

#include "Iterator.h"

iterator::iterator(BaseFileSystem* FS)
{
	MyFS = FS; // ��������� ��������� �� ��
	currentCluster = 0;
	lastCluster = FS -> getClustersPerDisk();
	pResultBuffer = new BYTE[FS -> getClusterSize()]; // ������� ����� ��� �������� ������ ��������
}

void iterator::First()
{
	currentCluster = 0; // ����� �������� �������� �� ���������
}

void iterator::Next()
{
	currentCluster++; // ����������� ������ �������� �������� �� 1
}

bool iterator::IsDone()
{
	return currentCluster >= lastCluster; // ���������� true, ���� ������� ������� ������ ��� ����� ����������
}

void iterator::getCurrentCluster()
{
    if (!IsDone()) {
    	MyFS->readClusterNumber(currentCluster, pResultBuffer); // ������ ������ �������� � �����
    }

}
//---------------------------------------------------------------------------
#pragma package(smart_init)
