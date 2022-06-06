#include"Headers/Def.h"
#include"System.h"
#include"Headers/Game.h"
void Main()
{

	mySystem::Initialize();
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	Game game;
	while (System::Update()) {
		game.Update();
	}
	return;
}
