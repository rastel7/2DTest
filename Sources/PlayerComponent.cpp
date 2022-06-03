#include"PlayerComponent.h"
#include"Actor.h"
#include"SpriteRenderer.h"
#include"Collision.h"
#include"Stage.h"
Player::Player(Transform _transform, Ptr<Actor> _ptr):UpdateComponent(_ptr) {
	mactorptr.lock()->name = U"Player";
	if (auto ptr = mactorptr.lock()) {
		ptr->SetTransform(_transform);
		ptr->AddComponent(Ptr<Component>(new Sprite(U"Chara", 48, 64, ptr)));
		ptr->AddComponent(std::make_shared<Collision>(0.7f, mactorptr.lock()->GetStage()->col_manager, ptr));
	}

}

void Player::Update() {
	SetComponents();
	Move();
	UpdatePlayerGraphics();
}

void Player::Move() {
	Ptr<Actor> ptr = mactorptr.lock();
	Transform transform = ptr->GetTransform();
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
	
	ptr->SetTransform(transform);
	Print << transform.m_position;
	if (doMove) {
		m_prop.MovingTime++;
	}
	else {
		m_prop.MovingTime = 0;
	}
}
void Player::SetComponents() {
	if (m_player_sprite == nullptr) {
		m_player_sprite = mactorptr.lock()->GetComponent<Sprite>();
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
