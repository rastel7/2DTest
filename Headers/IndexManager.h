#pragma once
#include"Def.h"
	
//一意なIDを返す．

template<class T>
class IndexManager {
	std::set<T> m_set;
	T id;
public:
	inline T GetID() {
		while (m_set.count(id)) {
			id++;
		}
		m_set.insert(id);
		return id;
	}
	inline void ReturnID(T _id) {
		m_set.erase(_id);
	}
};
