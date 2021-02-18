#include "pch.h"
#include "BackGround.h"
#include "Image.h"
#include "Camera.h"

BackGround::BackGround(const string& name, float x, float y)

	: GameObject(name) 
{
	mX = x, mY = y;
}

void BackGround::Init()
{
	IMAGEMANAGER->LoadFromFile(L"BackGround", Resources(L"BackGround.bmp"), 1200, 800, false);
	mImage = IMAGEMANAGER->FindImage(L"BackGround");

}

void BackGround::Release()
{
}

void BackGround::Update()
{
}

void BackGround::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleRender(hdc, mImage, 0, 0, 2400, 1600);
}
