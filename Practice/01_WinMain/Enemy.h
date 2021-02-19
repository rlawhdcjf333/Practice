#pragma once
#include "GameObject.h"
class Animation;
class Player;

class Enemy : public GameObject
{
	Image* mImage;

	map <wstring, Animation*> mAnimationList;

	typedef map<wstring, Animation*> ::iterator ListIter;
	
	Player* mPlayer;

	float mDistance;

	Animation* mCurrentAnm;

	float mSpeed;

	bool isDeath;
public:
	Enemy(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetPlayer(Player* p_Player) { mPlayer = p_Player; }

};

