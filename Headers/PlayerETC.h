#pragma once
#include"UI.h"
#include"UIElement.h"
class Player;
class PlayerHPDraw:public UI {
	WPtr<Player> m_player;
	Texture food{ U"❤"_emoji,TextureDesc::Mipped };
public:
	PlayerHPDraw(Stage* _stage, Ptr<Player> _player);
	void Draw() const override;
	void Update() override;
};