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
	if (m_pCell.lock() == 0) {
		return false;//所属しているcellがない
	}
	// 自分を登録している空間に自身を通知
	if (!m_pCell.lock()->OnRemove(weak_from_this().lock()))
		return false;
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
	auto col = m_pObject.lock();
	const float left = col->left, top = col->top, bottom = col->bottom, right = col->right;
	if (weak_from_this().lock() != nullptr) {
		auto p = shared_from_this();
		auto col_man = col_manager.lock();
		if (col_man != nullptr) {
			col_man->Regist(left, top, right, bottom, p);
		}
	}
}
Collision::Collision(float _r, Ptr<CollisionManager> _col_manager, Ptr<Actor> _actor) :DrawComponent(_actor),m_r(_r) {
	mpriority = 0;
	auto colmn_ptr = mactorptr.lock()->GetStage()->col_manager;
	auto this_ptr = weak_from_this().lock();
	if(this_ptr!=nullptr)//コンストラクタの時点では，weak_from_thisが使えない？
		m_CFT = Ptr<CollisionforTree>(new CollisionforTree(this_ptr, colmn_ptr));

}
void Collision::Draw()  {
#ifdef DEBUG1
	auto stage = mactorptr.lock()->GetStage()->GamePositiontoWorldPosition(mactorptr.lock().get()->GetTransform().m_position);
	auto c = Circle(stage.x,stage.y,m_r*Const::TILE_MASU_SIZE);
	c.draw(ColorF(0.1,0.7,0.1,0.3));
	c = Circle(stage.x, stage.y, m_r * Const::TILE_MASU_SIZE*0.5);
	c.draw(ColorF(0.1, 0.7, 0.1, 1.0));
	if (m_CFT != nullptr) {
		auto molton = m_CFT->col_manager.lock()->GetMortonNumber(left, top, right, bottom);
		Print << U"{}_{}"_fmt(mactorptr.lock()->name, molton);
	}
#endif // DEBUG
	UpdateParameter();
	if (m_CFT == nullptr) {
		auto p = weak_from_this().lock();
		if (p != nullptr) {
			auto colmn_ptr = mactorptr.lock()->GetStage()->col_manager;
			m_CFT = Ptr<CollisionforTree>(new CollisionforTree(p, colmn_ptr));
		}
	}
	
	if(m_CFT!=nullptr)
		m_CFT->Update();
}

void Collision::UpdateParameter()  const{
	auto m_pos = mactorptr.lock()->GetTransform().m_position;
	left = m_pos.x - m_r;
	right = m_pos.x + m_r;
	top = m_pos.y + m_r;
	bottom = m_pos.y - m_r;
}
void Collision::Resolution(Ptr<Collision> const& rhs) {
	if (!isValid || !rhs->isValid) {
		return;
	}
	auto l_t = mactorptr.lock()->GetTransform().m_position;
	auto r_t = rhs->GetTransform().m_position;
	auto dist_sq = (l_t.x - r_t.x) * (l_t.x - r_t.x) + (l_t.y - r_t.y) * (l_t.y - r_t.y);
	auto circle_r = rhs->m_r * rhs->m_r + 2 * rhs->m_r * m_r + m_r * m_r;
	if (circle_r <= dist_sq)return;//接触していない
	auto direction = l_t - r_t;
	if (direction.isZero()) {
		direction = { 1,0 };
	}
	direction.normalize();
	direction *= rhs->m_r + m_r;
	mactorptr.lock()->SetTransform(direction + r_t);
	direction = r_t - l_t;
	if (direction.isZero()) {
		direction = { -1,0 };
	}
	direction.normalize();
	direction *= rhs->m_r + m_r;
	rhs->SetTransform(direction + l_t);
}
