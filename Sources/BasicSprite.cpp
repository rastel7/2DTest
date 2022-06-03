#include"BasicSprite.h"
#include"Actor.h"
#include"SpriteRenderer.h"
BasicSprite::BasicSprite(Ptr<Actor> _actor):UpdateComponent(_actor) {
	m_prev_position = mactorptr.lock()->GetTransform().m_position;
	auto sprite = mactorptr.lock()->GetComponent<Sprite>();
	if (sprite != nullptr) {
		m_sprite_renderer = sprite;
	}
}

void BasicSprite::Update() {
	if (m_sprite_renderer.lock() == nullptr) {
		auto sprite = mactorptr.lock()->GetComponent<Sprite>();
		if (sprite != nullptr) {
			m_sprite_renderer = sprite;
		}
		return;
	}
	GameVec2 now_position;
	try {
		auto transform = mactorptr.lock()->GetTransform();
		now_position = transform.m_position;
	}
	catch (...) {
		throw "transformが見つかりません";
	}
	if (now_position == m_prev_position) {
		isMoving = 0;
	}
	else {
		isMoving++;
	}
	if (now_position.x != m_prev_position.x) {
		Left = now_position.x < m_prev_position.x;
	}
	if (isMoving > SPRITE_SPEED * 4) {
		isMoving -= SPRITE_SPEED * 4;
	}
	int id = 0;
	if (Left == 0) {
		id = 3;
	}
	else {
		id = 9;
	}
	int add = 0;
	if (isMoving < SPRITE_SPEED) {
		add = 1;
	}
	else if (isMoving < SPRITE_SPEED * 2) {
		add = 0;
	}
	else if (isMoving < SPRITE_SPEED * 3) {
		add = 1;
	}
	else {
		add = 2;
	}
	m_sprite_renderer.lock()->SetTextureID((id + add) % 12);
}
