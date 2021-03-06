#include "EditorGrid.h"

#include "../../Map/Map.h"
#include "../../PTC.h"
#include "../../Scenes/LevelEditorScene.h"

EditorGrid::EditorGrid() {
}

void EditorGrid::rightClickReact() {
}

void EditorGrid::leftClickReact() {
	LevelEditorScene *_scene = dynamic_cast<LevelEditorScene*>(current_scene);

	_scene->currentMap->setMayDrawGrid(!_scene->currentMap->isMayDrawGrid());
}

void EditorGrid::focusReact() {
}

void EditorGrid::disfocusReact() {
}

void EditorGrid::Destroy()
{
	PTC::sayDestroyed("EditorGrid");
}

void EditorGrid::Init(GameObject *owner)
{
	PTC::sayCreated("EditorGrid");
}

EditorGrid::~EditorGrid() {
}
