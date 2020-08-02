#include "MainMenuScene.h"

#include "../Menu/Buttons/PlayButton.h"
#include "../Menu/Buttons/QuitButton.h"
#include "../Menu/ImageWidgets/Background.h"
#include "../Textures.h"
#include "../../Engine/SceneManagment/SceneManager.h"
#include "../../Engine/Control/InputManager.h"

#include <iostream>

MainMenuScene::MainMenuScene() {}

void MainMenuScene::Init()
{
	//! Initializing the background
	Background* background = new Background();
	background->Init(nullptr);
	background->setScene(this);
	background->setSpriteID(Textures::TEST_BACKGROUND);
	widgets.push_back(background);

	//! Initializing the button that leads to the gameplay scene
	PlayButton* play_button = new PlayButton();
	play_button->Init(nullptr);
	play_button->setScene(this);
	play_button->setScalPos({0.5, 0.5});
	play_button->setSpriteID(Textures::MAIN_MENU_PLAY_BUTTON);
	widgets.push_back(play_button);

	//! Initializing the button that leads to the gameplay scene
	QuitButton* quit_button = new QuitButton();
	quit_button->Init(nullptr);
	quit_button->setScene(this);
	quit_button->setScalPos({0.5, 0.75});
	quit_button->setSpriteID(Textures::MAIN_MENU_QUIT_BUTTON);
	widgets.push_back(quit_button);
}

void MainMenuScene::Update()
{
	for (auto widget : widgets) {
		widget->Update();
	}
	for (auto widget : widgets) {
		widget->Draw();
	}

	Vector2F pos = GraphicManager::ConvertRealToView(InputManager::GetMousePos(), Views::TEST);

	printf("%g; %g\n", pos.x, pos.y);

	// It is in the end of this function for gentle change of scene
	if (!is_active){
		SceneManager::CloseScene(this);
		return ;
	}
}

void MainMenuScene::Destroy()
{
	for (auto widget : widgets) {
		widget->Destroy();
		delete widget;
	}
	widgets.clear();

	printf("MainMenuScene destroyed!\n");
	std::cout.flush();
}