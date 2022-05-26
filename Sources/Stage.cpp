#include"Stage.h"
#include"Actor.h"
#include"Component.h"
#include"DrawComponent.h"
#include"TileMapRenderer.h"
#include"SpriteRenderer.h"
#include"PlayerComponent.h"
#include"Transform.h"
Stage::Stage(const InitData& init) : IScene{ init },camera(this) {
	
	{
		auto actor = Ptr<Actor>(new Actor(Ptr<Stage>(this)));
		actor->AddComponent(Ptr<Component>(new TileMap(U"TestStage",Ptr<Actor>(actor))));
		actors.insert(actor);
	}
	{
		auto actor = Ptr<Actor>(new Actor(Ptr<Stage>(this)));
		actor->AddComponent(Ptr<Component>(new Sprite(U"Chara", 42, 64, actor)));
		actor->AddComponent(Ptr<Player>(new Player(Transform(0,0), actor)));
		actors.insert(actor);
	}
	
}

void Stage::update() {
	for (auto ptr : actors) {
		ptr->Update();
	}
	if (inputmanager.GetEdgePressed(PadButtonNumber::Jump)) {
		System::Exit();
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

Vec2 Stage::GamePositiontoWorldPosition(Vec2 const& _position) const {
	Vec2 ret{0,0};
	ret.x = _position.x * Const::TILE_MASU_SIZE;
	ret.y -= _position.y * Const::TILE_MASU_SIZE;
	return ret;
}
Stage::~Stage() {//なぜか二回呼ばれてる
	Logger << U"Stage::~Stage():{}"_fmt(zero);
	zero++;
	actors.clear();
}

