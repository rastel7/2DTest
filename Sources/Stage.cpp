#include"Stage.h"
#include"Actor.h"
#include"Component.h"
#include"DrawComponent.h"
#include"TileMapRenderer.h"
Stage::Stage(const InitData& init) : IScene{ init },camera(Ptr<Stage>(this)) {
	{
		auto actor = Ptr<Actor>(new Actor(Ptr<Stage>(this)));
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
	camera.Update();
}
void Stage::draw() const {
	const auto transformer = camera.GetCamera().createTransformer();
	for (auto ptr : actors) {
		ptr->Draw();
	}
	Print << U"Camera_Center:{}"_fmt(camera.GetCamera().getCenter());
}

