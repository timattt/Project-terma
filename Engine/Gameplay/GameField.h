#pragma once
#include "ObjectsArray.h"

/*!
* ����� �������� ����.
* �������� �����-���� ������ � ����������� ��.
* ������ ������� ������� � ���������� ���������� ���
* 
* ����� ������� ��������� ������� ����� ������������
* 
* �� ������ ������ �������� ����� ������ �������� ���� � Gameplay Scene. ���� �������������� ������� ���� �� �����
* ������� ���� ����� ������������. � ���� ������ ��� ������� ���������� ������������� �� ����.
* 
* �������� �������� �������� �� ������� ����.
* ���������� ���� �������� ������ ��������, � ������� ����� ��������� ��� ������� �������.
* ���� - ������������ ��������� ������� ��������
* ���� ������ ����� ���������� �� ����� ���������� ��������� ���� (� ��� ����� � �� ���������� �� �� �����).
* ����� ������� ��������� �������� �������������� ��������.
* ��������, Player ��������� �� ���� Red, ��� ������� Bullet ����� �� ���� Red, ��������� Bullet �� ���� Blue
* ����� ��������� ������� ������ ��������� ��������, ���������� ����������� ������ �� ���� Blue, ��� ������������� ������� ���� Red.
* 
* ������� �������������� �������� ��������� � ����������
* 
* Init, Update, Destroy ����� ��������
* 
* ��������� �� �������
*/
class GameField
{
public:
	//! ������������� ������� ���� (��� ��������).
	void Init();

	//! ���������� ����� ����. ���������� ������ ����
	void Update();

	//! ����������� �������� ���� � ������� ���� ������
	void Destroy();

	/*!
	* ������� ����� ������� ������. ��������� GameobjectSpawnData �������, �������� ������ ��� ����� ������ �������
	* GameobjectSpawnData ��������:
	*	��������� �� ��� ������. �� ��� ������ ���� ������, ������ ��� ���� �������� � �� ������������������.
	*	������ bool'��, ������� ���������, �� ����� ����� ������ ������������. ��� ���� ������ �������������
	*/ 
	void SpawnObject(const GameobjectSpawnData& new_object);

	/*!
	* ����������� �������. ������������� ������� ������ � �������� Destroy �� ��������� �����.
	* ��������� ��������� �� ������, ����� ��������� O(n), ��� n - ���-�� ��������
	*/
	void KillObject(const GameObject* object);

	/*!
	* ����������� �������. ������������� ������� ������ � �������� Destroy �� ��������� �����.
	* ��������� ������������ ID ������� (����� �������� � ������� GetID), ����� ��������� O(1)
	*/
	void KillObject(const unsigned ID);
private:

	/*!
	* ���������� ����� ������� �����. ������������ ������� ��� �������.
	* �������� �������� ����� ������ ����� ��������� ����� �������� �������� �����������, ��� � ���� ���� Update ���� ��������
	* ����� ��� ����� ������������ ��������
	*/
	void ClearKilledObjects();
	ObjectsArray* _objects;//! ������ ���� ��������. ��������� � ����������� �����
};

