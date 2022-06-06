#pragma once
#include"Def.h"
#include"UpdateComponent.h"
#include"SpriteRenderer.h"
//3*4の画像が動くやつ
//基本はこれ
class Actor;
class BasicSprite :public UpdateComponent{
	const int SPRITE_SPEED = 15;
	int isMoving = 0;//連続して歩いている時間
	GameVec2 m_prev_position;
	bool Left = 0;
	WPtr<Sprite> m_sprite_renderer;
public:
	BasicSprite(Ptr<Actor> _actor);
	void Update() override;
};
