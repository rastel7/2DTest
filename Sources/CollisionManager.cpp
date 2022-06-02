#include"CollisionManager.h"
#include"Stage.h"
CCell::CCell(CollisionManager* _colmanager):m_colmanager(_colmanager) {
	
}
bool CCell::Push(Ptr<CollisionforTree> _ptr){
	if (_ptr == nullptr) return false;//引数がヌルポインタ
	if (_ptr->m_pObject.lock() == 0)return false;//無効なオブジェクト
	if (_ptr->m_pCell.lock().get() == this)return false;//二重登録回避
	if (m_spLatest.lock().get() == nullptr) {
		//先頭がない
		m_spLatest = _ptr;
	}
	else {
		_ptr->m_spNext = m_spLatest;
		m_spLatest.lock()->m_spPre = _ptr;
		m_spLatest = _ptr;
	}
	auto p = shared_from_this();
	//空間を登録
	if (!_ptr->RegistCell(p)) {
		throw "nullptrが渡されています";
	}
	return true;
}

bool CCell::OnRemove(Ptr<CollisionforTree> _remove_obj) {
	if (m_spLatest.lock() == _remove_obj) {
		//次のオブジェクトに変更
		if (m_spLatest.lock() != nullptr) {
			m_spLatest = m_spLatest.lock()->m_spNext.lock();
		}
	
	}
	return true;
}
CollisionManager::CollisionManager(Stage* _stage) :m_stage(_stage), m_iPow(new std::array<unsigned int, CLINER4TREEMANAGER_MAXLEVEL + 1>()) {
	Logger << U"Init_Start";
	GameSize stage_size = m_stage->GetMapSize();
	Init(CLINER4TREEMANAGER_MAXLEVEL-5, 0.0, stage_size.y, stage_size.x, 0.0);
	Logger << U"Init_End";
}
bool CollisionManager::Init(unsigned int Level, float left, float top, float right, float bottom) {
	// 設定最高レベル以上の空間は作れない
	if (Level > CLINER4TREEMANAGER_MAXLEVEL + 1)
		return false;
	//各レベルでの空間数を前計算
	{
		int i = 0;
		m_iPow.get()->at(0)= 1;
		for (int i = 1; i <= CLINER4TREEMANAGER_MAXLEVEL; ++i) {
			m_iPow.get()->at(i) = m_iPow.get()->at(i-1)*4;
		}
	}
	m_dwCellNum = (m_iPow.get()->at(Level + 1) * 4);
	m_cellary = std::make_shared<std::vector<Ptr<CCell>>>(m_dwCellNum);
	for (int i = 0; i < m_dwCellNum; ++i) {
		m_cellary.get()->at(i).reset(new CCell(this));
	}
	// 有効領域を登録
	m_fLeft = left;
	m_fTop = top;
	m_fW = right - left;
	m_fH = bottom-top;
	m_fUnit_W = std::abs(m_fW / (1 << Level));
	m_fUnit_H = std::abs(m_fH / (1 << Level));

	m_uiLevel = Level;

	return true;
}

unsigned int CollisionManager::GetPointElem(float pos_x, float pos_y) const {
	return Get2DMortonNumber((unsigned long)((pos_x - m_fLeft) / m_fUnit_W), (unsigned long)(( m_fTop-pos_y) / m_fUnit_H));
}
unsigned int CollisionManager::Get2DMortonNumber(unsigned int x, unsigned int y) const {
	return (unsigned int)(BitSeparate32(x) | (BitSeparate32(y) << 1));
}
unsigned int CollisionManager::BitSeparate32(unsigned int n) const{
	n = (n | (n << 8)) & 0x00ff00ff;
	n = (n | (n << 4)) & 0x0f0f0f0f;
	n = (n | (n << 2)) & 0x33333333;
	return (n | (n << 1)) & 0x55555555;
}
unsigned long CollisionManager::GetMortonNumber(float left, float top, float right, float bottom) {
	//画面外にでていたらそれを修正
	left = std::max<float>(0.0f, left);
	right = std::min<float>(m_stage->GetMapSize().x, right);
	bottom = std::max<float>(0.0f, bottom);
	top = std::min<float>(m_stage->GetMapSize().y, top);
	unsigned long LT = GetPointElem(left, top);
	unsigned long RB = GetPointElem(right, bottom);
	// 空間番号の排他的論理和から
	// 所属レベルを算出
	unsigned int Def = RB ^ LT;
	unsigned int HiLevel = 0;
	unsigned int i;
	for (i = 0; i < m_uiLevel; i++)
	{
		unsigned int Check = (Def >> (i * 2)) & 0x3;
		if (Check != 0)
			HiLevel = i + 1;
	}
	unsigned int SpaceNum = RB >> (HiLevel * 2);
	unsigned int AddNum = (m_iPow.get()->at(m_uiLevel - HiLevel) - 1) / 3;
	SpaceNum += AddNum;

	if (SpaceNum > m_dwCellNum)
		return 0xffffffff;

	return SpaceNum;
}
bool CollisionManager::Regist(float left, float top, float right, float bottom, Ptr<CollisionforTree> _ptr) {
	
	//モートン番号を取得
	unsigned long elem = GetMortonNumber(left, top, right, bottom);
	if (elem < m_dwCellNum) {
		auto p = (m_cellary.get());
		return m_cellary.get()->at(elem)->Push(_ptr);
	}
	return false;
}

