#include "pch.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Camera.h"

Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Player::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Player", Resources(L"Player.bmp"), 1215, 1080, 9, 8,true);
	mImage = IMAGEMANAGER->FindImage(L"Player");

	//왼쪽 모션
	mLeftIdleAnm = new Animation();
	mLeftIdleAnm->InitFrameByStartEnd(0, 0, 7, 0, false);
	mLeftIdleAnm->SetIsLoop(true);
	mLeftIdleAnm->SetFrameUpdateTime(0.3f);
	mLeftIdleAnm->Play();

	mLeftWalkAnm = new Animation();
	mLeftWalkAnm->InitFrameByStartEnd(0, 6, 7, 6, false);
	mLeftWalkAnm->SetIsLoop(true);
	mLeftWalkAnm->SetFrameUpdateTime(0.2f);

	mLeftAttackAnm = new Animation();
	mLeftAttackAnm->InitFrameByStartEnd(0, 2, 8, 2, false);
	mLeftAttackAnm->SetIsLoop(false);
	mLeftAttackAnm->SetFrameUpdateTime(0.1f);

	mLeftDeathAnm = new Animation();
	mLeftDeathAnm->InitFrameByStartEnd(0, 4, 5, 4, false);
	mLeftDeathAnm->SetIsLoop(false);
	mLeftDeathAnm->SetFrameUpdateTime(0.5f);

	//오른쪽 모션
	mRightIdleAnm = new Animation();
	mRightIdleAnm->InitFrameByStartEnd(0, 1, 7, 1, false);
	mRightIdleAnm->SetIsLoop(true);
	mRightIdleAnm->SetFrameUpdateTime(0.3f);

	mRightWalkAnm = new Animation();
	mRightWalkAnm->InitFrameByStartEnd(0, 7, 7, 7, false);
	mRightWalkAnm->SetIsLoop(true);
	mRightWalkAnm->SetFrameUpdateTime(0.2f);

	mRightAttackAnm = new Animation();
	mRightAttackAnm->InitFrameByStartEnd(0, 3, 8, 3, false);
	mRightAttackAnm->SetIsLoop(false);
	mRightAttackAnm->SetFrameUpdateTime(0.1f);

	mRightDeathAnm = new Animation();
	mRightDeathAnm->InitFrameByStartEnd(0, 5, 5, 5, false);
	mRightDeathAnm->SetIsLoop(false);
	mRightDeathAnm->SetFrameUpdateTime(0.5f);


	mCurrentAnm = mLeftIdleAnm;

	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Release()
{
	SafeDelete(mLeftIdleAnm);
	SafeDelete(mLeftWalkAnm);
	SafeDelete(mLeftAttackAnm);
	SafeDelete(mLeftDeathAnm);
	SafeDelete(mRightIdleAnm);
	SafeDelete(mRightWalkAnm);
	SafeDelete(mRightAttackAnm);
	SafeDelete(mRightDeathAnm);
}

