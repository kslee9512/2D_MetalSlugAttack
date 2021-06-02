#include "EnemyManager.h"
#include "Enemy.h"
#include "CollisionChecker.h"
#include "Image.h"
HRESULT EnemyManager::Init(int unitNum, CollisionChecker* collisionChecker)
{
    this->collisionChecker = collisionChecker;
    isDefeat = false;
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

HRESULT EnemyManager::BaseInit()
{
    ImageManager::GetSingleton()->AddImage("enemybase", "Image/Base/Base_enemy.bmp", 1298, 80, 22, 1, true, RGB(255, 255, 255));
    enemyBase = ImageManager::GetSingleton()->FindImage("enemybase");
    isStart = false;
    baseEngageFrame = 21;
    currFrameX = 0;
    frameTimer = 0.0f;
    return S_OK;
}

void EnemyManager::Release()
{

}

void EnemyManager::Update()
{
    if (!isStart)
    {
        frameTimer += TimerManager::GetSingleton()->GetElapsedTime();
        if (frameTimer >= 0.05)
        {
            frameTimer = 0.0f;
            currFrameX++;
            if (currFrameX == baseEngageFrame)
            {
                isStart = true;
            }
        }
    }
    for (int i = 0; i < vEnemyMgr.size(); i++)
    {
    	vEnemyMgr[i]->Update();
    }
    if (isDefeat)
    {
        BaseRetreat();
    }
}

void EnemyManager::Render(HDC hdc)
{
    enemyBase->FrameRender(hdc, WINSIZE_X - 150, 310, currFrameX, 0, true, 2);
	for (int i = 0; i < vEnemyMgr.size(); i++)
	{
        if (!(vEnemyMgr[i]->GetEndDeadScene()))
        {
            vEnemyMgr[i]->Render(hdc);
        }
	}
}

void EnemyManager::BaseRetreat()
{
    frameTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (frameTimer >= 0.05)
    {
        frameTimer = 0.0f;
        currFrameX--;
        if (currFrameX == 0)
        {
            currFrameX = 0;
        }
    }
}
