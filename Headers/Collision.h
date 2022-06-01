#pragma once
#include"Def.h"
#include"Transform.h"
#include"DrawComponent.h"
#include"UpdateComponent.h"
class Actor;
class CCell;
class Collision;
class CollisionManager;
class CollisionforTree:public std::enable_shared_from_this<CollisionforTree> {
public:
	WPtr<CollisionManager> col_manager;
	WPtr<CCell> m_pCell;//登録されている空間へのポインタ
	WPtr<Collision> m_pObject;//コリジョンへのポインタ
	WPtr<CollisionforTree> m_spPre;//前方
	WPtr<CollisionforTree> m_spNext;//後方
	inline CollisionforTree(Ptr<Collision> _m_pObject,Ptr<CollisionManager> _col_mane):m_pObject(_m_pObject),col_manager(_col_mane) {}
	bool RegistCell(Ptr<CCell> _p_Cell);//CCellへ自身を登録
	bool Remove();//登録されているCCellから抜ける
	void Update();
};
class Collision :public DrawComponent, public std::enable_shared_from_this<Collision> {
	mutable Ptr<CollisionforTree> m_CFT;
public:
	Collision(Ptr<CollisionManager> _col_manager, Ptr<Actor> _actor);
	
	float m_r;
	mutable float left, top, bottom, right;
	inline Collision(float _r,Ptr<Actor> _ptr): DrawComponent(_ptr),m_r(_r) {

	}
	void UpdateParameter() const;
	void Draw() const override;
};
