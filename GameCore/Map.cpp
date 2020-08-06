#include "Map.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <type_traits>

#include "../Engine/Colliders/Collider.h"
#include "../Engine/Colliders/SquareCollider.h"
#include "../Engine/Graphics/DrawData.h"
#include "../Engine/Graphics/GraphicManager.h"
#include "../Engine/Utility/Coordinate.h"
#include "Blocks/DirtBlock.h"
#include "Blocks/GrassBlock.h"
#include "Blocks/multiblockStructures/Multiblock.h"
#include "Blocks/multiblockStructures/StructureBlock.h"
#include "Blocks/multiblockStructures/Tree.h"
#include "Level.h"
#include "player/Player.h"
#include "Textures.h"

class Multiblock;

void Map::setLevel(Level *level) {
	this->level = level;
}

Level* Map::getLevel() {
	return this->level;
}

void Map::addBlock(Vector2I pos, Block *block) {
	this->blocks[pos.x][pos.y] = block;
}

template<typename T>
void Map::collectEntities(void inv(T *ent)) {
	for (int i = 0; i < this->entities.size(); i++) {
		if (dynamic_cast<T>(entities[i]) != NULL) {
			inv(entities[i]);
		}
	}
}

void Map::Init() {
	this->level->generate(this);
	this->player = new Player();
	this->addEntity( { 1500, 800 }, this->player);

	// WIREFRAME
	for (int x = 0; x < MAX_LEVEL_SIZE; x++) {
		for (int y = 0; y < MAX_LEVEL_SIZE; y++) {
			colliders_wireframe[x][y] = new SquareCollider();
			colliders_wireframe[x][y]->Init(NULL, Vector2F(x, y) * BLOCK_SIZE,
					Vector2F(1, 1) * BLOCK_SIZE);
		}
	}

	genTestStuff();
}

void Map::Update() {
	if (!is_paused) {
		updateBlocks();
		updateEntities();
	}

	drawBackground();
	drawWallblocks();
	drawBlocks();
	drawEntities();
	drawMultiblocks();
}

void Map::Destroy() {
}

void Map::addEntity(Vector2F pos, Entity *entity) {
	entity->SetPos( { pos.x, pos.y });
	entity->setMap(this);
	this->entities.push_back(entity);
}

Block* Map::getBlockFromMesh(Vector2I pos) {
	return blocks[pos.x][pos.y];
}

void Map::removeEntity(Entity *entity) {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		if (entity == *it) {
			entities.erase(it);
			return;
		}
	}
}

template<typename Base, typename T> inline bool Map::instanceof(const T*) {
	return std::is_base_of<Base, T>::value;
}

/*

 Y
 ^
 |
 |
 |		          +-----* (x1, y1)
 |                |BLOCK|
 |	     	      |     |
 y*       (x0, y0) *-----+
 |
 |
 |
 +----------------*-----------------> X
 |		          x
 |


 */
//! ������ �����, ����� ���������� � ������� ����������� ����.
void Map::drawBlocks() {
	View *camera = this->player->getCamera();
	int total = 0;
	for (int x = (camera->virtual_position.x - camera->virtual_size.x / 2)
			/ BLOCK_SIZE - 1;
			x
					< (camera->virtual_position.x + camera->virtual_size.x / 2)
							/ BLOCK_SIZE + 1; x++) {
		for (int y = (camera->virtual_position.y - camera->virtual_size.y / 2)
				/ BLOCK_SIZE - 1;
				y
						< (camera->virtual_position.y
								+ camera->virtual_size.y / 2) / BLOCK_SIZE + 1;
				y++) {
			if (x < 0 || x >= MAX_LEVEL_SIZE || y < 0 || y >= MAX_LEVEL_SIZE) {
				continue;
			}

			Block *currBlock = blocks[x][y];

			if (!currBlock) {
				continue;
			}
			if (dynamic_cast<Multiblock*>(currBlock) != NULL) {
				continue;
			}

			total++;

			float x0 = x * BLOCK_SIZE;
			float y0 = y * BLOCK_SIZE;

			float x1 = (x + 1) * BLOCK_SIZE;
			float y1 = (y + 1) * BLOCK_SIZE;

			DrawData info = { };
			info.position.x = (x0 + x1) / 2;
			info.position.y = (y0 + y1) / 2;

			info.size.x = BLOCK_SIZE;
			info.size.y = BLOCK_SIZE;

			info.origin = { 0.5, 0.5 };

			info.frame = 0;
			info.layer = 0;

			info.color.b = info.color.r = info.color.g = 255
					* currBlock->getLightLevel();

			info.spriteID = currBlock->getSpriteId();
			GraphicManager::Draw(info, Views::PLAYER_CAM);
		}
	}
}

