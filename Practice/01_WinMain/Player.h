#pragma once
#include "GameObject.h"

class Animation;
class Player : public GameObject
{
	Image* mImage;

	map <wstring, Animation*> mAnimationList;
	Animation* mCurrentAnm;

	bool isDeath;

	int mRandomIndexX;	//�̹��� ���� ����
	int mRandomIndexY;	//�̹��� ���� ����
public:
	Player(const string& name,float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

