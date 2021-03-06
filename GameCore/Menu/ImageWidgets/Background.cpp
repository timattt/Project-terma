#include "Background.h"

#include <cstdio>

#include "../../../Engine/Graphics/DrawData.h"
#include "../../../Engine/Graphics/GraphicManager.h"
#include "../../PTC.h"

Background::Background() {}

void Background::Init(GameObject *owner) {
	PTC::sayCreated("Background");
}

void Background::Update() {
	//! Background is a static image
	return ;
}

void Background::Draw() {
	DrawData info = { };

	info.position = _pos;

	info.size = _size;

	info.origin = { 0.5, 0.5 };

	info.frame = 0;
	info.layer = this->layer;

	info.spriteID = this->sprite_id;
	GraphicManager::Draw(info, view_id);
}


unsigned Background::GetView()
{
	return view_id;
}

void Background::Destroy() {
	PTC::sayCreated("Background");
}

bool Background::isToDraw() const {
	return to_draw;
}

void Background::setToDraw(bool toDraw) {
	to_draw = toDraw;
}

Background::~Background() {}