void Map::drawEntities() {
	for (Entity *ent : entities) {
		ent->Draw();
	}
}

void Map::drawBackground() {
	DrawData info = { };
	info.position.x = player->GetPos().x;
	info.position.y = player->GetPos().y;

	info.size.x = 2000;
	info.size.y = 1000;

	info.origin = { 0.5, 0.5 };

	info.frame = 0;
	info.layer = 0;

	info.spriteID = Textures::TEST_BACKGROUND;
	GraphicManager::Draw(info, Views::PLAYER_CAM);
}

void Map::updateBlocks() {
	View *camera = this->player->getCamera();
	int total = 0;
	for (int x = (camera->virtual_position.x - camera->virtual_size.x / 2)
			/ BLOCK_SIZE - 1;
			x
					< (camera->virtual_position.x + camera->virtual_size.x / 2)
							/ BLOCK_SIZE + 1; x++) {
		for (int y = (camera->virtual_position.y - camera->virtual_size.y / 2)
				/ BLOCK_SIZE - 1;
				y
						< (camera->virtual_position.y
								+ camera->virtual_size.y / 2) / BLOCK_SIZE + 1;
				y++) {
			if (x < 0 || x >= MAX_LEVEL_SIZE || y < 0 || y >= MAX_LEVEL_SIZE) {
				continue;
			}
			if (blocks[x][y]) {
				blocks[x][y]->Update();
			}
		}
	}
}

void Map::genTestStuff() {
	for (int x = 0; x < MAX_LEVEL_SIZE; x++) {
		for (int y = 0; y < MAX_LEVEL_SIZE; y++) {
			addWallblock( { x, y }, new DirtBlock());
		}
	}
	for (int y = 0; y < 14; y++) {
		for (int x = 0; x < MAX_LEVEL_SIZE; x++) {
			addBlock( { x, y }, new DirtBlock());
		}
	}
	for (int y = 10; y < 14; y++) {
		for (int x = 0; x < MAX_LEVEL_SIZE; x++) {
			int token = rand() % 3;
			if (token == 1 || token == 2)
				addBlock( { x, y }, new GrassBlock());
		}
	}
	for (int y = 13; y < 14; y++) {
		for (int x = 0; x < MAX_LEVEL_SIZE; x++) {
			addBlock( { x, y }, new GrassBlock());
		}
	}

	// TREES
	for (int x = 0; x < MAX_LEVEL_SIZE - 20; x++) {
		if (x % 15 == 1) {
			addMultiblock( { x, 14 }, new Tree());
		}
	}

	for (int x = 0; x < MAX_LEVEL_SIZE; x += 20) {
		for (int y = 0; y < MAX_LEVEL_SIZE; y++) {
			if (blocks[x][y] == NULL) {
				//addBlock( { x, y }, new DirtBlock());
			}
		}
	}

//addEntity( { 600, 500 }, new RedStar());
}

float Map::testCollision(SquareCollider *col, Vector2F dir) {
	Vector2F bl_sz = { BLOCK_SIZE / 2, BLOCK_SIZE / 2 };

	float dir_len = dir.Magnitude();
	float result = 10000000.0f;

	for (int y = (col->getPos().y - 1 * col->getSize().y - dir_len) / BLOCK_SIZE
			- 1;
			y
					< (col->getPos().y + 1 * col->getSize().y + dir_len)
							/ BLOCK_SIZE + 1; y++) {
		for (int x = (col->getPos().x - 1 * col->getSize().x - dir_len)
				/ BLOCK_SIZE - 1;
				x
						< (col->getPos().x + 1 * col->getSize().x + dir_len)
								/ BLOCK_SIZE + 1; x++) {

			if (x < 0 || x >= MAX_LEVEL_SIZE || y < 0 || y >= MAX_LEVEL_SIZE) {
				continue;
			}

			if (blocks[x][y] == NULL) {
				continue;
			}
			if (blocks[x][y]->isPassable()) {
				continue;
			}

			// DEBUG
			//------------------------------
			//Debugger::DrawSquareCollider(bl, 10, 4, Views::PLAYER_CAM);
			//Debugger::DrawLine(bl.getPos(), col->getPos(), 4, Views::PLAYER_CAM,
			//		Color::Red());
			//------------------------------

			float dist = Collider::DistanceBetween(col,
					colliders_wireframe[x][y], dir);

			if (!std::isnan(dist)) {
				if (dist >= 0.0f) {
					result = std::min(result, dist);
				}
			}
		}
	}

	return result;
}

