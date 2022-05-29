#pragma once
#include"Def.h"
#include"MyCamera.h"
#include"Transform.h"
#include"Collision.h"
#include"CollisionManager.h"
class Actor;
class Stage:public  App::Scene {
	std::set<Ptr<Actor>> actors;
	MyCamera camera;
	int zero = 0;
public:
	CollisionManager collisionmanager;
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
	std::vector<CollisionParameter> GetCollisionParameters() const;
	std::vector<Ptr<Collision>> GetCollisions() const;
	Vec2 GamePositiontoWorldPosition(Vec2 const& _position) const;
	inline void AddActor(Ptr<Actor> _actor) { actors.insert(_actor); }
};
