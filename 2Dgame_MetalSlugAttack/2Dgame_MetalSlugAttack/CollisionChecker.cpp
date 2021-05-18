#include "CollisionChecker.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "CharacterData.h"

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

void CollisionChecker::CheckAttackRange()
{
	RECT rc;
	RECT playerHitBox;
	RECT playerAttackRange;
	RECT enemyHitBox;
	RECT enemyAttackRange;
	for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
	{
		for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
		{
			playerAttackRange = (*itlPlayerCharacter)->GetAttackBox();
			enemyHitBox = (*itlEnemyCharacter)->GetHitBox();
			if (IntersectRect(&rc, &playerAttackRange, &enemyHitBox))
			{
				if (!((*itlPlayerCharacter)->GetFindEnemy()))
				{
					(*itlPlayerCharacter)->SetFindEnemy(true);
					(*itlPlayerCharacter)->SetCurrFrameX(0);
				}
				break;
			}
			else
			{
				(*itlPlayerCharacter)->SetFindEnemy(false);
			}
		}
	}
	for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
	{
		for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
		{
			playerHitBox = (*itlPlayerCharacter)->GetHitBox();
			enemyAttackRange = (*itlEnemyCharacter)->GetAttackBox();
			if (IntersectRect(&rc, &playerHitBox, &enemyAttackRange))
			{
				if (!(*itlEnemyCharacter)->GetFindEnemy())
				{
					(*itlEnemyCharacter)->SetFindEnemy(true);
					(*itlEnemyCharacter)->SetCurrFrameX(0);
				}
				break;
			}
			else
			{
				(*itlEnemyCharacter)->SetFindEnemy(false);
			}
		}
	}
}

void CollisionChecker::CalcDamage()
{
	RECT rc;
	RECT playerHitBox;
	RECT playerAttackRange;
	RECT enemyHitBox;
	RECT enemyAttackRange;
	for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
	{
		for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
		{
			playerAttackRange = (*itlPlayerCharacter)->GetAttackBox();
			enemyHitBox = (*itlEnemyCharacter)->GetHitBox();
			if (IntersectRect(&rc, &playerAttackRange, &enemyHitBox))
			{
				if ((*itlPlayerCharacter)->GetStatus() == STATUS::FIRE
					&& (*itlPlayerCharacter)->GetCurrAttackCount() < (*itlPlayerCharacter)->GetMaxAttackCount())
				{
					(*itlEnemyCharacter)->SetCharacterHp((*itlPlayerCharacter)->GetCharacterAtk());
					if ((*itlEnemyCharacter)->GetCharacterHp() <= 0)
					{
						(*itlEnemyCharacter)->SetIsAlive(false);
					}
				}
				(*itlPlayerCharacter)->PlusCurrAttackCount();
				if ((*itlPlayerCharacter)->GetStatus() == STATUS::STAND
					&& (*itlPlayerCharacter)->GetCurrAttackCount() >= (*itlPlayerCharacter)->GetMaxAttackCount())
				{
					(*itlPlayerCharacter)->SetCurrAttackCount(0);
				}
			}
		}
	}
}
