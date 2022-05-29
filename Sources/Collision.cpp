#include"Collision.h"
#include"Actor.h"
#include"Stage.h"
#include"CollisionManager.h"
Collision::Collision(GameSize _size,bool _isStatic,Ptr<Actor> _ptr):DrawComponent(_ptr) ,m_size(_size),m_isStatic(_isStatic) {
	mpriority = 100;
	m_col_id = collision_id_manager.GetID();
	mactorptr->AddComponent(Ptr<Component>(new CollisionUpdater(mactorptr)));
}
Collision::~Collision() {
	collision_id_manager.ReturnID(m_col_id);
}
void Collision::Draw()const {
#ifdef DEBUG
	{
		auto transform = mactorptr->GetTransform();
		auto stage = mactorptr->GetStage()->GamePositiontoWorldPosition(transform.m_position);
		auto _scale = m_size * Const::TILE_MASU_SIZE;
		Rect(stage.x- _scale.x/2,stage.y- _scale.y/2.0f, (float)_scale.x, (float)_scale.y).draw(ColorF(0.2,0.8,0.2,0.3f));
		Circle(stage.x, stage.y, 3.0f).draw();
	}
#endif // DEBUG

}
CollisionParameter Collision::GetCollisionParameter() const {
	CollisionParameter ret{ m_size,m_col_id,mactorptr->GetTransform() };
	return ret;
}


CollisionParameter Collision::GetLargeCollisionParameter() const {
	CollisionParameter ret{m_size*1.5f,m_col_id,mactorptr->GetTransform()};
	return ret;
}


CollisionParameter::LeftUpandBottomDown CollisionParameter::GetLeftandBottom() const {
	return CollisionParameter::LeftUpandBottomDown{transform.m_position.x-(float)m_size.x/2.0f,transform.m_position.y + (float)m_size.y / 2.0f, transform.m_position.x + (float)m_size.x / 2.0f, transform.m_position.y - (float)m_size.y / 2.0f,};
}
bool CollisionParameter::isHit(CollisionParameter const& r) const {
	auto l_ub = this->GetLeftandBottom();
	auto r_ub = r.GetLeftandBottom();
	if (l_ub.rx < r_ub.lx)return false;
	if (l_ub.lx > r_ub.rx)return false;
	if (l_ub.ly < r_ub.ry)return false;
	if (l_ub.ry > r_ub.ly)return false;
	return true;
}
GameSize CollisionParameter::GetMinBounds(CollisionParameter const& r) const {
	GameSize ret{0,0};
	float min = 1e9;
	auto l_ub = this->GetLeftandBottom();
	auto r_ub = r.GetLeftandBottom();
	{//上
		float abs = Abs(l_ub.ly - r_ub.ry);
		if (abs < min) {
			min = abs;
			ret = GameSize(0.0,l_ub.ly - r_ub.ry);
		}
	}
	{//下
		float abs = Abs(l_ub.ry - r_ub.ly);
		if (abs < min) {
			min = abs;
			ret = GameSize(0.0,l_ub.ry - r_ub.ly);
		}
	}
	{//左
		float abs = Abs(l_ub.lx - r_ub.rx);
		if (abs < min) {
			min = abs;
			ret = GameSize(l_ub.lx - r_ub.rx, 0.0);
		}
	}
	{//右
		float abs = Abs(l_ub.rx - r_ub.lx);
		if (abs < min) {
			min = abs;
			ret = GameSize(l_ub.rx - r_ub.lx, 0.0);
		}
	}
	return ret;
}
CollisionUpdater::CollisionUpdater(Ptr<Actor> _actor) :UpdateComponent(_actor) {

}

bool CollisionUpdater::isHit(CollisionParameter const& l, CollisionParameter const& r) const {
	return l.isHit(r);
}
void CollisionUpdater::Update() {
	Ptr<Collision> colision_ptr = mactorptr->GetComponent<Collision>();
	if (colision_ptr == nullptr) {
		Print << U"コリジョンが見つかりません";
		return;
	}
	//Staticなオブジェクトは動かない
	if (colision_ptr->IsStatic()) {
		return;
	}
	/*前バージョン
	CollisionParameter this_col_param = colision_ptr->GetCollisionParameter();
	std::vector<CollisionParameter> colls = mactorptr->GetStage()->GetCollisionParameters();
	for (auto const& col : colls) {
		if (col.m_col_id == this_col_param.m_col_id)continue;//同じコリジョン
		if (!isHit(this_col_param, col))continue;
		GameSize bound = this_col_param.GetMinBounds(col);
		Transform transform = GetTransform();
		transform.m_position -= bound;
		mactorptr->SetTransform(transform);
		this_col_param = colision_ptr->GetCollisionParameter();
	}
	*/
	std::vector<Ptr<Collision>> nearcolls = mactorptr->GetStage()->collisionmanager.GetNearCollision(colision_ptr);
	Print << U"cool_{}"_fmt(nearcolls.size());
	for (auto const& col : nearcolls) {
		if (colision_ptr->GetColID() == col->GetColID())continue;//同じコリジョン
		CollisionParameter this_col_param = colision_ptr->GetCollisionParameter();
		if (!isHit(this_col_param, col->GetCollisionParameter()))continue;
		GameSize bound = this_col_param.GetMinBounds(col->GetCollisionParameter());
		Transform transform = GetTransform();
		transform.m_position -= bound;
		mactorptr->SetTransform(transform);
		this_col_param = colision_ptr->GetCollisionParameter();
	}
}
