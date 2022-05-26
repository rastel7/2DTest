#pragma once
#include"Def.h"
class Stage;
class MyCamera {
	Ptr<Stage> stage;
	Vec2 camera_center;
	Camera2D camera;
public:
	MyCamera(Ptr<Stage> _stage);
	void Update();
	Camera2D GetCamera() const;
};
