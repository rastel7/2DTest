#include"PlayerComponent.h"
#include"Actor.h"
#include"SpriteRenderer.h"
#include"Collision.h"
Player::Player(Transform _transform, Ptr<Actor> _ptr):UpdateComponent(_ptr) {
	mactorptr->SetTransform(_transform);
	mactorptr->AddComponent(Ptr<Component>(new Sprite(U"Chara", 48, 64, mactorptr)));
	mactorptr->AddComponent(Ptr<Component>(new Collision(Vec2{ 1.0f, 1.8f }, mactorptr)));
}

void Player::Update() {
	Transform transform = mactorptr->GetTransform();
	if (inputmanager.GetPressed(PadButtonNumber::Up)) {
		transform.m_position.y += 0.05;
	}
	if (inputmanager.GetPressed(PadButtonNumber::Down)) {
		transform.m_position.y -= 0.05;
	}
	if (inputmanager.GetPressed(PadButtonNumber::Left)) {
		transform.m_position.x -= 0.05;
	}
	if (inputmanager.GetPressed(PadButtonNumber::Right)) {
		transform.m_position.x += 0.05;
	}
	Print << transform.m_position;
	mactorptr->SetTransform(transform);
}
