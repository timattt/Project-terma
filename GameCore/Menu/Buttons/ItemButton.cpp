#include "ItemButton.h"

#include <cstdio>
#include <iostream>
#include <vector>

#include "../../../Engine/Control/InputManager.h"
#include "../../../Engine/Graphics/DrawData.h"
#include "../../../Engine/Graphics/GraphicManager.h"
#include "../../../Engine/Utility/Coordinate.h"
#include "../../Items/Equippable.h"
#include "../../Map/Map.h"
#include "../../Player/Inventory.h"
#include "../../Player/Player.h"
#include "../../PTC.h"
#include "../../Scenes/InventoryScene.h"
#include "../../Views.h"
#include "../Cell.h"
#include "../ImageWidgets/ItemFocus.h"

ItemButton::ItemButton(Item *_item) {
	item = _item;
	was_focused = false;
	is_dragged = false;
}

const Vector2F weaponEquippedIcon = { 1021, 435 };

void ItemButton::leftClickReact() {
	// Equip this item (give the pointer to the player, indicate that other item is unequipped)

	Equippable *_item = dynamic_cast<Equippable*>(item);

	if (_item != nullptr) {
		this->setDragged();
	}
}

void ItemButton::focusReact() {
	// Show that this item is focused - indicate this item for item_focus image widget
	InventoryScene *_scene = dynamic_cast<InventoryScene*>(current_scene);

	if (!is_dragged) {
		_scene->focused_item->focusItem(this->item);
		was_focused = true;
	} else {
		disfocusReact();
	}
	// printf("FOCUS ITEMBUTTON! ADDRESS - %x\n", _scene);
}

void ItemButton::disfocusReact() {
	/*
	 printf("=============\n");
	 printf("DISFOCUSED ITEMBUTTON NOW!\n");
	 printf("=============\n");
	 */

	// Disfocus (if have been focused)
	InventoryScene *_scene = dynamic_cast<InventoryScene*>(this->current_scene);

	if (was_focused) {
		_scene->focused_item->disfocus();
		was_focused = false;
	}
}

void ItemButton::Destroy() {
	PTC::sayDestroyed("ItemButton");
}

void ItemButton::Init(GameObject *owner) {
	PTC::sayCreated("ItemButton");
}

void ItemButton::setOriginalPos(Vector2F original) {
	original_pos = original;
}

Vector2F ItemButton::getOriginalPos() {
	return original_pos;
}

void ItemButton::Update() {
	Equippable *_item = dynamic_cast<Equippable*>(item);

	if (isDragged()) {
		_item->SetPos(
				GraphicManager::ConvertRealToView(InputManager::GetMousePos(),
						Views::MAIN_MENU));
		SetPos(
				GraphicManager::ConvertRealToView(InputManager::GetMousePos(),
						Views::MAIN_MENU));
	}

	if (_item != nullptr && !is_dragged) {
		if (_item->isEquipped()) {
			// If this button's item is equipped, change it's position to the equipped icon
			SetPos(weaponEquippedIcon);
			item->SetPos(weaponEquippedIcon);
		} else {
			// Othewise return the original position
			SetPos(getOriginalPos());
			item->SetPos(getOriginalPos());
		}
	}

	if (isFocused())
		focusReact();
	else
		disfocusReact();
	if (isRightClicked())
		rightClickReact();
	if (isLeftClicked())
		leftClickReact();
	if (InputManager::IsRealesed(MouseKey::Mouse_Left) && is_dragged) {
		leftButtonReleaseReact();
	}
}

void ItemButton::rightClickReact() {
	// Nothing for now
}

void ItemButton::setDragged() {
	is_dragged = true;
}

bool ItemButton::isDragged() {
	return is_dragged;
}

void ItemButton::leftButtonReleaseReact() {
	// If the item was released, check its position
	InventoryScene *_scene = dynamic_cast<InventoryScene*>(current_scene);
	Equippable *_item = dynamic_cast<Equippable*>(item);

	is_dragged = false;

	Vector2F calculate = { _pos.x - (itemStartPos.x - itemIconSize.x / 2),
			(itemStartPos.y + itemIconSize.y / 2) - _pos.y };

	// If the button got to the equipping icon, its good
	if (_pos.x >= weaponEquippedIcon.x - _size.x / 2
			&& _pos.x <= weaponEquippedIcon.x + _size.x / 2
			&& _pos.y >= weaponEquippedIcon.y - _size.y / 2
			&& _pos.y <= weaponEquippedIcon.y + _size.y / 2) {
		if (_scene->gamefield->player->isEquipped()) {
			// Some item is equipped at the moment
			Equippable *__item =
					dynamic_cast<Equippable*>(_scene->gamefield->player->weapon_equipped);
			__item->unequip();
		}

		_item->equip();
		_scene->gamefield->player->equipWeapon(item);

	} else if (calculate.x >= 0 && calculate.y >= 0) {
		// Item is in the inventory bar

		Vector2F cell = { static_cast<float>(static_cast<int>(calculate.x)
				/ static_cast<int>(itemIconSize.x)),
				static_cast<float>(static_cast<int>(calculate.y)
						/ static_cast<int>(itemIconSize.y)) };

		if (cell.x < maxColumns + 1 && cell.y < maxRows && _scene->cells[static_cast<int>(cell.y * maxColumns + cell.x)].getButton() == nullptr) {
			_item->unequip();
			_scene->gamefield->player->unequipWeapon();

			// Change item's position in the inventory
			_scene->gamefield->player->inventory->getItems()->at(cell.y * maxColumns + cell.x)
					= _scene->gamefield->player->inventory->getItems()->at(
							(itemStartPos.y - getOriginalPos().y) / itemIconSize.y * maxColumns
							+ (getOriginalPos().x - itemStartPos.x) / itemIconSize.x);
			 _scene->cells[static_cast<int>(cell.y * maxColumns + cell.x)].setButton(this);
			_scene->gamefield->player->inventory->getItems()->at(
										(itemStartPos.y - getOriginalPos().y) / itemIconSize.y * maxColumns
										+ (getOriginalPos().x - itemStartPos.x) / itemIconSize.x) = nullptr;
			_scene->cells[static_cast<int>((itemStartPos.y - getOriginalPos().y) / itemIconSize.y * maxColumns
		+ (getOriginalPos().x - itemStartPos.x) / itemIconSize.x)].setButton(nullptr);

			setOriginalPos(
					Vector2F(itemStartPos.x + cell.x * itemIconSize.x,
							itemStartPos.y - cell.y * itemIconSize.y));

		}

		/* else if (_pos.x >= getOriginalPos().x - _size.x / 2
		 && _pos.x <= getOriginalPos().x + _size.x / 2
		 && _pos.y >= getOriginalPos().y - _size.y / 2
		 && _pos.y <= getOriginalPos().y + _size.y / 2) {
		 // Unequip and put back
		 _item->unequip();
		 _scene->gamefield->player->unequipWeapon();
		 SetPos(getOriginalPos());
		 }
		 */
	}
}

ItemButton::~ItemButton() {
	item = nullptr;
}

void ItemButton::Draw() {
	DrawData info = { };

	info.position = _pos;

	info.size = _size;

	info.origin = { 0.5, 0.5 };

	info.frame = 1;
	info.layer = (this->is_dragged) ?  layer + 1 : layer;

	info.spriteID = this->sprite_id;
	GraphicManager::Draw(info, view_id);
}
