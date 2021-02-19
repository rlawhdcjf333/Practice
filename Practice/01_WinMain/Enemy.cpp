#include "pch.h"
#include "Enemy.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Player.h"

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

	Animation* p_Tmp = new Animation();
	p_Tmp->InitFrameByStartEnd(0, 0, 11, 0, true);
	p_Tmp->SetIsLoop(true);
	p_Tmp->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", p_Tmp));

	mCurrentAnm = p_Tmp;


	p_Tmp = new Animation();
	p_Tmp->InitFrameByStartEnd(0, 3, 11, 3, false);
	p_Tmp->SetIsLoop(true);
	p_Tmp->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", p_Tmp));

	p_Tmp = new Animation();
	p_Tmp->InitFrameByStartEnd(0, 7, 11, 7, true);
	p_Tmp->SetIsLoop(false);
	p_Tmp->SetFrameUpdateTime(0.1f);
	mAnimationList.insert(make_pair(L"LeftAttack", p_Tmp));

	p_Tmp = new Animation();
	p_Tmp->InitFrameByStartEnd(0, 6, 11, 6, false);
	p_Tmp->SetIsLoop(false);
	p_Tmp->SetFrameUpdateTime(0.1f);
	mAnimationList.insert(make_pair(L"RightAttack", p_Tmp));

	p_Tmp = new Animation();
	p_Tmp->InitFrameByStartEnd(0, 4, 17, 4, true);
	p_Tmp->SetIsLoop(true);
	p_Tmp->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftWalk", p_Tmp));

	p_Tmp = new Animation();
	p_Tmp->InitFrameByStartEnd(0, 1, 17, 1, false);
	p_Tmp->SetIsLoop(true);
	p_Tmp->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightWalk", p_Tmp));

	p_Tmp = new Animation();
	p_Tmp->InitFrameByStartEnd(0, 5, 14, 5, true);
	p_Tmp->SetIsLoop(false);
	p_Tmp->SetFrameUpdateTime(0.1f);
	mAnimationList.insert(make_pair(L"LeftDeath", p_Tmp));

	p_Tmp = new Animation();
	p_Tmp->InitFrameByStartEnd(0, 2, 14, 2, false);
	p_Tmp->SetIsLoop(false);
	p_Tmp->SetFrameUpdateTime(0.1f);
	mAnimationList.insert(make_pair(L"RightDeath", p_Tmp));

	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mDistance = 1500;
	mCurrentAnm->Play();

	mSpeed = Random::GetInstance()->RandomInt(1, 150);
	isDeath = false;

}

void Enemy::Release()
{
	ListIter iter = mAnimationList.begin();
	for (; iter != mAnimationList.end(); ++iter) {

		SafeDelete(iter->second);
	}


}

void Enemy::Update()
{

	mCurrentAnm->Update();

	float dtime = Time::GetInstance()->DeltaTime();

	float playerX = mPlayer->GetX();
	float playerY = mPlayer->GetY();

	mDistance = Math::GetDistance(mX, mY, playerX, playerY);

	ListIter iter;

	if (ObjectManager::GetInstance()->IsCollision(ObjectLayer::Enemy, mHitBox))
	{
		if (mCurrentAnm->GetNowFrameY() == 3 || mCurrentAnm->GetNowFrameY() == 4 || mCurrentAnm->GetNowFrameY() == 7)	//왼쪽볼때
		{
			mCurrentAnm = mAnimationList.find(L"LeftDeath")->second;

		}
		else if (mCurrentAnm->GetNowFrameY() == 0 || mCurrentAnm->GetNowFrameY() == 1 || mCurrentAnm->GetNowFrameY() == 6)	//오른쪽볼때
		{
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"RightDeath")->second;
		}
		mCurrentAnm->Play();
		//체력을 추가하면 여기에 조건을 걸고?
		isDeath = true;
	}

	if (isDeath)
	{
		if (mCurrentAnm == mAnimationList.find(L"LeftDeath")->second)
		{
			if(mCurrentAnm->GetNowFrameX() == 0)
				GameObject::SetIsDestroy(true);
		}
		else if (mCurrentAnm == mAnimationList.find(L"RightDeath")->second)
		{
			if (mCurrentAnm->GetNowFrameX() == 14)
				GameObject::SetIsDestroy(true);
		}
	}
	if (!isDeath)
	{

		if (mDistance > 1000) {

			if (mX > playerX) {
				iter = mAnimationList.find(L"LeftIdle");

				if (mCurrentAnm != iter->second) mCurrentAnm->Stop();
				mCurrentAnm = iter->second;
				mCurrentAnm->Play();

			}

			else {
				iter = mAnimationList.find(L"RightIdle");

				if (mCurrentAnm != iter->second) mCurrentAnm->Stop();
				mCurrentAnm = iter->second;
				mCurrentAnm->Play();

			}

			return;
		}


		if (mDistance <= mSizeX / 2) {

			if (mX > playerX) {

				iter = mAnimationList.find(L"LeftAttack");
				if (mCurrentAnm != iter->second) mCurrentAnm->Stop();
				mCurrentAnm = iter->second;
				mCurrentAnm->Play();


			}
			else {
				iter = mAnimationList.find(L"RightAttack");
				if (mCurrentAnm != iter->second) mCurrentAnm->Stop();
				mCurrentAnm = iter->second;
				mCurrentAnm->Play();

			}

		}

		if (mCurrentAnm == mAnimationList.find(L"LeftAttack")->second or mCurrentAnm == mAnimationList.find(L"RightAttack")->second) {

			if (mCurrentAnm->GetIsPlay()) { return; }
		}


		if (mDistance > mSizeX / 2) {
			if (mX > playerX) {

				iter = mAnimationList.find(L"LeftWalk");

				if (mCurrentAnm != iter->second) mCurrentAnm->Stop();
				mCurrentAnm = iter->second;
				mCurrentAnm->Play();

				mX -= dtime * 150.f;

				if (mY > playerY) mY -= dtime * mSpeed;
				else if (mY < playerY) mY += dtime * mSpeed;
			}
			else {

				iter = mAnimationList.find(L"RightWalk");

				if (mCurrentAnm != iter->second) mCurrentAnm->Stop();
				mCurrentAnm = iter->second;
				mCurrentAnm->Play();

				mX += dtime * 150.f;

				if (mY > playerY) mY -= dtime * mSpeed;
				else if (mY < playerY) mY += dtime * mSpeed;

			}
		}
	}


	if (mRect.left < 0) { mX = mSizeX / 2; }
	if (mRect.top < 0) { mY = mSizeY / 2; }
	if (mRect.right > 2400) { mX = 2400 - (mSizeX / 2); }
	if (mRect.bottom > 1600) { mY = 1600 - (mSizeY / 2); }


	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX + 20, mY + 50, mSizeX - 30, mSizeY + 40);




}

void Enemy::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnm->GetNowFrameX(),
		mCurrentAnm->GetNowFrameY(), 150, 132);
	//CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mHitBox);
}
