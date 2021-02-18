#include "pch.h"
#include "Scene1.h"

#include "BackGround.h"
#include "Player.h"
#include  "Enemy.h"
#include "NPC.h"
#include "Camera.h"
#include "GameEvent.h"

void Scene1::Init()
{
	BackGround* backGround = new BackGround("BackGround", 0,0);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);

	Player* player1 = new Player("1", 400, 700);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player1);

	Enemy* enemy[5];
	for (int i = 0; i < 5; i++) {
		enemy[i] = new Enemy("enemy" + to_string(i+1), Random::GetInstance()->RandomInt(1000, 2200), Random::GetInstance()->RandomInt(1400));
		enemy[i]->SetPlayer(player1);
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, enemy[i]);
	}


	Camera* mCamera = new Camera();
	mCamera->SetTarget(player1);
	CameraManager::GetInstance()->SetMainCamera(mCamera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mCamera);

	ObjectManager::GetInstance()->Init();

	//GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.0f));
	//GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(player2));
	//GameEventManager::GetInstance()->PushEvent(new IDelayEvent(3.0f));
	//GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(player1));
}

void Scene1::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene1::Update()
{
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();
}

void Scene1::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}
