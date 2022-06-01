#include"Collision.h"
#include"Actor.h"
#include"Stage.h"
#include"CollisionManager.h"

bool CollisionforTree::RegistCell(Ptr<CCell> _p_Cell) {
	if (_p_Cell != nullptr) {
		m_pCell = _p_Cell;
		return true;
	}
	return false;
}
bool CollisionforTree::Remove() {
	if (m_pCell.lock() == nullptr) {
		return false;//所属しているcellがない
	}
	// 自分を登録している空間に自身を通知
	//ToDO
	if (m_spPre.lock() != nullptr) {
		m_spPre.lock()->m_spNext = m_spNext.lock();
	}
	if (m_spNext.lock() != nullptr) {
		m_spNext.lock()->m_spPre = m_spPre.lock();
	}
	m_spPre.reset();
	m_spNext.reset();
	m_pCell.reset();
	return true;
}

void CollisionforTree::Update() {
	Remove();
	m_pObject.lock();
}
Collision::Collision(Ptr<CollisionManager> _col_manager, Ptr<Actor> _actor) :DrawComponent(_actor) {
	mpriority = 999;
	m_CFT = Ptr<CollisionforTree>(new CollisionforTree(shared_from_this(), mactorptr.lock()->GetStage()->col_manager));

}
void Collision::Draw() const {
#ifdef DEBUG
	auto stage = mactorptr.lock()->GetStage()->GamePositiontoWorldPosition(mactorptr.lock().get()->GetTransform().m_position);
	auto c = Circle(stage.x,stage.y,m_r*Const::TILE_MASU_SIZE);
	c.draw(ColorF(0.1,0.7,0.1,0.3));
#endif // DEBUG
	UpdateParameter();
}

void Collision::UpdateParameter()  const{
	auto m_pos = mactorptr.lock()->GetTransform().m_position;
	left = m_pos.x - m_r;
	right = m_pos.x + m_r;
	top = m_pos.y - m_r;
	bottom = m_pos.y + m_r;
}
