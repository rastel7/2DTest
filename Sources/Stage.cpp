#include"Stage.h"
#include"Actor.h"
#include"Component.h"
#include"DrawComponent.h"
#include"TileMapRenderer.h"
Stage::Stage(const InitData& init) : IScene{ init } {
	{
		auto actor = Ptr<Actor>(new Actor());
		actor->AddComponent(Ptr<Component>(new TileMap(U"TestStage",Ptr<Actor>(actor))));
		actors.insert(actor);
	}
}

void Stage::update() {
	for (auto ptr : actors) {
		ptr->Update();
	}
	if (inputmanager.GetEdgePressed(PadButtonNumber::Jump)) {
		changeScene(U"Title");
	}
}
void Stage::draw() const {
	for (auto ptr : actors) {
		ptr->Draw();
	}
}
