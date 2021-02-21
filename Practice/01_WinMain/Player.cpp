#include "pch.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "GameEventManager.h"

Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Player::Init()
{
	mRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 100, 100);

	mRandomIndexX = Random::GetInstance()->RandomInt(10);
	mRandomIndexY = Random::GetInstance()->RandomInt(8);

	IMAGEMANAGER->LoadFromFile(L"Staff", Resources(L"Staff(30 , 16).bmp"), 960, 512, 30, 16, true);
	mImage = IMAGEMANAGER->FindImage(L"Staff");	//랜덤하게 넣기

	//이미지 작업한 다음에 애니메이션 모션 만들어서 넣기

	Animation* tempAnm = new Animation();
	tempAnm->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2, mRandomIndexX * 3, mRandomIndexY * 2, true);
	tempAnm->SetIsLoop(true);
	tempAnm->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", tempAnm));
	mCurrentAnm = tempAnm;

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2 + 1, mRandomIndexX * 3,mRandomIndexY * 2 + 1, true);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2, mRandomIndexX * 3 + 2, mRandomIndexY * 2, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2 + 1, mRandomIndexX * 3 + 2, mRandomIndexY * 2 + 1, true);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));

}

void Player::Release()
{

}

void Player::Update()
{
	if (Input::GetInstance()->GetKeyDown('A')) {
		mCurrentAnm->Stop();
		mCurrentAnm = mAnimationList.find(L"LeftRun")->second;
		mCurrentAnm->Play();
	}

	if (Input::GetInstance()->GetKeyUp('A')) {
		mCurrentAnm->Stop();
		mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;
		mCurrentAnm->Play();
	}
	if (Input::GetInstance()->GetKeyDown('D')) {
		mCurrentAnm->Stop();
		mCurrentAnm = mAnimationList.find(L"RightRun")->second;
		mCurrentAnm->Play();

	}
	if (Input::GetInstance()->GetKeyUp('D')) {
		mCurrentAnm->Stop();
		mCurrentAnm = mAnimationList.find(L"RightIdle")->second;
		mCurrentAnm->Play();
	}
	mCurrentAnm->Update();
}

void Player::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnm->GetNowFrameX(),
		mCurrentAnm->GetNowFrameY(), mImage->GetFrameWidth() * 2, mImage->GetFrameHeight() * 2);
	//CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mAttackRect);
	//CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mHitBox);
	//mImage->FrameRender(hdc,mRect.left,mRect.top, mCurrentAnm->GetNowFrameX(),mCurrentAnm->GetNowFrameY());
}
