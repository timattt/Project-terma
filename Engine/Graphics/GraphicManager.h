#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "DrawData.h"
#include "../Utility/Coordinate.h"

//! ��������� ��� �������� ���������� �� ������������ � ��������, ������������ ������ � GraphicManager
struct GraphicPrefab {
	sf::Texture texture; //! sfml �������� �������
	sf::Sprite sprite; //! sfml ������ ��� ���������
	Vector2F size; //! ������ ������� � ��������
	unsigned frames_count = 1; //! ���-�� �������� � ��������. ��� ���������� ����������� 1
};

//! ��������� ��� �������� ����� ����������� � GraphicManager
struct GraphicPrefabData {
	GraphicPrefabData(std::string f, Vector2F s, unsigned fc) :
		file(f), size(s), frames_count(fc) {}
	std::string file; //! ����, ��� ������������� ���� � ����
	Vector2F size; //! ������ ������� � ��������
	unsigned frames_count = 1; //! ���-�� �������� � ��������. ��� ���������� ����������� 1
};

/*!
* ��������� �����, ��������������� ��� ������ � ��������. 
* 
* ����������� �������, ������� ����� ���� ������� � ������� ���� - ������� Draw, ����� ���������� ������ ������,
* �� ��������� ������� ������������ �� ���.
* 
* ��� ���� �� �������� �������, ��������� �� SFML (���������, � ������, ����� �������������� ��� ����).
* ���� �������� ������������� ��������� � SFML �� ���-�� ������, ����� ����� ���������� ������ �����
* (� ����� TimeManager � InputManager), �������� ���������� ������� (����� �� ����������� ������ ������������� ���������� ����)
* 
* ������� �������� ��������������� ������ ������� ������. ������� ������ ������ ID ����� �������� � ���� enum Sprites
* 
* ��������� ������� �� DrawData � View.
* DrawData - ���������� � ���, ���, ��� � ��� ����� ���������� (�������� � ��������������� �����)
* View �������� �� �������������.
* ��������� View ����� �� ���������� � ������������ ������� ��������� ��������. ��������� � ��� ��� �������� View ��������� � DrawData.h
* 
* ���������
*/
class GraphicManager
{
public:

	//! �������������, �������� �������������
	static void Init();
	
	//! ���������� ���������� ������ ����
	static bool Update();

	//! ����� ���������� ��� �������� ����. ���������� ��� ����, �������� � � ����������
	static void Exit();

	//static void LoadPack();
	//! ���������� ������ �������� DrawData, �������� � ���� View � view_id. data ��� ���� ���������� ��������!!!
	//! ������ true, ���� ���������� �������, false ���� ��� (id ������� ������ ��� ����� ����������� ��������)
	static bool Draw(DrawData& data, Views view_id = Views::BASIC);

	//! ��������� � data ��������������� View. ��� ���� data ����������!
	static void SetView(DrawData& data, Views view_id);

	//! ������������� ������������ ���������� ������������ ����������� ��������
	static void SetSpritesMaxCount(unsigned count);

	//! �������� ������������ ���������� ������������ ����������� ��������
	static unsigned GetSpritesMaxCount();

	//! �������� ���������� ����������� �������� �� ������ ������
	static unsigned GetSpritesCount();

	//! ����������� ����� ��� ��������, �������� �� ����������� ��������� ���������� (�� ����������� ����������� ������������ ������) 
	static void ClearSprites();

	/*!
	* ��������� ������ �� ��������� ���� � �������� ��� �� ��������� ��������� id
	* ������ id ������ ������� ��� �������� ��������, ������ -1 � ������ ������ (��� ��������� id, �� ������ ���� �� ����) 
	*/
	static int LoadSprite(GraphicPrefabData& data);

	/*!
	* ��������� ������ �� ��������� ���� � �������� ��� �� �������� id.
	* ������, ������� ��������� ����� �� ����� id ����������������
	* ������ true ��� �������� ��������, ����� ������ false (������ id ������ ������������ ����������, �� ������ ���� �� ����)
	* id <= GetSpritesMaxCount() ������
	*/
	static bool LoadSprite(GraphicPrefabData& data, unsigned id);

	/*!
	* ���������� ��������� �� view, ������� ������ ID.
	* View �� ������� ��������� ����� ��������, ��� ��� ��� ��������� ��������� �� ����������� ���� ��������, ������������ ������ view
	* ������������ �� ������������� ������ ��������� real_size � 
	*/
	static View* GetView(Views view_id);

private:
	static sf::RenderWindow window; //! ���� SFML, �� ������� ���������� ��� ���������

	static std::vector<GraphicPrefab> sprites; //! ������ ���� �������� ����

	static std::vector<std::list<sf::Sprite>> to_draw; //! ������ ���� ��������, ������� ����� ���������� � ������ ����

	static std::vector<View> views; //! ������ ���� Views. �� ������ ������ ����������� �������

	static const unsigned LAYER_COUNT; //! ����� ���� ���� ���������. �� ������ �� ������ ��������. �������� �� ��, ����� ������� ��������� ������ ������, � ����� ���

	static unsigned _sprites_count;
};