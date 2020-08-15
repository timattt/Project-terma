#include "StructureBlock.h"

#include "../../Map/Map.h"
#include "Multiblock.h"

class Textures;

StructureBlock::StructureBlock(Multiblock *parent) {
	this->parent = parent;
	setSpriteId(-1);

	FAST_CAST(parent, LightSource, {this->setLightRadius(casted->getLightRadius());})

	this->setPassable(parent->isPassable());
}

void StructureBlock::update() {
}

GameObject* StructureBlock::Clone() const {
	return new StructureBlock(parent);
}