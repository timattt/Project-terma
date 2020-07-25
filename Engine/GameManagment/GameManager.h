#pragma once
#include "../SceneManagment/Scene.h"
/*!
* ������� ��������� ����� ����, ������� ��������� � �������������� �� ���������.
* �������� ������ ���� (� Launch) �������� ����.
* 
* ��� ���� �������� ������ ������������� �������� �����. �������� ������ ������ ���������� �������� �����������,
* ��� ��� � ���� ������ �� ����� �������� ������ ���������.
* 
* �� ������ ������ ��������� ����� MainMenu. ��������� � ������ � SceneManager.h
* 
* ���������
*/
class GameManager
{
public:
	static void Launch(Scene* start_scene); //! ������������� ���� ���������� � ������� ����. ������ ������ �����


private:
	static bool is_exit; //! ���������, ��� �� �������� ����� �� ���� ��������� ���� ��� ���� ������

};
