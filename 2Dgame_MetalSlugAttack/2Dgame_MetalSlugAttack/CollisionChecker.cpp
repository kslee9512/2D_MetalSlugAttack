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

void CollisionChecker::CheckEnemy()
{
	RECT rc;
	RECT playerAttackRange;
	RECT playerHitBox;
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
				(*itlPlayerCharacter)->SetFindEnemy(true);
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
				(*itlEnemyCharacter)->SetFindEnemy(true);
			}
			else
			{
				(*itlEnemyCharacter)->SetFindEnemy(false);
			}
		}
	}
}
