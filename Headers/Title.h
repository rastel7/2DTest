﻿#pragma once
#include"Def.h"

class Title : public  App::Scene {
public:
	Title(const InitData& init);
	void update() override;
	void draw()const override;
};
