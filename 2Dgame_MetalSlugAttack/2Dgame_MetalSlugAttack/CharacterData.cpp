#include "CharacterData.h"
#include "CollisionChecker.h"
#include "Image.h"

HRESULT CharacterData::Init(int unitNum, CollisionChecker* collisionChecker)
{
    if (unitNum == 1)
    {
        this->collisionChecker = collisionChecker;
     
        image_Stand = ImageManager::GetSingleton()->FindImage("Eri_stand");
        if (image_Stand == nullptr)
        {
            MessageBox(g_hWnd, "Eri_Stand_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }

        image_Walk = ImageManager::GetSingleton()->FindImage("Eri_walk");
        if (image_Walk == nullptr)
        {
            MessageBox(g_hWnd, "Eri_Walk_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        isAlive = true;
        characterStatus = STATUS::WALK;
        pos.x = 130;
        pos.y = 350;
        currFrameX = 0;
        changeTimer = 0.0f;
        SetCollisionList();
    }

    return S_OK;
}

void CharacterData::Release()
{

}

void CharacterData::Update()
{
    changeTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTimer >= 0.1f)
    {
        changeTimer = 0.0f;
        currFrameX++;
        if (currFrameX > 6)
        {
            currFrameX = 0;
        }
    }
}

void CharacterData::Render(HDC hdc)
{
    if (isAlive == true)
    {
        if (characterStatus == STATUS::WALK)
        {
            image_Walk->FrameRender(hdc, pos.x, pos.y, currFrameX, 0);
        }
    }
}

void CharacterData::SetCollisionList()
{
    collisionChecker->AddPlayerCharacter(this);
}
