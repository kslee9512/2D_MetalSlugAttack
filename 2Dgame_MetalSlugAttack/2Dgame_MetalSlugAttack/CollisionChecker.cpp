#include "CollisionChecker.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "CharacterData.h"
void CollisionChecker::CheckAlive()
{
	for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
	{
		if (!(*itlPlayerCharacter)->GetCharacterAlive())
		{
			lPlayerCharacter.erase(itlPlayerCharacter);
		}
	}
	for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
	{
		if (!(*itlEnemyCharacter)->GetCharacterAlive())
		{
			lEnemyCharacter.erase(itlEnemyCharacter);
		}
	}
}

void CollisionChecker::CheckAttackRange()
{
	for (itlPlayerCharacter = lPlayerCharacter.begin(); itlPlayerCharacter != lPlayerCharacter.end(); itlPlayerCharacter++)
	{
		for (itlEnemyCharacter = lEnemyCharacter.begin(); itlEnemyCharacter != lEnemyCharacter.end(); itlEnemyCharacter++)
		{
			RECT rc;
			RECT playerRc = (*itlPlayerCharacter)->GetAttackBox();
			RECT enemyRc = (*itlEnemyCharacter)->GetHitBox();
			if (IntersectRect(&rc, &playerRc, &enemyRc))
			{
				int a = 0;
			}
		}
	}
}

void CollisionChecker::TestArray()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD2))
	{
		int a = lPlayerCharacter.size();
		int b = lEnemyCharacter.size();
	}
}
