#pragma once

#include "Multiblock.h"

class Tree: public Multiblock {
public:
	Tree() :
			Multiblock() {
		setSize({10, 10});
		setSpriteId(Textures::TREE);
		setPassable(1);
	}

	GameObject* clone() const {
		return new Tree();
	}
};