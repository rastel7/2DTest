#include"Game.h"
#include"Title.h"
#include"Stage.h"
Game::Game() {
	manager.add<Title>(U"Title");
	manager.add<Stage>(U"Stage");
}

bool Game::Update() {
	ClearPrint();
	inputmanager.Update();
	inputmanager.DebugDraw();
	manager.update();
	return true;
}
