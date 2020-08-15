#include "Views.h"

#include "ProjectTerma.h"

// Define static variables
unsigned Views::MAIN_MENU = -1;
unsigned Views::PLAYER_CAM = -1;
unsigned Views::EDITOR_CAM = -1;

void Views::LOAD_ALL_VIEWS() {
	Views::MAIN_MENU = GraphicManager::AddView({{ 0, 0 }, cur_resolution,{ 0, 0 },{ 0, 0 },{ 1600,900 },{ 0, 0 },{ 1, -1 }});
	Views::PLAYER_CAM = GraphicManager::AddView({{0, 0}, cur_resolution, { 0, 0}, { 0, 0 }, { 1600,900 }, { 0.5, 0.5 }, { 1, -1 }});
	Views::EDITOR_CAM = GraphicManager::AddView({cur_resolution * 0.5, cur_resolution * 0.5, { 0.5, 0.5}, { 0, 0 }, { 1600,900 }, { 0.5, 0.5 }, { 1, -1 }});
}

void Views::SET_RESOLUTION(Vector2U new_size)
{
	GraphicManager::GetView(MAIN_MENU)->real_size = Vector2F(new_size.x, new_size.y);

	GraphicManager::GetView(PLAYER_CAM)->real_size = Vector2F(new_size.x, new_size.y);

	GraphicManager::GetView(EDITOR_CAM)->real_position = Vector2F(new_size.x * 0.5, new_size.y * 0.5);
	GraphicManager::GetView(EDITOR_CAM)->real_size = Vector2F(new_size.x * 0.5, new_size.y * 0.5);
}
