#include "CharacterData.h"
#include "CollisionChecker.h"
#include "Image.h"

HRESULT CharacterData::Init(int unitNum, CollisionChecker* collisionChecker)
{
    if (unitNum == 1)
    {
        this->collisionChecker = collisionChecker;
        unitType = UnitType::PLAYER;
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
        image_Fire = ImageManager::GetSingleton()->FindImage("Eri_fire");
        if (image_Fire == nullptr)
        {
            MessageBox(g_hWnd, "Eri_Fire_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Dead = ImageManager::GetSingleton()->FindImage("Eri_dead");
        if (image_Dead == nullptr)
        {
            MessageBox(g_hWnd, "Eri_Dead_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Win = ImageManager::GetSingleton()->FindImage("Eri_win");
        if (image_Win == nullptr)
        {
            MessageBox(g_hWnd, "Eri_Win_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        isAlive = true;
        characterStatus = STATUS::WALK;
        pos.x = 130;
        pos.y = 300;
        currFrameX = 0;
        changeTimer = 0.0f;
        SetCollisionList();
        moveSpeed = 50.0f;
        walkMaxFrame = 11;
        standMaxFrame = 7;
        fireMaxFrame = 5;
        deadMaxFrame = 20;
        winMaxFrame = 6;
    }

    return S_OK;
}

void CharacterData::Release()
{

}

void CharacterData::Update()
{
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
    {
        characterStatus = STATUS::FIRE;
        currFrameX = 0;
    }
    changeTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTimer >= 0.08f)
    {
        changeTimer = 0.0f;
        currFrameX++;
        if (characterStatus == STATUS::WALK && currFrameX > walkMaxFrame)
        {
            currFrameX = 0;
        }
        else if (characterStatus == STATUS::STAND && currFrameX > standMaxFrame)
        {
            currFrameX = 0;
        }
        else if (characterStatus == STATUS::FIRE && currFrameX > fireMaxFrame)
        {
            currFrameX = 0;
            characterStatus = STATUS::STAND;
        }
        else if (characterStatus == STATUS::DEAD && currFrameX > deadMaxFrame)
        {
            currFrameX = 0;
            isAlive = false;
        }
        else if (characterStatus == STATUS::WIN && currFrameX > winMaxFrame)
        {
            currFrameX = 0;
        }
    }
    Move();
}

void CharacterData::Render(HDC hdc)
{
    if (isAlive == true)
    {
        if (characterStatus == STATUS::WALK)
        {
            image_Walk->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, false, 2);
        }
        else if (characterStatus == STATUS::STAND)
        {
            image_Stand->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, false, 2);
        }
        else if (characterStatus == STATUS::FIRE)
        {
            image_Fire->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, false, 2);
        }
        else if (characterStatus == STATUS::DEAD)
        {
            image_Dead->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, false, 2);
        }
        else if (characterStatus == STATUS::WIN)
        {
            image_Win->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, false, 2);
        }
    }
}

void CharacterData::SetCollisionList()
{
    collisionChecker->AddPlayerCharacter(this);
}

void CharacterData::Move()
{
    if (unitType == UnitType::PLAYER && characterStatus == STATUS::WALK)
    {
        pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    }
    if (pos.x >= WINSIZE_X || pos.x < 0)
    {
        isAlive = false;
        collisionChecker->EraseDeadCharacter(this);
    }
}
