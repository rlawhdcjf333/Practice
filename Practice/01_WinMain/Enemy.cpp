#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Enemy::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Golem", Resources(L"Golem.bmp"), 1800, 534, 18, 8, true);
	mImage = IMAGEMANAGER->FindImage(L"Golem");



}

void Enemy::Release()
{
}

void Enemy::Update()
{
}

void Enemy::Render(HDC hdc)
{
}
