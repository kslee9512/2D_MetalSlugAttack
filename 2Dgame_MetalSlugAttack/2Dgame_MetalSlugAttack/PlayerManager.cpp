#include "PlayerManager.h"
#include "CollisionChecker.h"
#include "CharacterData.h"
HRESULT PlayerManager::Init(int unitNum, CollisionChecker* collisionChecker)
{
    this->collisionChecker = collisionChecker;
    if (vPlayerCharacter.size() < 1)
    {
        vPlayerCharacter.push_back(new CharacterData);
        vPlayerCharacter[0]->Init(unitNum, collisionChecker);
    }
    else
    {
        for (int i = 0; i < vPlayerCharacter.size();)
        {
            if (!vPlayerCharacter[i]->GetIsAlive())
            {
                vPlayerCharacter[i]->Init(unitNum, collisionChecker);
                break;
            }
            else if (vPlayerCharacter[i]->GetIsAlive() == true)
            {
                i++;
                if (i == vPlayerCharacter.size())
                {
                    vPlayerCharacter.push_back(new CharacterData);
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
    if (vPlayerCharacter.size() >= 1)
    {
        for (int i = 0; i < vPlayerCharacter.size(); i++)
        {
            vPlayerCharacter[i]->Update();
        }
    }
}

void PlayerManager::Render(HDC hdc)
{
    if (vPlayerCharacter.size() >= 1)
    {
        for (int i = 0; i < vPlayerCharacter.size(); i++)
        {
            vPlayerCharacter[i]->Render(hdc);
        }
    }
}
