#include "Player.h"
#include "CommonFunction.h"
#include "Image.h"
#include "CollisionChecker.h"

HRESULT Player::Init(int unitNum, CollisionChecker* collisionChecker)
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
    endDeadScene = false;
    if (unitNum == 1)
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

    attackBoxPos = { pos.x + (attackRangeWidth / 2) - 30, pos.y };
    attackRange = GetRectToCenter(attackBoxPos.x, attackBoxPos.y, attackRangeWidth, attackRangeHeight);
    hitBox = GetRectToCenter(hitBoxPos.x, hitBoxPos.y, hitBoxWidth, hitBoxHeight);
    collisionChecker->AddPlayerCharacter(this);
    return E_NOTIMPL;
}

void Player::Release()
{
}

void Player::Update()
{
    if (characterHp <= 0)
    {
        if (isAlive)
        {
            isAlive = false;
            characterStatus = STATUS::DEAD;
            currFrameX = 0;
            changeTimer = 0.0f;
        }
    }
    switch (characterStatus)
    {
    case STATUS::WALK:
        UpdateMove();
        break;
    case STATUS::STAND:
        UpdateStand();
        break;
    case STATUS::FIRE:
        UpdateFire();
        break;
    case STATUS::DEAD:
        UpdateDead();
        break;   
    }
}

void Player::Render(HDC hdc)
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
        //Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
    }
    if (isAlive == false && endDeadScene == false)
    {
        image_Dead->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true, 2);
    }
}

void Player::UpdateMove()
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
    pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    hitBoxPos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    attackBoxPos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    hitBox = GetRectToCenter(hitBoxPos.x, hitBoxPos.y, hitBoxWidth, hitBoxHeight);
    attackRange = GetRectToCenter(attackBoxPos.x, attackBoxPos.y, attackRangeWidth, attackRangeHeight);
    if (pos.x >= WINSIZE_X || pos.x < 0)
    {
        isAlive = false;
    }
}

void Player::UpdateStand()
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
        changeTimer = 0.0f;
        characterStatus = STATUS::FIRE;
        target->SetCharacterHp(characterAtk);
    }
    else if (!findEnemy)
    {
        currFrameX = 0;
        changeTimer = 0.0f;
        characterStatus = STATUS::WALK;
    }
}

void Player::UpdateFire()
{
    changeTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTimer >= 0.07f)
    {
        changeTimer = 0.0f;
        currFrameX++;
        if (currFrameX >= fireMaxFrame)
        {
            currFrameX = 0;
            fireCount = 0.0f;
            currAttackCount = 0;
            readyToFire = false;
            characterStatus = STATUS::STAND;
        }
    }
}

void Player::UpdateDead()
{
    changeTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTimer >= 0.07f)
    {
        changeTimer = 0.0f;
        currFrameX++;
        if (currFrameX > deadMaxFrame)
        {
            currFrameX = 0;
            endDeadScene = true;
        }
    }
}
