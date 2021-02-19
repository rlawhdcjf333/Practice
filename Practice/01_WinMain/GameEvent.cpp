#include "pch.h"
#include "GameEvent.h"
#include "NPC.h"
#include "Camera.h"
IChangeCameraTargetEvent::IChangeCameraTargetEvent(GameObject * target)
{
	mTarget = target;
}

void IChangeCameraTargetEvent::Start()
{
	CameraManager::GetInstance()->GetMainCamera()->SetTarget(mTarget);
}

bool IChangeCameraTargetEvent::Update()
{
	float x = CameraManager::GetInstance()->GetMainCamera()->GetX();
	float y = CameraManager::GetInstance()->GetMainCamera()->GetY();

	if (Math::GetDistance(x, y, mTarget->GetX(), mTarget->GetY()) <= 5.0f)
	{
		return true;
	}

	return false;
}

IDelayEvent::IDelayEvent(float delayTime)
{
	mDelayTime = delayTime;
	mCurrentTime = 0.f;
}

void IDelayEvent::Start()
{
}

bool IDelayEvent::Update()
{
	mCurrentTime += Time::GetInstance()->DeltaTime();

	if (mCurrentTime >= mDelayTime)
	{
		return true;
	}

	return false;
}

void EndEvent::Start()
{
	mNpc->SetY(-100);

	if (mPlayer->GetX()-CameraX- 400 < 0)
	{
		mNpc->SetX(mPlayer->GetX()-CameraX + 400);
		NPC* temp = (NPC*)mNpc;
		temp->SetCurrentAnm(temp->GetAnimation(true));
	}
	else
	{
		mNpc->SetX(mPlayer->GetX()- CameraX - 400);
		NPC* temp = (NPC*)mNpc;
		temp->SetCurrentAnm(temp->GetAnimation(false));
	}
}

bool EndEvent::Update()
{
	float dtime = Time::GetInstance()->DeltaTime();
	mNpc->SetY(mNpc->GetY() + dtime * 100.f);

	if (mNpc->GetY() >= mPlayer->GetY()-CameraY)
	{
		mNpc->SetY(mPlayer->GetY()-CameraY);
		return true;
	}

	return false;
}

EndEvent::EndEvent(GameObject * target1, GameObject * target2)
{
	mNpc = target1;
	mPlayer = target2;

}
