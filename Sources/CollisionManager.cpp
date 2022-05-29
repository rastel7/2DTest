#include"CollisionManager.h"
#include"Stage.h"
void CollisionManager::Update() {
	colls.clear();
	auto coll_ = stage->GetCollisions();
	for (auto c : coll_) {
		//左端の座標をfirstとする．
		auto GetLeftX = [](CollisionParameter param) {return param.transform.m_position.x - param.m_size.x/2.0f; };
		colls.emplace_back(std::make_pair(GetLeftX(c->GetCollisionParameter()),c));
	}
	//コリジョンの左端の基準に昇順ソートする
	std::sort(colls.begin(), colls.end(), [](const std::pair<double, Ptr<Collision>>& l, const std::pair<double, Ptr<Collision>>& r) {
		return l.first < r.first;
	});
	
}

std::vector<Ptr<Collision>> CollisionManager::GetNearCollision(Ptr<Collision> col) const {
	std::vector<Ptr<Collision>> ret;
	auto prev_size = col->GetSize();
	//col->SetSize(prev_size * 1.5f);//一時的にコリジョンを大きくする
	auto GetRightX = [](CollisionParameter param) {return param.transform.m_position.x + param.m_size.x/2.0f; };
	auto make_t = std::make_pair(GetRightX(col->GetCollisionParameter()), col);
	auto itr = std::upper_bound(colls.begin(), colls.end(), make_t, [](const std::pair<double, Ptr<Collision>>& l, const std::pair<double, Ptr<Collision>>& r) {
		return l.first < r.first;
	});
	Print << U"CollStart:{}"_fmt(itr - colls.begin());
	col->SetSize(prev_size);//大きさを戻す
	auto l_param = col->GetCollisionParameter();
	bool checkedStart = false;
	if (itr == colls.end()) {
		itr--;
	}
	auto start = itr;
	while (true) {
		//ループしている
		
		if (start == itr&& checkedStart) {
			break;
		}
		
		checkedStart = true;
		//採用するかどうかの判断
		auto ptr = (*itr).second;
		auto param = ptr->GetCollisionParameter();
		auto dist1 = std::abs(l_param.transform.m_position.x-param.transform.m_position.x);
		auto dist2 = std::abs(dist1 - stage->GetMapSize().x);
		auto left = param.transform.m_position.x - param.m_size.x;
		
		if (l_param.m_size.x/2.0+param.m_size.x/2.0 < std::min<float>(dist1,dist2)) {
			if (l_param.transform.m_position.x > param.transform.m_position.x) {
				break;
			}
		}
		else {
			ret.emplace_back((*itr).second);
		}
	
		if (itr == colls.begin()) {
			itr = colls.end();
		}
		itr--;
	}
	itr = start; checkedStart = 0;
	while (true) {
		//ループしている

		if (start == itr && checkedStart) {
			break;
		}

		checkedStart = true;
		//採用するかどうかの判断
		auto ptr = (*itr).second;
		auto param = ptr->GetCollisionParameter();
		auto dist1 = std::abs(l_param.transform.m_position.x - param.transform.m_position.x);
		auto dist2 = std::abs(dist1 - stage->GetMapSize().x);
		auto left = param.transform.m_position.x - param.m_size.x;

		if ((l_param.m_size.x / 2.0 + param.m_size.x / 2.0)*1.2f < std::min<float>(dist1, dist2)) {
				break;
		}
		else {
			ret.emplace_back((*itr).second);
		}

		itr++;
		if (itr == colls.end()) {
			itr = colls.begin();
		}
	}

	Print << U"CollEnd:{}"_fmt(itr - colls.begin());
	return ret;
}

bool CollisionManager::Cmp(const Ptr<Collision> & l,const Ptr<Collision> & r) {
	auto l_param = l->GetCollisionParameter();
	auto r_param = r->GetCollisionParameter();
	auto GetLeftX = [](CollisionParameter param) {return param.transform.m_position.x + param.m_size.x; };
	return GetLeftX(l_param) < GetLeftX(r_param);
}
