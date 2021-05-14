#include "EnemyManager.h"
#include "CharacterData.h"
#include "CollisionChecker.h"

HRESULT EnemyManager::Init(CollisionChecker* collisionChecker)
{
	this->collisionChecker = collisionChecker;
	vEnemyMgr.push_back(new CharacterData);
	vEnemyMgr[0]->Init(-1, collisionChecker);
	return S_OK;
}

void EnemyManager::Release()
{

}

void EnemyManager::Update()
{
	if (vEnemyMgr.size() >= 1)
	{
		for (int i = 0; i < vEnemyMgr.size(); i++)
		{
			vEnemyMgr[i]->Update();
		}
	}
}

void EnemyManager::Render(HDC hdc)
{
	if (vEnemyMgr.size() >= 1)
	{
		for (int i = 0; i < vEnemyMgr.size(); i++)
		{
			vEnemyMgr[i]->Render(hdc);
		}
	}
}
