﻿#pragma once
#include"Def.h"
#include"Collision.h"
class CollisionManager;
class Stage;

class CCell :public std::enable_shared_from_this<CCell>{
	CollisionManager *m_colmanager;
	WPtr<CollisionforTree> m_spLatest,m_spNext;
public:
	CCell(CollisionManager* _colmanager);
	bool Push(Ptr<CollisionforTree> _ptr);
	bool OnRemove(Ptr<CollisionforTree> _remove_obj);
	inline WPtr<CollisionforTree> GetFirstObj() { return m_spLatest; }
};
class CollisionManager {
	static const size_t CLINER4TREEMANAGER_MAXLEVEL = 9;
	Ptr<std::vector<Ptr<CCell>>> m_cellary;
	Ptr<std::array<unsigned int, CLINER4TREEMANAGER_MAXLEVEL+1>> m_iPow;
	Stage* m_stage;
	unsigned long m_dwCellNum;// 空間の数
	float m_fW;		// 領域のX軸幅
	float m_fH;		// 領域のY軸幅
	float m_fLeft;	// 領域の左側（X軸最小値）
	float m_fTop;	// 領域の上側（Y軸最小値）
	float m_fUnit_W;		// 最小レベル空間の幅単位
	float m_fUnit_H;		// 最小レベル空間の高単位
	unsigned int m_uiLevel;			// 最下位レベル
	bool Init(unsigned int Level, float left, float top, float right, float bottom);//木にあたらしいセルを作成する
	unsigned long GetAllCollisionList(std::vector<WPtr<Collision>>& ColVect);
	bool GetCollisionList(unsigned long Elem, std::vector<WPtr<Collision>>& ColVect, std::list<WPtr<Collision>>& ColStac);
public:
	unsigned long GetMortonNumber(float left, float top, float right, float bottom);
	CollisionManager(Stage* _stage);
	bool Regist(float left, float top, float right, float bottom, Ptr<CollisionforTree> spOFT);
	void Update();
	void DebugDraw();
};

