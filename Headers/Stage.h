#pragma once
#include"Def.h"
#include"MyCamera.h"
#include"Transform.h"
class Actor;
class Stage:public  App::Scene {
	std::set<Ptr<Actor>> actors;
	MyCamera camera;
	int zero = 0;
public:
	Stage(const InitData& init);
	virtual ~Stage();
	void update() override;
	void draw()const override;
	template<class T>
	inline  Ptr<T> GetComponent() {//コンポーネントを検索して一番最初にマッチしたものを返す
		Ptr<T> ret;
		for (auto ptr : actors) {
			auto pt = ptr->GetComponent<T>();
			if (pt != nullptr) {
				return pt;
			}
		}
		return ret;
	}
	Vec2 GamePositiontoWorldPosition(Vec2 const& _position) const;
};
