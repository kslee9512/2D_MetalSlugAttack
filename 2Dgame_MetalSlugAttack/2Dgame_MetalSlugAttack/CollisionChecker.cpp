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
	RECT playerAttackBox;
	RECT playerHitBox;
	RECT enemyHitBox;
	RECT enemyAttackBox;

	//PlayerCharacter의 공격범위에 EnemyCharacter가 들어 올 경우
	for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
	{
		for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
		{
			playerAttackBox = (*itlPlayerCharacter)->GetAttackBox();
			enemyHitBox = (*itlEnemyCharacter)->GetHitBox();

			if (IntersectRect(&rc, &playerAttackBox, &enemyHitBox))
			{
				if (!(*itlPlayerCharacter)->GetFindEnemy())
				{
					(*itlPlayerCharacter)->SetFindEnemy(true);
					(*itlPlayerCharacter)->SetCurrFrameX(0);
					break;
				}
			}
			else if(!IntersectRect(&rc, &playerAttackBox, &enemyHitBox))
			{
				(*itlPlayerCharacter)->SetFindEnemy(false);
			}
		}
	}

	//EnemyCharacter의 공격범위에 PlayerCharacter가 들어 올 경우
	for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
	{
		for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
		{
			playerHitBox = (*itlPlayerCharacter)->GetHitBox();
			enemyAttackBox = (*itlEnemyCharacter)->GetAttackBox();
			if (IntersectRect(&rc, &playerHitBox, &enemyAttackBox))
			{
				if (!(*itlEnemyCharacter)->GetFindEnemy())
				{
					(*itlEnemyCharacter)->SetFindEnemy(true);
					(*itlEnemyCharacter)->SetCurrFrameX(0);
					break;
				}
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
	for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
	{
		for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
		{
			if ((*itlPlayerCharacter)->GetStatus() == STATUS::FIRE && (*itlPlayerCharacter)->GetReadyToFire() && (*itlPlayerCharacter)->GetFindEnemy())
			{
				if ((*itlEnemyCharacter)->GetCharacterHp() > 0)
				{
					(*itlEnemyCharacter)->SetCharacterHp((*itlPlayerCharacter)->GetCharacterAtk());
				}
				if ((*itlEnemyCharacter)->GetCharacterHp() <= 0)
				{
					(*itlEnemyCharacter)->SetStatus(STATUS::DEAD);
				}
				(*itlPlayerCharacter)->SetReadyToFire(false);
				break;
			}
		}
	}
	for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
	{
		for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
		{
			if ((*itlEnemyCharacter)->GetStatus() == STATUS::FIRE && (*itlEnemyCharacter)->GetReadyToFire() && (*itlEnemyCharacter)->GetFindEnemy())
			{
				(*itlEnemyCharacter)->SetReadyToFire(false);
				break;
			}
		}
	}
}
