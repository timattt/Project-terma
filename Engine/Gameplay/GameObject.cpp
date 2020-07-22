#pragma once
#include "GameObject.h"

void GameObject::SetID(unsigned new_id)
{
	_ID = new_id;
}

unsigned GameObject::GetID()
{
	return _ID;
}

void GameObject::SetGamefield(GameField* field)
{
	gamefield = field;
}

GameField* GameObject::GetGamefield()
{
	return gamefield;
}

Vector2F GameObject::GetPos()
{
	return _pos;
}

float GameObject::GetRotation()
{
	return _angle;
}

void GameObject::SetTag(const std::string& new_tag)
{
	_tag = new_tag;
}

const std::string& GameObject::GetTag()
{
	return _tag;
}

Vector2F GameObject::GetDirection()
{
	return _basic_direction;
}