void Player::Update()
{
	if (Input::GetInstance()->GetKeyDown('D'))
	{
		mCurrentAnm->Stop();
		mCurrentAnm = mRightWalkAnm;
		mCurrentAnm->Play();
	}

	if ((mCurrentAnm == mRightWalkAnm or mCurrentAnm == mRightAttackAnm )and Input::GetInstance()->GetKey('D')) {

		float dtime = Time::GetInstance()->DeltaTime();
		mX += dtime * 200.f;

	}

	if (mCurrentAnm == mRightWalkAnm and Input::GetInstance()->GetKeyUp('D'))
	{
		mCurrentAnm->Stop();
		if (Input::GetInstance()->GetKey('A')) {
			mCurrentAnm = mLeftWalkAnm;
		}
		else if(!Input::GetInstance()->GetKey('W') and !Input::GetInstance()->GetKey('S')) mCurrentAnm = mRightIdleAnm;
		mCurrentAnm->Play();
	}

	if (Input::GetInstance()->GetKeyDown('A'))
	{
		mCurrentAnm->Stop();
		mCurrentAnm = mLeftWalkAnm;
		mCurrentAnm->Play();
	}

	if ((mCurrentAnm == mLeftWalkAnm or mCurrentAnm == mLeftAttackAnm) and Input::GetInstance()->GetKey('A')) {

		float dtime = Time::GetInstance()->DeltaTime();
		mX -= dtime * 200.f;
	}

	if (mCurrentAnm == mLeftWalkAnm and Input::GetInstance()->GetKeyUp('A'))
	{
		mCurrentAnm->Stop();
		if (Input::GetInstance()->GetKey('D')) {
			mCurrentAnm = mRightWalkAnm;
		}
		else if (!Input::GetInstance()->GetKey('W') and !Input::GetInstance()->GetKey('S'))mCurrentAnm = mLeftIdleAnm;
		mCurrentAnm->Play();
	}

	if (Input::GetInstance()->GetKeyDown('W'))
	{
		mCurrentAnm->Stop();

		if (mCurrentAnm == mLeftIdleAnm)
			mCurrentAnm = mLeftWalkAnm;
		else if (mCurrentAnm == mRightIdleAnm)
			mCurrentAnm = mRightWalkAnm;

		mCurrentAnm->Play();

	}

	if (Input::GetInstance()->GetKey('W')) {

		float dtime = Time::GetInstance()->DeltaTime();
		mY -= dtime * 200.f;
	}

	if ((mCurrentAnm==mLeftWalkAnm or mCurrentAnm == mRightWalkAnm) and Input::GetInstance()->GetKeyUp('W'))
	{
		if (Input::GetInstance()->GetKey('S')) { return; }
		mCurrentAnm->Stop();

		if(mCurrentAnm==mLeftWalkAnm)
			mCurrentAnm = mLeftIdleAnm;
		else if (mCurrentAnm == mRightWalkAnm)
			mCurrentAnm = mRightIdleAnm;
	
		if (Input::GetInstance()->GetKey('A')) {mCurrentAnm = mLeftWalkAnm;}
		if (Input::GetInstance()->GetKey('D')) { mCurrentAnm = mRightWalkAnm;}
		mCurrentAnm->Play();
	}


	if (Input::GetInstance()->GetKeyDown('S'))
	{
		mCurrentAnm->Stop();

		if (mCurrentAnm == mLeftIdleAnm)
			mCurrentAnm = mLeftWalkAnm;
		else if (mCurrentAnm == mRightIdleAnm)
			mCurrentAnm = mRightWalkAnm;

		mCurrentAnm->Play();

	}

	if (Input::GetInstance()->GetKey('S')) {

		float dtime = Time::GetInstance()->DeltaTime();
		mY += dtime * 200.f;
	}

	if ((mCurrentAnm == mLeftWalkAnm or mCurrentAnm == mRightWalkAnm) and Input::GetInstance()->GetKeyUp('S'))
	{

		if (Input::GetInstance()->GetKey('W')) { return; }
		mCurrentAnm->Stop();

		if (mCurrentAnm == mLeftWalkAnm)
			mCurrentAnm = mLeftIdleAnm;
		if (mCurrentAnm == mRightWalkAnm)
			mCurrentAnm = mRightIdleAnm;

		if (Input::GetInstance()->GetKey('A')) { mCurrentAnm = mLeftWalkAnm; }
		if (Input::GetInstance()->GetKey('D')) { mCurrentAnm = mRightWalkAnm; }

		mCurrentAnm->Play();
	}

	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{

		if (mCurrentAnm == mLeftAttackAnm or mCurrentAnm == mRightAttackAnm) {
			return;
		}

		mCurrentAnm->Stop();

		if (mCurrentAnm == mLeftIdleAnm || mCurrentAnm == mLeftWalkAnm)
			mCurrentAnm = mLeftAttackAnm;
		else if (mCurrentAnm == mRightIdleAnm || mCurrentAnm == mRightWalkAnm)
			mCurrentAnm = mRightAttackAnm;

		mCurrentAnm->Stop();
		mCurrentAnm->Play();

	}

	if (mCurrentAnm == mLeftAttackAnm and mCurrentAnm->GetNowFrameX() == 7) {

		 mCurrentAnm = mLeftIdleAnm;
		 mCurrentAnm->Play();

		 if (Input::GetInstance()->GetKey('A')) {
			mCurrentAnm->Stop();
			mCurrentAnm = mLeftWalkAnm;
			mCurrentAnm->Play();

		 }

	}


	if (mCurrentAnm == mRightAttackAnm and mCurrentAnm->GetNowFrameX() == 7) {

		mCurrentAnm = mRightIdleAnm;
		mCurrentAnm->Play();

		if (Input::GetInstance()->GetKey('D')) {
		
			mCurrentAnm->Stop();
			mCurrentAnm = mRightWalkAnm;
			mCurrentAnm->Play();
		}

	}

	if (mRect.left < 0) { mX = mSizeX / 2; }
	if (mRect.top < 0) { mY = mSizeY / 2; }
	if (mRect.right > 2400) { mX = 2400 - (mSizeX / 2); }
	if (mRect.bottom > 1600) { mY = 1600 - (mSizeY / 2); }


	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mCurrentAnm->Update();
}

void Player::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->FrameRender(hdc, mImage, mRect.left, mRect.top,mCurrentAnm->GetNowFrameX(),
			mCurrentAnm->GetNowFrameY());

	//mImage->FrameRender(hdc,mRect.left,mRect.top, mCurrentAnm->GetNowFrameX(),mCurrentAnm->GetNowFrameY());
}
