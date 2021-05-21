#include "PlayerManager.h"
#include "CollisionChecker.h"
#include "Player.h"
HRESULT PlayerManager::Init(int unitNum, CollisionChecker* collisionChecker)
{
    this->collisionChecker = collisionChecker;
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

void PlayerManager::Release()
{
}

void PlayerManager::Update()
{
    for (int i = 0; i < vPlayerCharacter.size(); i++)
    {
        vPlayerCharacter[i]->Update();
    }
}

void PlayerManager::Render(HDC hdc)
{
    for (int i = 0; i < vPlayerCharacter.size(); i++)
    {
        vPlayerCharacter[i]->Render(hdc);
    }
}
