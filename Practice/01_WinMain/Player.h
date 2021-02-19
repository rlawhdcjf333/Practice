#pragma once
#include "GameObject.h"

class Animation;
class Player : public GameObject
{
	Image* mImage;

	Animation* mRightIdleAnm; // 0,1,7,1
	Animation* mRightWalkAnm; // 0,7,7,7
	Animation* mRightAttackAnm; // 0,3,8,3
	Animation* mRightDeathAnm; // 0,5,5,5

	Animation* mLeftIdleAnm; // 0,0,7,0
	Animation* mLeftWalkAnm; //0,6,7,6
	Animation* mLeftAttackAnm; //0,2,8,2
	Animation* mLeftDeathAnm; // 0,4,5,4

	Animation* mCurrentAnm;

	bool isDeath;
public:
	Player(const string& name,float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

