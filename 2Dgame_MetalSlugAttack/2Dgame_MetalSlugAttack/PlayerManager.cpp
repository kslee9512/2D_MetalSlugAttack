#include "PlayerManager.h"
#include "CollisionChecker.h"
#include "Player.h"
#include "Image.h"
HRESULT PlayerManager::Init(int unitNum, CollisionChecker* collisionChecker)
{
    this->collisionChecker = collisionChecker;
    isDefeat = false;
    if (vPlayerCharacter.size() < 1)
    {
        vPlayerCharacter.push_back(new Player);
        vPlayerCharacter[0]->Init(unitNum, collisionChecker);
    }
    else
    {
        for (int i = 0; i < vPlayerCharacter.size();)
        {
            if (!vPlayerCharacter[i]->GetCharacterAlive() && vPlayerCharacter[i]->GetEndDeadScene())
            {
                vPlayerCharacter[i]->Init(unitNum, collisionChecker);
                break;
            }
            else
            {
                i++;
                if (i == vPlayerCharacter.size())
                {
                    vPlayerCharacter.push_back(new Player);
                    vPlayerCharacter[i]->Init(unitNum, collisionChecker);
                    break;
                }
            }
        }
    }

    return S_OK;
}

HRESULT PlayerManager::BaseInit()
{
    ImageManager::GetSingleton()->AddImage("playerbase", "Image/Base/Base_player.bmp", 1298, 80, 22, 1, true, RGB(255, 255, 255));
    playerBase = ImageManager::GetSingleton()->FindImage("playerbase");
    isStart = false;
    baseEngageFrame = 21;

    currFrameX = 0;
    frameTimer = 0.0f;
    return S_OK;
}

void PlayerManager::Release()
{
}

void PlayerManager::Update()
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
    for (int i = 0; i < vPlayerCharacter.size(); i++)
    {
        vPlayerCharacter[i]->Update();
    }
    if (isDefeat)
    {
        PlayerBaseRetreat();
    }
}

void PlayerManager::Render(HDC hdc)
{
    playerBase->FrameRender(hdc, 100, 310, currFrameX, 0, true, 2);
    for (int i = 0; i < vPlayerCharacter.size(); i++)
    {
        vPlayerCharacter[i]->Render(hdc);
    }
}

void PlayerManager::PlayerBaseRetreat()
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
