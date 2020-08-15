#include "MainMenuScene.h"

#include <cstdio>
#include <iostream>
#include <vector>

#include "../../Engine/Control/InputManager.h"
#include "../../Engine/SceneManagment/SceneManager.h"
#include "../../Engine/Time/TimeManager.h"
#include "../../Engine/Utility/Coordinate.h"
#include "../Menu/Buttons/MenuLevelEditorButton.h"
#include "../Menu/Buttons/OptionsButton.h"
#include "../Menu/Buttons/PlayButton.h"
#include "../Menu/Buttons/QuitButton.h"
#include "../Menu/ImageWidgets/Background.h"
#include "../Textures.h"
#include "../Views.h"

MainMenuScene::MainMenuScene() {
	_delay = 0;
}

void MainMenuScene::Init() {
	widgets = new std::vector<MenuWidget*>;

	//! Initializing the background
	Background *background = new Background();
	background->Init(nullptr);
	background->setScene(this);
	background->setSpriteID(Textures::TEST_BACKGROUND);
	background->SetSize(Vector2F(2000, 1000));
	background->SetPos(Vector2F(1000, 500));
	background->SetView(Views::MAIN_MENU);
	widgets->push_back(background);

	//! Initializing the button that leads to the gameplay scene
	PlayButton *play_button = new PlayButton();
	play_button->Init(nullptr);
	play_button->setScene(this);
	play_button->setSpriteID(Textures::MAIN_MENU_PLAY_BUTTON);
	play_button->SetPos( { 800, 600 });
	play_button->SetSize( { 512, 128 });
	play_button->SetView(Views::MAIN_MENU);
	play_button->SetGap( { 0, 0 });
	widgets->push_back(play_button);

	//! Initializing the button that exits
	QuitButton *quit_button = new QuitButton();
	quit_button->Init(nullptr);
	quit_button->setScene(this);
	quit_button->setSpriteID(Textures::MAIN_MENU_QUIT_BUTTON);
	quit_button->SetPos( { 800, 200 });
	quit_button->SetSize( { 490, 190 });
	quit_button->SetGap( { 10, 10 });
	quit_button->SetView(Views::MAIN_MENU);
	widgets->push_back(quit_button);

	//! Initializing the button that leads to the settings scene
	OptionsButton *options_button = new OptionsButton();
	options_button->Init(nullptr);
	options_button->setScene(this);
	options_button->setSpriteID(Textures::MAIN_MENU_OPTIONS_BUTTON);
	options_button->SetPos( { 800, 400 });
	options_button->SetSize( { 760, 230 });
	options_button->SetGap( { 70, 50 });
	options_button->SetView(Views::MAIN_MENU);
	widgets->push_back(options_button);

	//! Initializing the level editor button
	MenuLevelEditorButton* menu_level_editor_button = new MenuLevelEditorButton();
	menu_level_editor_button->Init(nullptr);
	menu_level_editor_button->setScene(this);
	menu_level_editor_button->setSpriteID(Textures::MAIN_MENU_EDITOR);
	menu_level_editor_button->SetPos({800, 800});
	menu_level_editor_button->SetSize({400, 200});
	menu_level_editor_button->SetGap({20, 27});
	menu_level_editor_button->SetView(Views::MAIN_MENU);
	widgets->push_back(menu_level_editor_button);
}

void MainMenuScene::Update() {
	_delay += TimeManager::GetDeltaTime();

	updateWidgets();
	drawWidgets();

	if (InputManager::IsPressed(KeyboardKey::BACK) && _delay > 1000000) {
		SceneManager::CloseScene(this);
		return;
	}

	// It is in the end of this function for gentle change of scene
	if (!is_active) {
		SceneManager::CloseScene(this);
		return;
	}
}

void MainMenuScene::Destroy() {
	destroyWidgets();

	printf("MainMenuScene destroyed!\n");
	std::cout.flush();
}