unsigned long CollisionManager::GetAllCollisionList(std::vector<WPtr<Collision>>& ColVect) {
	Logger << U"GetALL";
	ColVect.clear();
	//判定を行う当たり判定のリスト
	std::list<WPtr<Collision>> ColStac;
	GetCollisionList(0, ColVect, ColStac);
	Logger << U"EndALL";
	return (unsigned long)ColVect.size();
}
bool CollisionManager::GetCollisionList(unsigned long Elem, std::vector<WPtr<Collision>>& ColVect, std::list<WPtr<Collision>>& ColStac) {
	std::list<WPtr<Collision>>::iterator itr;
	//1:空間内でのオブジェクト同士の衝突リストを作成
	Ptr<CollisionforTree> spCFT1 = m_cellary.get()->at(Elem)->GetFirstObj().lock();
	while (spCFT1.get() != nullptr) {
		auto spCFT2 = spCFT1->m_spNext.lock();
		while (spCFT2 != nullptr) {
			ColVect.emplace_back(spCFT1->m_pObject);
			ColVect.emplace_back(spCFT2->m_pObject);
			spCFT2 = spCFT2->m_spNext.lock();
		}
		//2:衝突スタックとの衝突リスト作成
		for (itr = ColStac.begin(); itr != ColStac.end(); itr++) {
			ColVect.push_back(spCFT1->m_pObject);
			ColVect.push_back(*itr);
		}
		spCFT1 = spCFT1->m_spNext.lock();
	}
	bool ChildFlag = false;
	unsigned int ObjNum = 0;
	unsigned int i, NextElem;
	for (i = 0; i < 4; ++i) {
		NextElem = Elem * 4 + 1+i;
		if (NextElem < m_dwCellNum) {
			if (!ChildFlag) {
				//オブジェクトをスタックに追加
				spCFT1 = m_cellary.get()->at(Elem)->GetFirstObj().lock();
				while (spCFT1.get()!=nullptr)
				{
					ColStac.emplace_back(spCFT1->m_pObject);
					ObjNum++;
					spCFT1 = spCFT1->m_spNext.lock();
				}

			}
			ChildFlag = true;
			//子空間へ
			GetCollisionList(Elem * 4 + 1 + i, ColVect, ColStac);
		}
	}
	if (ChildFlag) {
		for (int i = 0; i < ObjNum; ++i) {
			ColStac.pop_back();
		}
	}
	return true;
}

void CollisionManager::Update() {
	std::vector<WPtr<Collision>> ColVect;
	GetAllCollisionList(ColVect);
	Print <<U"Near_Collisions:{}"_fmt(ColVect.size());
	int col_cnt = 0;
	for (int i = 0; i < m_dwCellNum; ++i) {
		auto ptr = m_cellary.get()->at(i)->GetFirstObj().lock();
		while (ptr != nullptr) {
			col_cnt++;
			ptr = ptr->m_spNext.lock();
		}
		++i;
	}
	Print << U"Col_Cnt:{}"_fmt(col_cnt);
}

void CollisionManager::DebugDraw() {
#ifdef DEBUG
	std::vector<WPtr<Collision>> ColVect;
	GetAllCollisionList(ColVect);
	for (int i = 0; i + 1 < ColVect.size(); ++i) {
		auto l = m_stage->GamePositiontoWorldPosition(ColVect[i].lock()->GetTransform().m_position);
		auto r= m_stage->GamePositiontoWorldPosition(ColVect[i+1].lock()->GetTransform().m_position);
		Line(l.x, l.y, r.x, r.y).draw(Palette::Red);
	}

	for (int i = 0; i < m_dwCellNum; ++i) {
		std::vector<WPtr<CollisionforTree>> cols;
		auto ptr = m_cellary.get()->at(i)->GetFirstObj();
		while (ptr.lock() != nullptr) {
			cols.emplace_back(ptr);
			ptr = ptr.lock()->m_spNext;
		}
		for (int j = 0; j < cols.size(); ++j) {
			for (int k = j + 1; k < cols.size(); ++k) {
				auto l = m_stage->GamePositiontoWorldPosition(cols[j].lock()->m_pObject.lock()->GetTransform().m_position);
				auto r = m_stage->GamePositiontoWorldPosition(cols[k].lock()->m_pObject.lock()->GetTransform().m_position);
				Line(l.x, l.y, r.x, r.y).draw(Palette::Blue);
			}
		}
	}
	float width =std::abs(m_fUnit_W),height=std::abs(m_fUnit_H);
	for (float i = 0.0f; i < m_uiLevel; ++i) {
		for (float _y = 0; _y <= std::abs(m_fH); _y += height*std::powf(2,i)) {
			auto l = m_stage->GamePositiontoWorldPosition({ 0,_y });
			auto r = m_stage->GamePositiontoWorldPosition({ std::abs(m_fW),_y });
			Line(l.x, l.y, r.x, r.y).draw(std::powf(2, i), Palette::White);
		}
		for (float _x = 0; _x <= std::abs(m_fW); _x += width* std::powf(2, i)) {
			auto l = m_stage->GamePositiontoWorldPosition({ _x,std::abs(m_fH) });
			auto r = m_stage->GamePositiontoWorldPosition({ _x,0 });
			Line(l.x, l.y, r.x, r.y).draw(std::powf(2, i), Palette::White);
		}
	}
#endif // DEBUG
}