void Map::drawMultiblocks() {
	View *camera = this->player->getCamera();
	for (int x = (camera->virtual_position.x - camera->virtual_size.x / 2)
			/ BLOCK_SIZE - 1 - MAX_MULTIBLOCK_STRUCTURE_SEARCH_RADIUS;
			x
					< (camera->virtual_position.x + camera->virtual_size.x / 2)
							/ BLOCK_SIZE + 1
							+ MAX_MULTIBLOCK_STRUCTURE_SEARCH_RADIUS; x++) {
		for (int y = (camera->virtual_position.y - camera->virtual_size.y / 2)
				/ BLOCK_SIZE - 1 - MAX_MULTIBLOCK_STRUCTURE_SEARCH_RADIUS;
				y
						< (camera->virtual_position.y
								+ camera->virtual_size.y / 2) / BLOCK_SIZE + 1
								+ MAX_MULTIBLOCK_STRUCTURE_SEARCH_RADIUS; y++) {
			if (x < 0 || x >= MAX_LEVEL_SIZE || y < 0 || y >= MAX_LEVEL_SIZE) {
				continue;
			}

			Block *currBlock_ = blocks[x][y];

			if (!currBlock_) {
				continue;
			}
			if (dynamic_cast<Multiblock*>(currBlock_) == NULL) {
				continue;
			}

			Multiblock *currBlock = (Multiblock*) currBlock_;

			DrawData info = { };
			info.position =
					(Vector2F(x, y) + 0.5f * currBlock->getSize().to2F())
							* BLOCK_SIZE;

			info.size = (float) (BLOCK_SIZE) * currBlock->getSize().to2F();

			info.origin = { 0.5, 0.5 };

			info.frame = 0;
			info.layer = 0;

			info.spriteID = currBlock->getSpriteId();
			GraphicManager::Draw(info, Views::PLAYER_CAM);
		}
	}
}

void Map::addMultiblock(Vector2I pos, Multiblock *block) {
	addBlock(pos, block);
	for (int x = 0; x < block->getSize().x; x++) {
		for (int y = 0; y < block->getSize().y; y++) {
			if (x == 0 && y == 0) {
				continue;
			}
			addBlock( { pos.x + x, pos.y + y }, new StructureBlock(block));
		}
	}
}

void Map::pauseGame() {
	is_paused = true;
}

void Map::unpauseGame() {
	is_paused = false;
}

bool Map::isPaused() {
	return is_paused;
}

void Map::addWallblock(Vector2I pos, Block *block) {
	this->wallblocks[pos.x][pos.y] = block;
}

void Map::updateEntities() {
	for (Entity *ent : entities) {
		ent->Update();
	}
}

void Map::drawWallblocks() {
	View *camera = this->player->getCamera();
	int total = 0;
	for (int x = (camera->virtual_position.x - camera->virtual_size.x / 2)
			/ BLOCK_SIZE - 1;
			x
					< (camera->virtual_position.x + camera->virtual_size.x / 2)
							/ BLOCK_SIZE + 1; x++) {
		for (int y = (camera->virtual_position.y - camera->virtual_size.y / 2)
				/ BLOCK_SIZE - 1;
				y
						< (camera->virtual_position.y
								+ camera->virtual_size.y / 2) / BLOCK_SIZE + 1;
				y++) {
			if (x < 0 || x >= MAX_LEVEL_SIZE || y < 0 || y >= MAX_LEVEL_SIZE) {
				continue;
			}

			Block *currBlock = wallblocks[x][y];

			if (!currBlock) {
				continue;
			}
			if (dynamic_cast<Multiblock*>(currBlock) != NULL) {
				continue;
			}

			total++;

			float x0 = x * BLOCK_SIZE;
			float y0 = y * BLOCK_SIZE;

			float x1 = (x + 1) * BLOCK_SIZE;
			float y1 = (y + 1) * BLOCK_SIZE;

			DrawData info = { };
			info.position.x = (x0 + x1) / 2;
			info.position.y = (y0 + y1) / 2;

			info.size.x = BLOCK_SIZE;
			info.size.y = BLOCK_SIZE;

			info.origin = { 0.5, 0.5 };

			info.frame = 0;
			info.layer = 0;

			info.color.b = info.color.r = info.color.g = 255.0f
					* currBlock->getLightLevel() * 0.5f;

			info.spriteID = currBlock->getSpriteId();
			GraphicManager::Draw(info, Views::PLAYER_CAM);
		}
	}
}
