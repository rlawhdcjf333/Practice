#pragma once
#include "GameObject.h"
class Image;
class Animation;
class NPC : public GameObject
{
	Image* mImage;
	Animation* mIdleAnimation;
	Animation* mRunAnimation;
	Animation* mCurrentAnimation;	//���� �ִϸ��̼�

	Animation* mLeftIdleAnm;
	Animation* mRIghtIdleAnm;
public:
	NPC(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void SetCurrentAnm(Animation* mCurrentAnm) { mCurrentAnimation = mCurrentAnm; }
	Animation* GetAnimation(bool boo) { if(boo==true)return mLeftIdleAnm;
	else return mRIghtIdleAnm;}
};

