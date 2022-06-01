#pragma once
#include"Def.h"
#include"Transform.h"
#include"DrawComponent.h"
#include"UpdateComponent.h"
class Actor;
class CollisionUpdater;
struct CollisionParameter {
	GameSize m_size;
	int m_col_id;
	Transform transform;
	GameSize stage_size;
	struct LeftUpandBottomDown {
		double lx, ly, rx, ry;
	} lubd;
	bool isHit(CollisionParameter const& r) const;
	LeftUpandBottomDown GetLeftandBottom() const;
	//最小の被っている領域を返す
	GameSize GetMinBounds(CollisionParameter const& r) const;
	//画面外に判定の一部が出ていた場合，それに対応してズラしたコリジョンを加えたvectorを返す
	std::vector<LeftUpandBottomDown> GetCorrectionLB(LeftUpandBottomDown const& lb)const;
	void Update();//lubdの更新
};
class Collision :public DrawComponent{
	GameSize m_size;
	int m_col_id;
	bool m_isStatic = false;
	Ptr<Collision> this_col;
	WPtr<CollisionUpdater> this_updater;
	mutable CollisionParameter col_parameter;
public:
	inline bool IsStatic() const { return m_isStatic; }
	Collision(GameSize _size,bool _isStatic, Ptr<Actor> _ptr);
	~Collision();
	void Draw() const override;
	//探索用に若干大きめのコリジョンを返す
	CollisionParameter GetLargeCollisionParameter() const;
	CollisionParameter GetCollisionParameter() const;
	inline int GetColID() { return m_col_id; }
	inline GameSize GetSize() const { return m_size; }
	inline void SetSize(GameSize _size) { m_size = _size; }
	inline 	WPtr<CollisionUpdater> Get_this_updater() const { return this_updater; }
};


//コリジョンの衝突解消を行う
class CollisionUpdater :public UpdateComponent {
	WPtr<Collision> m_collision_ptr;
	bool isHit(CollisionParameter const& l, CollisionParameter const& r) const;
public:
	void SolutionOverlapping(WPtr<Collision> r_wptr);
	CollisionUpdater(WPtr<Collision> _collision_ptr,Ptr<Actor> _actor);
	void Update() override;
};
