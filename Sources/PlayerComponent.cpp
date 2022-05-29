#include"PlayerComponent.h"
#include"Actor.h"
#include"SpriteRenderer.h"
#include"Collision.h"
#include"Stage.h"
Player::Player(Transform _transform, Ptr<Actor> _ptr):UpdateComponent(_ptr) {
	mactorptr->SetTransform(_transform);
	mactorptr->AddComponent(Ptr<Component>(new Sprite(U"Chara", 48, 64, mactorptr)));
	mactorptr->AddComponent(Ptr<Component>(new Collision(Vec2{ 1.0f, 1.8f },false, mactorptr)));

}

void Player::Update() {
	SetComponents();
	Move();
	UpdatePlayerGraphics();
}

void Player::Move() {
	Transform transform = mactorptr->GetTransform();
	bool doMove = 0;
	if (inputmanager.GetPressed(PadButtonNumber::Up)) {
		transform.m_position.y += 0.05; doMove = 1;
	}
	if (inputmanager.GetPressed(PadButtonNumber::Down)) {
		transform.m_position.y -= 0.05; doMove = 1;
	}
	if (inputmanager.GetPressed(PadButtonNumber::Left)) {
		transform.m_position.x -= 0.05; doMove = 1;
		m_prop.isLeft = true;
	}
	if (inputmanager.GetPressed(PadButtonNumber::Right)) {
		transform.m_position.x += 0.05; doMove = 1;
		m_prop.isLeft = false;
	}
	
	mactorptr->SetTransform(transform);
	if (doMove) {
		m_prop.MovingTime++;
	}
	else {
		m_prop.MovingTime = 0;
	}
}
void Player::SetComponents() {
	if (m_player_sprite == nullptr) {
		m_player_sprite = mactorptr->GetComponent<Sprite>();
	}
}
void Player::UpdatePlayerGraphics() {
	if (m_player_sprite == nullptr)return;
	m_prop.MovingTime %= m_prop.MOVE_SPRITE_PERIOD * 4;
	int id = 0;
	if (m_prop.isLeft == 0) {
		id =3;
	}
	else {
		id = 9;
	}
	int add=0;
	if (m_prop.MovingTime < m_prop.MOVE_SPRITE_PERIOD) {
		add = 1;
	}else if (m_prop.MovingTime < m_prop.MOVE_SPRITE_PERIOD*2) {
		add = 0;
	}
	else if (m_prop.MovingTime < m_prop.MOVE_SPRITE_PERIOD*3) {
		add = 1;
	}
	else {
		add = 2;
	}
	m_player_sprite->SetTextureID((id + add)%12);
}
