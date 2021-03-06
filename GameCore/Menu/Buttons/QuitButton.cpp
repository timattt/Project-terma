#include "QuitButton.h"

#include <cstdio>

#include "../../PTC.h"
#include "../../Scenes/MainMenuScene.h"

QuitButton::QuitButton() {}

void QuitButton::leftClickReact() {
	MainMenuScene* _scene = dynamic_cast<MainMenuScene*>(current_scene);

	_scene->quitGame();
	_scene->disableScene();
}

void QuitButton::focusReact() {
	//! Nothing for now
}

void QuitButton::Init(GameObject *owner) {
	PTC::sayCreated("QuitButton");
}

void QuitButton::disfocusReact()
{
	// Nothing for now
}

void QuitButton::rightClickReact()
{
	// Nothing for now
}

void QuitButton::Destroy() {
	PTC::sayDestroyed("QuitButton");
}
