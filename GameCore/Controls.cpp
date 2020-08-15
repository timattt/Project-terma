#include "Controls.h"

void Controls::LOAD_ALL_GAMEKEYS()
{
	InputManager::LinkToCode(KeyboardKey::RIGHT, Controls::RIGHT);
	InputManager::LinkToCode(KeyboardKey::UP, Controls::UP);
	InputManager::LinkToCode(KeyboardKey::DOWN, Controls::DOWN);
	InputManager::LinkToCode(KeyboardKey::LEFT, Controls::LEFT);
	InputManager::LinkToCode(KeyboardKey::E, Controls::OPEN_INV);
	InputManager::LinkToCode(KeyboardKey::ESC, Controls::BACK);
}
