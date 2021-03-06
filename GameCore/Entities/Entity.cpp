#include "Entity.h"

#include "../../Engine/Time/TimeManager.h"
#include "../../Engine/Utility/Coordinate.h"
#include "../PTC.h"

void Entity::Destroy() {
}

void Entity::Init(GameObject *owner) {
}

void Entity::setMap( Map *map) {
	this->map = map;
}

Map* Entity::getMap() {
	return this->map;
}

void Entity::Update() {
	float dt = TimeManager::GetDeltaTimeF();

	_pos += dt * speed;
	speed += dt * externalForce;

	externalForce = {0, 0};
}

void Entity::setColliderSize(const Vector2F &colliderSize) {
	collider_size = colliderSize;
}

void Entity::setTextureSize(const Vector2F &textureSize) {
	texture_size = textureSize;
}
