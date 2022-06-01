#include"Collision.h"
#include"Actor.h"
#include"Stage.h"
#include"CollisionManager.h"
Collision::Collision(GameSize _size,bool _isStatic,Ptr<Actor> _ptr):DrawComponent(_ptr) ,m_size(_size),m_isStatic(_isStatic), this_col(this) {
	mpriority = 100;
	m_col_id = collision_id_manager.GetID();
	Ptr<Component> upd= Ptr<Component>( new CollisionUpdater(this_col,mactorptr));
	this_updater = std::dynamic_pointer_cast<CollisionUpdater>(upd);
	mactorptr->AddComponent(upd);
	mactorptr->GetStage()->collisionmanager.AddCollision(WPtr<Collision>(this_col));
	col_parameter.stage_size = mactorptr->GetStage()->GetMapSize();
	col_parameter.m_col_id = m_col_id;
	col_parameter.m_size = m_size;
	col_parameter.Update();
}
Collision::~Collision() {
	collision_id_manager.ReturnID(m_col_id);
	mactorptr->GetStage()->collisionmanager.EraseCollision(WPtr<Collision>(this_col));
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
	col_parameter.transform = GetTransform();
}
CollisionParameter Collision::GetCollisionParameter() const {
	return col_parameter;
}


CollisionParameter Collision::GetLargeCollisionParameter() const {
	auto tmp = col_parameter;
	tmp.m_size *= 1.5f;
	return tmp;
}


CollisionParameter::LeftUpandBottomDown CollisionParameter::GetLeftandBottom() const {
	auto ret = CollisionParameter::LeftUpandBottomDown{ transform.m_position.x - (float)m_size.x / 2.0f,transform.m_position.y + (float)m_size.y / 2.0f, transform.m_position.x + (float)m_size.x / 2.0f, transform.m_position.y - (float)m_size.y / 2.0f, };
	return ret;
}
std::vector<CollisionParameter::LeftUpandBottomDown> CollisionParameter::GetCorrectionLB(LeftUpandBottomDown const& lb)const {
	using LB = CollisionParameter::LeftUpandBottomDown;
	std::vector<LB> check_list = { lb };
	//判定が領域外に出ている場合，それに対応してズラしたコリジョンを判定に加える
	if (lb.lx < 0) {
		auto tmp = lb;
		tmp.lx += stage_size.x;
		tmp.rx += stage_size.x;
		check_list.emplace_back(tmp);
	}
	if (lb.rx > stage_size.x) {
		Print << U"HOGE";
		auto tmp = lb;
		tmp.lx -= stage_size.x;
		tmp.rx -= stage_size.x;
		check_list.emplace_back(tmp);
	}
	if (lb.ly > stage_size.y) {
		auto tmp = lb;
		tmp.ly -= stage_size.y;
		tmp.ry -= stage_size.y;
		check_list.emplace_back(tmp);
	}
	if (lb.ry < 0) {
		auto tmp = lb;
		tmp.ly += stage_size.y;
		tmp.ry += stage_size.y;
		check_list.emplace_back(tmp);
	}
	return check_list;
}
bool CollisionParameter::isHit(CollisionParameter const& r) const {
	using LB = CollisionParameter::LeftUpandBottomDown;
	auto l_ub = this->GetLeftandBottom();
	auto r_ub = r.GetLeftandBottom();
	std::vector<LB> check_list = GetCorrectionLB(l_ub);
	bool ret = false;
	auto check = [](LB const& l_ub, LB const& r_ub) {
		if (l_ub.rx < r_ub.lx)return false;
		if (l_ub.lx > r_ub.rx)return false;
		if (l_ub.ly < r_ub.ry)return false;
		if (l_ub.ry > r_ub.ly)return false;
		return true;
	};
	for (auto const& l : check_list) {
		ret |= check(l, r_ub);
	}
	return ret;
}
GameSize CollisionParameter::GetMinBounds(CollisionParameter const& r) const {
	using LB = CollisionParameter::LeftUpandBottomDown;
	GameSize ret{0,0};
	float min = 1e9;
	auto l_ub = this->GetLeftandBottom();
	auto r_ub = r.GetLeftandBottom();
	auto make_mod = [&](LB& x) {
		x.lx = fmod((x.lx + stage_size.x) , stage_size.x);
		x.rx = fmod((x.rx + stage_size.x), stage_size.x);
		x.ly = fmod((x.ly + stage_size.y), stage_size.y);
		x.ry = fmod((x.ry + stage_size.y), stage_size.y);
	};
	//make_mod(l_ub);
	//make_mod(r_ub);
	for (auto const& l_b : GetCorrectionLB(l_ub)) {
		{//上
			float abs = Abs(l_b.ly - r_ub.ry);
			if (abs < min) {
				min = abs;
				ret = GameSize(0.0, l_b.ly - r_ub.ry);
			}
		}
		{//下
			float abs = Abs(l_b.ry - r_ub.ly);
			if (abs < min) {
				min = abs;
				ret = GameSize(0.0, l_b.ry - r_ub.ly);
			}
		}
		{//左
			float abs = Abs(l_b.lx - r_ub.rx);
			if (abs < min) {
				min = abs;
				ret = GameSize(l_b.lx - r_ub.rx, 0.0);
			}
		}
		{//右
			float abs = Abs(l_b.rx - r_ub.lx);
			if (abs < min) {
				min = abs;
				ret = GameSize(l_b.rx - r_ub.lx, 0.0);
			}
		}
	}
	return ret;
}
CollisionUpdater::CollisionUpdater(WPtr<Collision> _collision_ptr,Ptr<Actor> _actor) :UpdateComponent(_actor),m_collision_ptr(_collision_ptr) {

}

bool CollisionUpdater::isHit(CollisionParameter const& l, CollisionParameter const& r) const {
	return l.isHit(r);
}
void CollisionUpdater::Update() {
}
void CollisionUpdater::SolutionOverlapping(WPtr<Collision>  r_wptr) {
	return;
	auto l = m_collision_ptr.lock();
	auto r = r_wptr.lock();
	if (l->IsStatic()) {
		if (!(r->IsStatic())) {
			r->Get_this_updater().lock()->SolutionOverlapping(m_collision_ptr.lock());
		}
		return;
	}
	if (l->GetColID() == r->GetColID())return;//同じコリジョン
	CollisionParameter this_col_param = l->GetCollisionParameter();
	if (!isHit(this_col_param, r->GetCollisionParameter()))return;
	GameSize bound = this_col_param.GetMinBounds(r->GetCollisionParameter());
	Transform transform = GetTransform();
	transform.m_position -= bound;
	mactorptr->SetTransform(transform);
	this_col_param = l->GetCollisionParameter();
}
void CollisionParameter::Update() {
	lubd.lx = transform.m_position.x - m_size.x/2.0f;
	lubd.rx = lubd.lx + m_size.x;
	lubd.ly = transform.m_position.y + m_size.y / 2.0f;
	lubd.ry = lubd.ly + m_size.y;
}
