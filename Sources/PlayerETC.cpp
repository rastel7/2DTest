#include"PlayerETC.h"
#include"PlayerComponent.h"
#include"System.h"
PlayerHPDraw::PlayerHPDraw(Stage* _stage, Ptr<Player> _player):UI(_stage),m_player(_player) {
	
}

void PlayerHPDraw::Draw() const {
	auto ptr = m_player.lock();
	if (!ptr)return;
	auto life = ptr->GetLife();
	int x_size = 32;
	float scale = 0.2f;
	const int INIT_Y = x_size / 2, INIT_X = SystemNum::WindowWidth - x_size / 2;
	int y, x;
	y = INIT_Y, x = INIT_X;
	for (int i = 0; i < life.maxlife; ++i) {
		food.scaled(scale).drawAt(Vec2{ x,y }, ColorF(0, 0, 0));
		x -= x_size;
	}
	 y = INIT_Y, x = INIT_X;
	for (int i = 0; i < life.life; ++i) {
		food.scaled(scale).drawAt(Vec2{x,y});
		x -= x_size;
	}
	
}
void PlayerHPDraw::Update() {

}