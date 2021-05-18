#include "CharacterData.h"
#include "CollisionChecker.h"
#include "Image.h"
#include "CommonFunction.h"
HRESULT CharacterData::Init(int unitNum, CollisionChecker* collisionChecker)
{
    this->collisionChecker = collisionChecker;
    fireCount = 0.0f;
    changeTimer = 0.0f; // 프레임 변경 확인용 타이머
    currFrameX = 0; //캐릭터 이미지 전환용 프레임
    isAlive = true;
    characterStatus = STATUS::STAND;
    findEnemy = false;
    readyToFire = true;
    currAttackCount = 0;
    //Rifle Init
    if (unitNum == -1)
    {
        Name = "소총수";
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
        pos.y = 350;
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
        hitBoxPos = { pos.x + hitBoxWidth, pos.y };
        attackRangeWidth = 250;
        attackRangeHeight = 150;
        maxAttackCount = 1;
    }
    //Player_Eri Init
    else if (unitNum == 1)
    {
        Name = "Eri";
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
        maxAttackCount = 1;
    }
    if (unitType == UnitType::ENEMY)
    {
        attackBoxPos = { pos.x - (attackRangeWidth / 2) + 30, pos.y };
        attackRange = GetRectToCenter(attackBoxPos.x, attackBoxPos.y, attackRangeWidth, attackRangeHeight);
        hitBox = GetRectToCenter(pos.x, pos.y, hitBoxWidth, hitBoxHeight);
    }
    else if (unitType == UnitType::PLAYER)
    {
        attackBoxPos = { pos.x + (attackRangeWidth / 2) - 30, pos.y };
        attackRange = GetRectToCenter(attackBoxPos.x, attackBoxPos.y, attackRangeWidth, attackRangeHeight);
        hitBox = GetRectToCenter(hitBoxPos.x, hitBoxPos.y, hitBoxWidth, hitBoxHeight);
    }

    if (unitType == UnitType::PLAYER)
    {
        collisionChecker->AddPlayerCharacter(this);
    }
    else if (unitType == UnitType::ENEMY)
    {
        collisionChecker->AddEnemyCharacter(this);
    }
    return S_OK; 
}

void CharacterData::Release()
{

}

void CharacterData::Update()
{
    switch (characterStatus)
    {
    case STATUS::WALK :
        UpdateMove();
        break;
    case STATUS::STAND :
        UpdateStand();
        break;
    case STATUS::FIRE :
        UpdateFire();
        break;
    }
    if (characterHp <= 0)
    {
        isAlive = false;
    }
}

void CharacterData::Render(HDC hdc)
{
    if (isAlive == true)
    {
        //Rectangle(hdc, attackRange.left, attackRange.top, attackRange.right, attackRange.bottom);
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

    }
}

void CharacterData::UpdateMove()
{
    //움직임 프레임
    changeTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTimer >= 0.07f)
    {
        changeTimer = 0.0f;
        currFrameX++;
        if (currFrameX > walkMaxFrame)
        {
            currFrameX = 0;
        }
    }
    if (!readyToFire && fireCount < attackCooltime)
    {
        fireCount += TimerManager::GetSingleton()->GetElapsedTime();
        if (fireCount >= attackCooltime)
        {
            readyToFire = true;
        }
    }
    if (findEnemy)
    {
        currFrameX = 0;
        characterStatus = STATUS::STAND;
    }
    if (unitType == UnitType::PLAYER)
    {
        pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
        hitBoxPos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
        attackBoxPos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
        hitBox = GetRectToCenter(hitBoxPos.x, hitBoxPos.y, hitBoxWidth, hitBoxHeight);
        attackRange = GetRectToCenter(attackBoxPos.x, attackBoxPos.y, attackRangeWidth, attackRangeHeight);
    }
    else if (unitType == UnitType::ENEMY)
    {
        pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
        hitBoxPos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
        attackBoxPos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
        hitBox = GetRectToCenter(hitBoxPos.x, hitBoxPos.y, hitBoxWidth, hitBoxHeight);
        attackRange = GetRectToCenter(attackBoxPos.x, attackBoxPos.y, attackRangeWidth, attackRangeHeight);
    }
    if (pos.x >= WINSIZE_X || pos.x < 0)
    {
        isAlive = false;
    }
}

void CharacterData::UpdateStand()
{
    changeTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTimer >= 0.07f)
    {
        changeTimer = 0.0f;
        currFrameX++;
        if (currFrameX > standMaxFrame)
        {
            currFrameX = 0;
        }
    }
    if (!readyToFire && fireCount < attackCooltime)
    {
        fireCount += TimerManager::GetSingleton()->GetElapsedTime();
        if (fireCount >= attackCooltime)
        {
            fireCount = 0;
            readyToFire = true;
        }
    }
    if (findEnemy && readyToFire)
    {
        currFrameX = 0;
        characterStatus = STATUS::FIRE;
    }
    else if (!findEnemy)
    {
        characterStatus = STATUS::WALK;
    }
}

void CharacterData::UpdateFire()
{
    changeTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTimer >= 0.07f)
    {
        changeTimer = 0.0f;
        currFrameX++;
        if (currFrameX > fireMaxFrame)
        {
            currFrameX = 0;
            fireCount = 0.0f;
            readyToFire = false;
            characterStatus = STATUS::STAND;
        }
    }
}
