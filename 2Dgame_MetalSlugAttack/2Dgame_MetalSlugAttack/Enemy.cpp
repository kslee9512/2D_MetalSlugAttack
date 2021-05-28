#include "Enemy.h"
#include "CollisionChecker.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT Enemy::Init(int unitNum, CollisionChecker* collisionChecker)
{
    this->collisionChecker = collisionChecker;
    endDeadScene = false;
    fireCount = 0.0f;
    changeTimer = 0.0f; // 프레임 변경 확인용 타이머
    currFrameX = 0; //캐릭터 이미지 전환용 프레임
    isAlive = true;
    characterStatus = STATUS::STAND;
    findEnemy = false;
    findBase = false;
    readyToFire = true;
    currAttackCount = 0;
    if (unitNum == 1)
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
        characterAtk = 20.0f;
        attackCooltime = 3.0f;
        hitBoxHeight = 50;
        hitBoxWidth = 30;
        hitBoxPos = { pos.x + hitBoxWidth, pos.y };
        attackRangeWidth = 250;
        attackRangeHeight = 150;
        maxAttackCount = 1;
        attackBoxPos = { pos.x - 220 + 10, pos.y - attackRangeHeight / 2 };
        attackRange = GetRectToCenter(attackBoxPos.x, attackBoxPos.y, attackRangeWidth, attackRangeHeight);
    }
    else if (unitNum == 2)
    {
        Name = "방패병";
        unitType = UnitType::ENEMY;
        image_Stand = ImageManager::GetSingleton()->FindImage("shield_stand");
        if (image_Stand == nullptr)
        {
            MessageBox(g_hWnd, "shield_stand_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }

        image_Walk = ImageManager::GetSingleton()->FindImage("shield_walk");
        if (image_Walk == nullptr)
        {
            MessageBox(g_hWnd, "shield_walk_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Fire = ImageManager::GetSingleton()->FindImage("shield_attack");
        if (image_Fire == nullptr)
        {
            MessageBox(g_hWnd, "shield_attack_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Dead = ImageManager::GetSingleton()->FindImage("shield_dead");
        if (image_Dead == nullptr)
        {
            MessageBox(g_hWnd, "shield_dead_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Win = ImageManager::GetSingleton()->FindImage("shield_win");
        if (image_Win == nullptr)
        {
            MessageBox(g_hWnd, "shield_win_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        pos.x = WINSIZE_X - 180;
        pos.y = 325;
        moveSpeed = 50.0f;
        standMaxFrame = 5;
        fireMaxFrame = 15;
        walkMaxFrame = 8;
        winMaxFrame = 3;
        deadMaxFrame = 11;
        characterHp = 400;
        characterAtk = 50.0f;
        attackCooltime = 8.0f;
        hitBoxHeight = 50;
        hitBoxWidth = 30;
        hitBoxPos = { pos.x + hitBoxWidth / 2, pos.y + hitBoxHeight / 2 };
        attackRangeWidth = 50;
        attackRangeHeight = 150;
        maxAttackCount = 1;
        attackBoxPos = { pos.x  - 20, pos.y - attackRangeHeight / 2 };
        attackRange = GetRectToCenter(attackBoxPos.x, attackBoxPos.y, attackRangeWidth, attackRangeHeight);
    }
    else if (unitNum == 3)
    {
        Name = "알렌오닐";
        unitType = UnitType::ENEMY;
        image_Stand = ImageManager::GetSingleton()->FindImage("allen_stand");
        image_Walk = ImageManager::GetSingleton()->FindImage("allen_walk");
        image_Fire = ImageManager::GetSingleton()->FindImage("allen_fire");
        image_Dead = ImageManager::GetSingleton()->FindImage("allen_dead");
        image_Win = ImageManager::GetSingleton()->FindImage("allen_stand");
        pos.x = WINSIZE_X - 230;
        pos.y = 330;
        moveSpeed = 70.0f;
        standMaxFrame = 13;
        fireMaxFrame = 8;
        walkMaxFrame = 9;
        winMaxFrame = 9;
        deadMaxFrame = 13;
        characterHp = 800;
        characterAtk = 100.0f;
        attackCooltime = 4.0f;
        hitBoxHeight = 50;
        hitBoxWidth = 30;
        hitBoxPos = { pos.x + 60, pos.y };
        attackRangeWidth = 400;
        attackRangeHeight = 150;
        maxAttackCount = 1;
        attackBoxPos = { pos.x  - 300, pos.y - attackRangeHeight / 2 };
        attackRange = GetRect(attackBoxPos.x, attackBoxPos.y,  attackRangeWidth , attackRangeHeight);
    }
    hitBox = GetRectToCenter(pos.x , pos.y, hitBoxWidth, hitBoxHeight);
    collisionChecker->AddEnemyCharacter(this);
	return E_NOTIMPL;
}

void Enemy::Release()
{
}

void Enemy::Update()
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
    case STATUS::WIN:
        UpdateWin();
        break;
    }
}

void Enemy::Render(HDC hdc)
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

void Enemy::UpdateMove()
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
    if (findEnemy || findBase)
    {
        currFrameX = 0;
        characterStatus = STATUS::STAND;
    }

    pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    hitBoxPos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    attackBoxPos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    hitBox = GetRectToCenter(hitBoxPos.x, hitBoxPos.y, hitBoxWidth, hitBoxHeight);
    attackRange = GetRect(attackBoxPos.x, attackBoxPos.y, attackRangeWidth , attackRangeHeight);

    if (pos.x >= WINSIZE_X || pos.x < 0)
    {
        isAlive = false;
    }
}

void Enemy::UpdateStand()
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
    if ((findEnemy || findBase) && readyToFire)
    {
        currFrameX = 0;
        readyToFire = false;
        if (findEnemy)
        {
            target->SetCharacterHp(characterAtk);
        }
        else if (findBase)
        {
            collisionChecker->SetPlayerBaseHp(characterAtk);
        }
        characterStatus = STATUS::FIRE;
    }
    else if (!findEnemy && !findBase)
    {
        characterStatus = STATUS::WALK;
    }
}

void Enemy::UpdateFire()
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
            characterStatus = STATUS::STAND;
        }
    }
}

void Enemy::UpdateDead()
{
    changeTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTimer >= 0.07f)
    {
        changeTimer = 0.0f;
        currFrameX++;
        if (currFrameX > deadMaxFrame)
        {
            endDeadScene = true;
            currFrameX = 0;
        }
    }
}

void Enemy::UpdateWin()
{
    changeTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTimer >= 0.07f)
    {
        changeTimer = 0.0f;
        currFrameX++;
        if (currFrameX > winMaxFrame)
        {
            currFrameX = 0;
        }
    }
}
