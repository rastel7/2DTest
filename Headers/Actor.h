#pragma once
#include"Def.h"
#include"Transform.h"
#include"Collision.h"
#include"Actor.h"
class Component;
class Stage;
class DrawComponent;
enum class ActorType {
	ETC = 0,
	PLAYER,
	ENEMY,
	EQUIP,
	PLAYER_BULLET
};

class Actor {
	int _componentNum = -1;
	std::vector<Ptr<Component>> components;
	void UpdateComponentOrder();//コンポーネントの優先順位をソート
	Actor();
protected:
	Stage* m_stage;
	Transform m_transform;
	ActorType m_actor_type;
public:
	bool CanRemove = false;
	friend Component;
	String name = U"";
	Actor(Stage* _m_stage);
	virtual ~Actor();
	void Update();
	std::vector<Ptr<DrawComponent>>  Draw() const;
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
	inline void SetTransform(Transform const& _transform) { m_transform = _transform; }
	inline Transform GetTransform() const { return m_transform; }
	inline Stage* GetStage() const { return m_stage; }
	inline ActorType GetActorType() const { return m_actor_type; }
	inline void SetActorType(ActorType const& _actor_type) { m_actor_type = m_actor_type; }
}; 

