#pragma once
#include"Def.h"
#include"MyCamera.h"
#include"Transform.h"
#include"Collision.h"
#include"CollisionManager.h"
#include"Actor.h"
class Actor;
class Stage:public  App::Scene {
	std::set<Ptr<Actor>> actors;
	MyCamera camera;
	int zero = 0;
public:
	Ptr<CollisionManager> col_manager;
	Stage(const InitData& init);
	virtual ~Stage();
	void update() override;
	void draw()const override;
	template<class T>
	inline  Ptr<T> GetComponent() const {//コンポーネントを検索して一番最初にマッチしたものを返す
		Ptr<T> ret;
		for (auto ptr : actors) {
			auto pt = ptr->GetComponent<T>();
			if (pt != nullptr) {
				return pt;
			}
		}
		return ret;
	}
	GameSize GetMapSize() const;
	Vec2 GamePositiontoWorldPosition(Vec2 const& _position) const;
	Ptr<Actor> CreateActor();
	//特定のtypeのアクターをvectorにして返す
	std::vector<WPtr<Actor>> GetActors(ActorType _actor_type);
	inline void AddActor(Ptr<Actor> _actor) { actors.insert(_actor); }

};
