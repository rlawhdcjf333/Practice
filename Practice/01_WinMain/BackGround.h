#pragma once
#include "GameObject.h"

class BackGround : public GameObject
{
	Image* mImage;

public:
	BackGround(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;



};

