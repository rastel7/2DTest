#pragma once
#include"Def.h"
class Actor;
class Stage:public  App::Scene {
	std::set<Ptr<Actor>> actors;
public:
	Stage(const InitData& init);
	void update() override;
	void draw()const override;
};
