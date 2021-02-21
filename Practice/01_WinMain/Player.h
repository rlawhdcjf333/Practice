#pragma once
#include "GameObject.h"

class Animation;
class Player : public GameObject
{
	Image* mImage;

	map <wstring, Animation*> mAnimationList;
	Animation* mCurrentAnm;

	bool isDeath;

	int mRandomIndexX;	//이미지 랜덤 변수
	int mRandomIndexY;	//이미지 랜덤 변수
public:
	Player(const string& name,float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

