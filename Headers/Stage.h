#pragma once
#include"Def.h"
#include"MyCamera.h"
class Actor;
class Stage:public  App::Scene {
	std::set<Ptr<Actor>> actors;
	MyCamera camera;
public:
	friend Actor;
	Stage(const InitData& init);
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
};
