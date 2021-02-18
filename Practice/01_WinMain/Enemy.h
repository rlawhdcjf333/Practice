#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
	class Image* mImage;
	class Animation* mIdleAnimation;
	class Animation* mRunAnimation;
	class Animation* mCurrentAnimation;	//현재 애니메이션
public:
	Enemy(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

