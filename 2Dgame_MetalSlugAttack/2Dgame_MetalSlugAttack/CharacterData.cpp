#include "CharacterData.h"
#include "CollisionChecker.h"

HRESULT CharacterData::Init(int unitNum, CollisionChecker* collisionChecker)
{
    if (unitNum == 1)
    {
        this->collisionChecker = collisionChecker;
        ImageManager::GetSingleton()->AddImage("Eri_stand", "Image/Eri/Eri_stand.bmp", 250, 50, true, RGB(255, 255, 255));
        image_Stand = ImageManager::GetSingleton()->FindImage("Eri_stand");
        if (image_Stand == nullptr)
        {
            MessageBox(g_hWnd, "Eri_Stand_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        ImageManager::GetSingleton()->AddImage("Eri_walk", "Image/Eri/Eri_walk.bmp", 350, 50, true, RGB(255, 255, 255));
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
    }

    return S_OK;
}

void CharacterData::Release()
{

}

void CharacterData::Update()
{

}

void CharacterData::Render(HDC hdc)
{

}

void CharacterData::SetCollisionList()
{
    collisionChecker->AddPlayerCharacter(this);
}
