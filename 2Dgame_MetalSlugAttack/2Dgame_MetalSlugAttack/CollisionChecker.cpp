#include "CollisionChecker.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Enemy.h"

HRESULT CollisionChecker::Init()
{
	playerBaseHp = 1000;
	playerBaseHitBox = { 50, 310, 100, 380 };
	enemyBaseHp = 1000;
	enemyBaseHitBox = { 860, 310, 910, 380 };
	return S_OK;
}

void CollisionChecker::Release()
{

}

void CollisionChecker::Render(HDC hdc)
{
	wsprintf(sztext, "%d , %d", playerBaseHp, enemyBaseHp);
	TextOut(hdc, 200, 400, sztext, strlen(sztext));
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
	RECT playerHitBox;
	RECT enemyHitBox;
	RECT enemyAttackRange;
	RECT playerBasehitBox = playerBaseHitBox;
	RECT enemyBasehitBox = enemyBaseHitBox;
	if (lPlayerCharacter.size() >= 1)
	{
		for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
		{
			playerAttackRange = (*itlPlayerCharacter)->GetAttackBox();
			if (lEnemyCharacter.size() >= 1)
			{
				for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
				{
					
					enemyHitBox = (*itlEnemyCharacter)->GetHitBox();
					if (IntersectRect(&rc, &playerAttackRange, &enemyHitBox)
						&& ((*itlPlayerCharacter)->GetStatus() == STATUS::WALK
							|| (*itlPlayerCharacter)->GetStatus() == STATUS::STAND))
					{
						(*itlPlayerCharacter)->SetFindEnemy(true);
						(*itlPlayerCharacter)->SetFindBase(false);
						(*itlPlayerCharacter)->SetTarget((*itlEnemyCharacter));
						break;
					}
				}
			}
			else if (IntersectRect(&rc, &playerAttackRange, &enemyBasehitBox))
			{
				(*itlPlayerCharacter)->SetFindEnemy(true);
				(*itlPlayerCharacter)->SetFindBase(true);
			}
			else
			{
				(*itlPlayerCharacter)->SetFindEnemy(false);
				(*itlPlayerCharacter)->SetFindBase(false);
			}
		}
	}
	if (lEnemyCharacter.size() >= 1)
	{
		for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
		{
			enemyAttackRange = (*itlEnemyCharacter)->GetAttackBox();
			if (lPlayerCharacter.size() >= 1)
			{
				for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
				{
					playerHitBox = (*itlPlayerCharacter)->GetHitBox();
					if (IntersectRect(&rc, &playerHitBox, &enemyAttackRange))
					{
						(*itlEnemyCharacter)->SetFindEnemy(true);
						(*itlEnemyCharacter)->SetFindBase(false);
						(*itlEnemyCharacter)->SetTarget((*itlPlayerCharacter));
						break;
					}
				}
			}
			else if (IntersectRect(&rc, &playerBasehitBox, &enemyAttackRange)) 
			{
				(*itlEnemyCharacter)->SetFindBase(true);
				(*itlEnemyCharacter)->SetFindEnemy(true);
			}
			else
			{
				(*itlEnemyCharacter)->SetFindEnemy(false);
				(*itlEnemyCharacter)->SetFindBase(false);
			}
		}
	}
}

bool CollisionChecker::CheckBaseHp()
{
	if (playerBaseHp <= 0)
	{
		for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
		{
			(*itlPlayerCharacter)->SetIsAlive(false);
		}
		for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
		{
			(*itlEnemyCharacter)->SetStatus(STATUS::WIN);
		}
		return true;
	}
	else if (enemyBaseHp <= 0)
	{
		for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
		{
			(*itlPlayerCharacter)->SetStatus(STATUS::WIN);
		}
		for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
		{
			(*itlEnemyCharacter)->SetIsAlive(false);
		}
		return true;
	}
	else
	{
		return false;
	}
}
