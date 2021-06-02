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
    needTarget = false;
    if (unitNum == 1)
    {
        Name = "Eri";
        unitType = UnitType::PLAYER;
        attackType = AttackType::NORMAL;
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
        characterAtk = 15.0f;
        attackCooltime = 2.0f;
        hitBoxHeight = 50;
        hitBoxWidth = 30;
        hitBoxPos.x = pos.x - hitBoxWidth;
        hitBoxPos.y = pos.y;
        attackRangeWidth = 200;
        attackRangeHeight = 150;
        maxAttackCount = 1;
        attackBoxPos = { pos.x + (attackRangeWidth / 2) - 30, pos.y };
    }
    if (unitNum == 2)
    {
        Name = "Trevor";
        unitType = UnitType::PLAYER;
        attackType = AttackType::NORMAL;
        image_Stand = ImageManager::GetSingleton()->FindImage("Trevor_stand");
        if (image_Stand == nullptr)
        {
            MessageBox(g_hWnd, "Trevor_Stand_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }

        image_Walk = ImageManager::GetSingleton()->FindImage("Trevor_walk");
        if (image_Walk == nullptr)
        {
            MessageBox(g_hWnd, "Trevor_Walk_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Fire = ImageManager::GetSingleton()->FindImage("Trevor_fire");
        if (image_Fire == nullptr)
        {
            MessageBox(g_hWnd, "Trevor_Fire_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Dead = ImageManager::GetSingleton()->FindImage("Trevor_dead");
        if (image_Dead == nullptr)
        {
            MessageBox(g_hWnd, "Trevor_Dead_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Win = ImageManager::GetSingleton()->FindImage("Trevor_win");
        if (image_Win == nullptr)
        {
            MessageBox(g_hWnd, "Trevor_Winready_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        pos.x = 140;
        pos.y = 330;
        moveSpeed = 100.0f;
        walkMaxFrame = 10;
        standMaxFrame = 7;
        fireMaxFrame = 6;
        deadMaxFrame = 17;
        winMaxFrame = 14;
        characterHp = 150;
        characterAtk = 50.0f;
        attackCooltime = 4.0f;
        hitBoxHeight = 50;
        hitBoxWidth = 30;
        hitBoxPos.x = pos.x - 40;
        hitBoxPos.y = pos.y + 20;
        attackRangeWidth = 220;
        attackRangeHeight = 150;
        maxAttackCount = 1;
        attackBoxPos = { pos.x + (attackRangeWidth / 2) - 30, pos.y };
    }
    if (unitNum == 3)
    {
        Name = "Ralf";
        unitType = UnitType::PLAYER;
        attackType = AttackType::NORMAL;
        image_Stand = ImageManager::GetSingleton()->FindImage("Ralf_stand");
        if (image_Stand == nullptr)
        {
            MessageBox(g_hWnd, "Ralf_Stand_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Walk = ImageManager::GetSingleton()->FindImage("Ralf_walk");
        if (image_Walk == nullptr)
        {
            MessageBox(g_hWnd, "Ralf_Walk_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Fire = ImageManager::GetSingleton()->FindImage("Ralf_fire");
        if (image_Fire == nullptr)
        {
            MessageBox(g_hWnd, "Ralf_Fire_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Dead = ImageManager::GetSingleton()->FindImage("Ralf_dead");
        if (image_Dead == nullptr)
        {
            MessageBox(g_hWnd, "Ralf_Dead_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Win = ImageManager::GetSingleton()->FindImage("Ralf_win");
        if (image_Win == nullptr)
        {
            MessageBox(g_hWnd, "Ralf_Winready_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        pos.x = 140;
        pos.y = 330;
        moveSpeed = 110.0f;
        walkMaxFrame = 11;
        standMaxFrame = 5;
        fireMaxFrame = 15;
        deadMaxFrame = 18;
        winMaxFrame = 14;
        characterHp = 350;
        characterAtk = 30.0f;
        attackCooltime = 1.0f;
        hitBoxHeight = 50;
        hitBoxWidth = 30;
        hitBoxPos.x = pos.x - 40;
        hitBoxPos.y = pos.y + 20;
        attackRangeWidth = 50;
        attackRangeHeight = 150;
        maxAttackCount = 1;
        attackBoxPos = { pos.x + (attackRangeWidth / 2) - 30, pos.y };
    }
    if (unitNum == 4)
    {
        Name = "Marco";
        unitType = UnitType::PLAYER;
        attackType = AttackType::NORMAL;
        image_Stand = ImageManager::GetSingleton()->FindImage("Marco_stand");
        if (image_Stand == nullptr)
        {
            MessageBox(g_hWnd, "Marco_Stand_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Walk = ImageManager::GetSingleton()->FindImage("Marco_walk");
        if (image_Walk == nullptr)
        {
            MessageBox(g_hWnd, "Marco_Walk_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Fire = ImageManager::GetSingleton()->FindImage("Marco_fire");
        if (image_Fire == nullptr)
        {
            MessageBox(g_hWnd, "Marco_Fire_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Dead = ImageManager::GetSingleton()->FindImage("Marco_dead");
        if (image_Dead == nullptr)
        {
            MessageBox(g_hWnd, "Marco_Dead_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Win = ImageManager::GetSingleton()->FindImage("Marco_win");
        if (image_Win == nullptr)
        {
            MessageBox(g_hWnd, "Marco_Winready_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        pos.x = 140;
        pos.y = 330;
        moveSpeed = 100.0f;
        walkMaxFrame = 11;
        standMaxFrame = 5;
        fireMaxFrame = 7;
        deadMaxFrame = 18;
        winMaxFrame = 5;
        characterHp = 250;
        characterAtk = 100.0f;
        attackCooltime = 4.0f;
        hitBoxHeight = 50;
        hitBoxWidth = 30;
        hitBoxPos.x = pos.x - 40;
        hitBoxPos.y = pos.y + 20;
        attackRangeWidth = 250;
        attackRangeHeight = 150;
        maxAttackCount = 1;
        attackBoxPos = { pos.x + (attackRangeWidth / 2) - 30, pos.y };
    }
    if (unitNum == 5)
    {
        Name = "Amber";
        unitType = UnitType::PLAYER;
        attackType = AttackType::PIERCE;
        image_Stand = ImageManager::GetSingleton()->FindImage("Amber_stand");
        if (image_Stand == nullptr)
        {
            MessageBox(g_hWnd, "Amber_Stand_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }

        image_Walk = ImageManager::GetSingleton()->FindImage("Amber_walk");
        if (image_Walk == nullptr)
        {
            MessageBox(g_hWnd, "Amber_Walk_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Fire = ImageManager::GetSingleton()->FindImage("Amber_fire");
        if (image_Fire == nullptr)
        {
            MessageBox(g_hWnd, "Amber_Fire_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Dead = ImageManager::GetSingleton()->FindImage("Amber_dead");
        if (image_Dead == nullptr)
        {
            MessageBox(g_hWnd, "Amber_Dead_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        image_Win = ImageManager::GetSingleton()->FindImage("Amber_win");
        if (image_Win == nullptr)
        {
            MessageBox(g_hWnd, "Amber_Winready_Image Load_Fail", "Image_Load Fail", MB_OK);
            return E_FAIL;
        }
        pos.x = 190;
        pos.y = 330;
        moveSpeed = 80.0f;
        walkMaxFrame = 15;
        standMaxFrame = 6;
        fireMaxFrame = 16;
        deadMaxFrame = 9;
        winMaxFrame = 32;
        characterHp = 2500;
        characterAtk = 300.0f;
        attackCooltime = 6.0f;
        hitBoxHeight = 50;
        hitBoxWidth = 30;
        hitBoxPos.x = pos.x - 70;
        hitBoxPos.y = pos.y + 30;
        attackRangeWidth = 240;
        attackRangeHeight = 150;
        maxAttackCount = 1;
        attackBoxPos = { pos.x + (attackRangeWidth / 2) - 80, pos.y };
        needTarget = true;
    }
    attackRange = GetRectToCenter(attackBoxPos.x, attackBoxPos.y, attackRangeWidth, attackRangeHeight);
    hitBox = GetRectToCenter(hitBoxPos.x, hitBoxPos.y, hitBoxWidth, hitBoxHeight);
    collisionChecker->AddPlayerCharacter(this);
    return S_OK;
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
    case STATUS::WIN:
        UpdateWin();
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
    if (findEnemy || findBase)
    {
        currFrameX = 0;
        characterStatus = STATUS::STAND;
    }
    pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    hitBoxPos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    attackBoxPos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    hitBox = GetRectToCenter(hitBoxPos.x, hitBoxPos.y, hitBoxWidth, hitBoxHeight);
    attackRange = GetRectToCenter(attackBoxPos.x, attackBoxPos.y, attackRangeWidth, attackRangeHeight);
    if (pos.x > WINSIZE_X + 100 || pos.x < - 100)
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
    if ((findEnemy || findBase) && readyToFire)
    {
        currFrameX = 0;
        readyToFire = false;
        if (findEnemy && attackType == AttackType::NORMAL)
        {
            target->SetCharacterHp(characterAtk);
        }
        else if (findEnemy && attackType == AttackType::PIERCE)
        {
            list<Enemy*>::iterator itlEnemy;
            for (itlEnemy = ltarget.begin(); itlEnemy != ltarget.end(); itlEnemy++)
            {
                (*itlEnemy)->SetCharacterHp(characterAtk);
            }
        }
        else if (findBase)
        {
            collisionChecker->SetEnemyBaseHp(characterAtk);
        }
        characterStatus = STATUS::FIRE;
    }
    else if (!findEnemy && !findBase)
    {
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
            if (attackType == AttackType::PIERCE)
            {
                needTarget = true;
                ltarget.clear();
            }
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

void Player::UpdateWin()
{
    changeTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTimer >= 0.07f)
    {
        changeTimer = 0.0f;
        currFrameX++;
        if (Name == "Trevor" && currFrameX > winMaxFrame)
        {
            currFrameX = 9;
        }
        else if (Name == "Amber" && currFrameX > winMaxFrame)
        {
            currFrameX = 29;
        }
        else if (Name == "Ralf" && currFrameX > winMaxFrame)
        {
            currFrameX--;
        }
        else if (currFrameX > winMaxFrame)
        {
            currFrameX = 0;
        }
    }
}
