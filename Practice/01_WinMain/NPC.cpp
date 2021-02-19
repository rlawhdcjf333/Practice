#include "pch.h"
#include "NPC.h"
#include "Animation.h"
#include "Image.h"
#include "GameEventManager.h"

NPC::NPC(const string& name, float x, float y)
{
	mX = x;
	mY = y;
}

void NPC::Init()
{
	IMAGEMANAGER->LoadFromFile(L"NPC", Resources(L"hollowidle.bmp"), 1098, 430, 6, 2, true);
	mImage = IMAGEMANAGER->FindImage(L"NPC");

	mLeftIdleAnm = new Animation();
	mLeftIdleAnm->InitFrameByStartEnd(0, 0, 5, 0, false);
	mLeftIdleAnm->SetIsLoop(true);
	mLeftIdleAnm->SetFrameUpdateTime(0.1f);
	mLeftIdleAnm->Play();

	mRIghtIdleAnm = new Animation();
	mRIghtIdleAnm->InitFrameByStartEnd(0, 1, 5, 1, false);
	mRIghtIdleAnm->SetIsLoop(true);
	mRIghtIdleAnm->SetFrameUpdateTime(0.1f);

	mCurrentAnimation = mLeftIdleAnm;
	
}

void NPC::Release()
{ 

}

void NPC::Update()
{
	mCurrentAnimation->Update();
}

void NPC::Render(HDC hdc)
{
	if (GameEventManager::GetInstance()->IsPlaying())
	{
		mImage->FrameRender(hdc, mX, mY, mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());
	}
}
