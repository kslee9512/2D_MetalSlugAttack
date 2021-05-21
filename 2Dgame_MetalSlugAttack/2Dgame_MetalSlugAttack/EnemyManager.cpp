#include "EnemyManager.h"
#include "Enemy.h"
#include "CollisionChecker.h"

HRESULT EnemyManager::Init(int unitNum, CollisionChecker* collisionChecker)
{
    this->collisionChecker = collisionChecker;
    if (vEnemyMgr.size() < 1)
    {
        vEnemyMgr.push_back(new Enemy);
        vEnemyMgr[0]->Init(unitNum, collisionChecker);
    }
    else
    {
        for (int i = 0; i < vEnemyMgr.size();)
        {
            if (!vEnemyMgr[i]->GetCharacterAlive() && vEnemyMgr[i]->GetEndDeadScene())
            {
                vEnemyMgr[i]->Init(unitNum, collisionChecker);
                break;
            }
            else
            {
                i++;
                if (i == vEnemyMgr.size())
                {
                    vEnemyMgr.push_back(new Enemy);
                    vEnemyMgr[i]->Init(unitNum, collisionChecker);
                    break;
                }
            }
        }
    }
    return S_OK;
}

void EnemyManager::Release()
{

}

void EnemyManager::Update()
{
		for (int i = 0; i < vEnemyMgr.size(); i++)
		{
			vEnemyMgr[i]->Update();
		}
}

void EnemyManager::Render(HDC hdc)
{
	for (int i = 0; i < vEnemyMgr.size(); i++)
	{
        if (!(vEnemyMgr[i]->GetEndDeadScene()))
        {
            vEnemyMgr[i]->Render(hdc);
        }
	}
}
