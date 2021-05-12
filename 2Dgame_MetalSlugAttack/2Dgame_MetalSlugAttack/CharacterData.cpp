#include "CharacterData.h"
#include "CollisionChecker.h"
#include "Image.h"
#include "CommonFunction.h"
HRESULT CharacterData::Init(int unitNum, CollisionChecker* collisionChecker)
{
    changeTimer = 0.0f; // 프레임 변경 확인용 타이머
    currFrameX = 0; //캐릭터 이미지 전환용 프레임
    isAlive = true;
    characterStatus = STATUS::STAND;

    //Rifle Init
    if (unitNum == -1)
    {
        this->collisionChecker = collisionChecker;
        unitType = UnitType::ENEMY;
        image_Stand = ImageManager::GetSingleton()->FindImage("rifle_stand");
        if (image_Stand == nullptr)
        {
            MessageBox(g_hWnd, "Rifle_Stand_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }

        image_Walk = ImageManager::GetSingleton()->FindImage("rifle_walk");
        if (image_Walk == nullptr)
        {
            MessageBox(g_hWnd, "rifle_Walk_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Fire = ImageManager::GetSingleton()->FindImage("rifle_fire");
        if (image_Fire == nullptr)
        {
            MessageBox(g_hWnd, "rifle_Fire_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Dead = ImageManager::GetSingleton()->FindImage("rifle_dead");
        if (image_Dead == nullptr)
        {
            MessageBox(g_hWnd, "rifle_Dead_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Win = ImageManager::GetSingleton()->FindImage("rifle_win");
        if (image_Win == nullptr)
        {
            MessageBox(g_hWnd, "rifle_Win_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        pos.x = WINSIZE_X - 180;
        pos.y = 300;
        moveSpeed = 60.0f;
        standMaxFrame = 7;
        fireMaxFrame = 7;
        walkMaxFrame = 11;
        winMaxFrame = 5;
        deadMaxFrame = 10;
        characterHp = 30;
        characterAtk = 10;
        attackCooltime = 3.0f;
        hitBoxHeight = 50;
        hitBoxWidth = 30;
        attackRangeWidth = 200;
        attackRangeHeight = 150;
        hitBox = GetRectToCenter(pos.x, pos.y, hitBoxWidth, hitBoxHeight);
        SetCollisionList();
    }
    //Player_Eri Init
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
        pos.y = 350;
        moveSpeed = 100.0f;
        walkMaxFrame = 11;
        standMaxFrame = 7;
        fireMaxFrame = 5;
        deadMaxFrame = 20;
        winMaxFrame = 6;
        characterHp = 50;
        characterAtk = 15;
        attackCooltime = 2.0f;
        hitBoxHeight = 50;
        hitBoxWidth = 30;
        hitBoxPos.x = pos.x - hitBoxWidth;
        hitBoxPos.y = pos.y;
        attackRangeWidth = 200;
        attackRangeHeight = 150;
        hitBox = GetRectToCenter(hitBoxPos.x, hitBoxPos.y, hitBoxWidth, hitBoxHeight);
    }
    SetCollisionList();
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
            image_Walk->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true, 2);
        }
        else if (characterStatus == STATUS::STAND)
        {
            image_Stand->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true, 2);
        }
        else if (characterStatus == STATUS::FIRE)
        {
            image_Fire->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true, 2);
        }
        else if (characterStatus == STATUS::WIN)
        {
            image_Win->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true, 2);
        }
        else if (characterStatus == STATUS::DEAD)
        {
            image_Dead->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true, 2);
        }
        //Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
        //Rectangle(hdc, attackRange.left, attackRange.top, attackRange.right, attackRange.bottom);
    }
}

void CharacterData::SetCollisionList()
{
    if (unitType == UnitType::PLAYER)
    {
        collisionChecker->AddPlayerCharacter(this);
    }
    else if (unitType == UnitType::ENEMY)
    {
        collisionChecker->AddEnemyCharacter(this);
    }
}

void CharacterData::Move()
{
    if (unitType == UnitType::PLAYER && characterStatus == STATUS::WALK)
    {
        pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    }
    else if (unitType == UnitType::ENEMY && characterStatus == STATUS::WALK)
    {
        pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    }
    if (pos.x >= WINSIZE_X || pos.x < 0)
    {
        isAlive = false;
        if (unitType == UnitType::PLAYER)
        {
            collisionChecker->EraseDeadPlayerCharacter(this);
        }
        else if (unitType == UnitType::ENEMY)
        {
            collisionChecker->EraseDeadEnemyCharacter(this);
        }
    }
}
