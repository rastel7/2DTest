#include"Stage.h"
#include"Actor.h"
#include"Component.h"
#include"DrawComponent.h"
#include"TileMapRenderer.h"
#include"SpriteRenderer.h"
#include"PlayerComponent.h"
#include"Transform.h"

Stage::Stage(const InitData& init) : IScene{ init },camera(this){
	col_manager = Ptr<CollisionManager>( new CollisionManager(this));
	{
		auto actor = Ptr<Actor>(new Actor(this));
		actor->AddComponent(Ptr<Component>(new TileMap(U"TestStage",Ptr<Actor>(actor))));
		actors.insert(actor);
	}
	{
		auto actor = Ptr<Actor>(new Actor(this));
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
	Print << U"ActorCount:{}"_fmt(actors.size());
}
void Stage::draw() const {
	const auto transformer = camera.GetCamera().createTransformer();
	std::vector<Ptr<DrawComponent>> draw_events;
	for (auto ptr : actors) {
		auto vec= ptr->Draw();
		std::copy(vec.begin(), vec.end(), std::back_inserter(draw_events));
	}
	sort(draw_events.begin(), draw_events.end(), [](Ptr<DrawComponent> const& l, Ptr<DrawComponent> const& r){
		return l->GetPriority() < r->GetPriority();
	});
	for (auto draw_component : draw_events) {
		draw_component->Draw();
	}
}

Vec2 Stage::GamePositiontoWorldPosition(Vec2 const& _position) const {
	Vec2 ret{0,0};
	ret.x = _position.x * Const::TILE_MASU_SIZE;
	ret.y -= _position.y * Const::TILE_MASU_SIZE;
	return ret;
}
Stage::~Stage() {
	Logger << U"Stage::~Stage():{}"_fmt(zero);
	zero++;
}



GameSize Stage::GetMapSize() const {
	Ptr<TileMap> stage = GetComponent<TileMap>();
	if (stage == nullptr){
		return GameSize{0,0};
	}
	return stage->GetMapSize();
}
