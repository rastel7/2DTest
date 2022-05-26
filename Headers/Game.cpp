#include"Game.h"
#include"Title.h"
#include"Stage.h"
Game::Game() {
	//manager.add<Title>(SceneState::Title);
	manager.add<Stage>(SceneState::Stage);
}

void Game::Update() {
	ClearPrint();
	inputmanager.Update();
	inputmanager.DebugDraw();
	manager.update();
}
