#pragma once
#include"Def.h"
#include"Transform.h"
class Component;
class Stage;
class Actor {
	Ptr<Stage> m_stage;
	int _componentNum = -1;
	std::vector<Ptr<Component>> components;
	void UpdateComponentOrder();//コンポーネントの優先順位をソート
	Transform m_transform;
public:
	friend Component;
	Actor(Ptr<Stage> _m_stage);
	virtual ~Actor();
	void Update();
	void Draw() const;
	void AddComponent(Ptr<Component> _component);
	template<class T>
	inline  Ptr<T> GetComponent() {//コンポーネントを検索して一番最初にマッチしたものを返す
		Ptr<T> ret;
		for (auto ptr : components) {
			auto Tptr = std::dynamic_pointer_cast<T>(ptr);
			if (Tptr != nullptr) {
				ret = Tptr;
				return ret;
			}
		}
		return ret;
	}
}; 
