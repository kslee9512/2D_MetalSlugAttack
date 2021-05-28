#include "CollisionChecker.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Image.h"
HRESULT CollisionChecker::Init()
{
	maxPlayerBaseHp = 1000.0f;
	playerBaseHp = maxPlayerBaseHp;
	playerBaseHitBox = { 50, 310, 100, 380 };
	maxEnemyBaseHp = 1000.0f;
	enemyBaseHp = maxEnemyBaseHp;
	enemyBaseHitBox = { 880, 310, 910, 380 };
	ImageManager::GetSingleton()->AddImage("enemyhp", "Image/Ui/Red_Bar.bmp", 178, 8, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("playerhp", "Image/Ui/Yellow_Bar.bmp", 178, 8, true, RGB(255, 255, 255));
	player_Hpbar = ImageManager::GetSingleton()->FindImage("playerhp");
	enemy_Hpbar = ImageManager::GetSingleton()->FindImage("enemyhp");
	return S_OK;
}

void CollisionChecker::Release()
{

}

void CollisionChecker::Render(HDC hdc)
{
	if (playerBaseHp >= 0)
	{
		player_Hpbar->PlayerBaseHpRender(hdc, 130, 30, false, playerBaseHp, maxPlayerBaseHp);
	}
	if (enemyBaseHp >= 0)
	{
		enemy_Hpbar->EnemyBaseHpRender(hdc, 887, 30, false, enemyBaseHp, maxEnemyBaseHp);
	}
}

void CollisionChecker::CheckAlive()
{
	//lPlayerCharacter의 iterator->isAlive값이 false의 경우 list에서 삭제
	for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
	{
		if ((*itlPlayerCharacter)->GetCharacterAlive() == false)
		{
			EraseDeadPlayerCharacter(*itlPlayerCharacter);
			break;
		}
	}
	
	//lEnemyCharacter의 iterator->isAlive값이 false의 경우 list에서 삭제
	for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
	{
		if ((*itlEnemyCharacter)->GetCharacterAlive() == false)
		{
			EraseDeadEnemyCharacter(*itlEnemyCharacter);
			break;
		}
	}
}

void CollisionChecker::CheckEnemy()
{
	RECT rc;
	RECT playerAttackRange;
	RECT enemyHitBox;
	RECT enemyBasehitBox = enemyBaseHitBox;
		for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
		{
			playerAttackRange = (*itlPlayerCharacter)->GetAttackBox();
			for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
			{
				enemyHitBox = (*itlEnemyCharacter)->GetHitBox();
				if (IntersectRect(&rc, &enemyHitBox, &playerAttackRange))
				{
					(*itlPlayerCharacter)->SetFindEnemy(true);
					(*itlPlayerCharacter)->SetFindBase(false);
					(*itlPlayerCharacter)->SetTarget((*itlEnemyCharacter));
					break;
				}
				else
				{
					(*itlPlayerCharacter)->SetFindEnemy(false);
					(*itlPlayerCharacter)->SetFindBase(false);
				}
			}
			if (IntersectRect(&rc, &enemyBasehitBox, &playerAttackRange))
			{
				(*itlPlayerCharacter)->SetFindEnemy(false);
				(*itlPlayerCharacter)->SetFindBase(true);
			}
		}
}

void CollisionChecker::CheckPlayer()
{
	RECT rc;
	RECT playerHitBox;
	RECT enemyAttackRange;
	RECT playerBasehitBox = playerBaseHitBox;
	for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
	{
		enemyAttackRange = (*itlEnemyCharacter)->GetAttackBox();
		if (lPlayerCharacter.size() >= 1)
		{
			for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
			{
				playerHitBox = (*itlPlayerCharacter)->GetHitBox();
				if (IntersectRect(&rc, &playerHitBox, &enemyAttackRange) && (*itlPlayerCharacter)->GetCharacterAlive())
				{
					(*itlEnemyCharacter)->SetFindEnemy(true);
					(*itlEnemyCharacter)->SetFindBase(false);
					(*itlEnemyCharacter)->SetTarget((*itlPlayerCharacter));
					break;
				}
				else
				{
					(*itlEnemyCharacter)->SetFindEnemy(false);
					(*itlEnemyCharacter)->SetFindBase(false);
				}
			}
		}
		else if (IntersectRect(&rc, &playerBasehitBox, &enemyAttackRange))
		{
			(*itlEnemyCharacter)->SetFindEnemy(false);
			(*itlEnemyCharacter)->SetFindBase(true);
		}
	}
}

bool CollisionChecker::CheckBaseHp()
{
	if (playerBaseHp <= 0)
	{
		for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
		{
			if ((*itlPlayerCharacter)->GetCharacterAlive())
			{
				(*itlPlayerCharacter)->SetIsAlive(false);
				(*itlEnemyCharacter)->SetCurrFrameX(0);
			}
		}
		for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
		{
			if ((*itlEnemyCharacter)->GetStatus() != STATUS::WIN)
			{
				(*itlEnemyCharacter)->SetStatus(STATUS::WIN);
				(*itlEnemyCharacter)->SetCurrFrameX(0);
			}
		}
		return true;
	}
	else if (enemyBaseHp <= 0)
	{
		for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
		{
			if ((*itlPlayerCharacter)->GetStatus() != STATUS::WIN)
			{
				(*itlPlayerCharacter)->SetStatus(STATUS::WIN);
				(*itlPlayerCharacter)->SetCurrFrameX(0);
			}
		}
		for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
		{
			if ((*itlEnemyCharacter)->GetCharacterAlive())
			{
				(*itlEnemyCharacter)->SetIsAlive(false);
				(*itlEnemyCharacter)->SetCurrFrameX(0);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionChecker::CheckPlayerWin()
{
	if (enemyBaseHp <= 0) return true;
	else return false;
}

bool CollisionChecker::CheckPlayerDefeat()
{
	if (playerBaseHp <= 0) return true;
	else return false;
}
