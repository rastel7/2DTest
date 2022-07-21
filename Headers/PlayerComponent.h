#pragma once
#include"Def.h"
#include"UpdateComponent.h"
#include"Transform.h"
#include"DrawComponent.h"
class Actor;
class Sprite;
//プレイヤーのステータスの値を保存
struct PlayerProperty {
	const int MOVE_SPRITE_PERIOD = 15;
	bool isLeft = 0;//右を向いている
	int MovingTime = 0;//連続して歩いている時間
};

class Player : public UpdateComponent {
	struct Life {
		int maxlife, life;
	} m_life;
	class Experience {
	public:
		int now_exp = 0, max_exp = 1;
		inline void AddExp(int _exp) {
			now_exp += _exp;
			
		}
	} exp;
	Ptr<Sprite> m_player_sprite;
	PlayerProperty m_prop;
	//メンバ変数のポインタをセットする
	void SetComponents();
	//パッドでの横移動を処理
	void Move();
	//spriteコンポーネントに対してidの変更などを行う
	void UpdatePlayerGraphics();
	void ExpProcess();
public:
	
	inline Life GetLife()const { return m_life; }
	Player(Transform _transform,Ptr<Actor> _ptr);
	virtual ~Player() {};
	void Update() override;
	inline void AddExp(int x) { exp.AddExp(x); }
};

