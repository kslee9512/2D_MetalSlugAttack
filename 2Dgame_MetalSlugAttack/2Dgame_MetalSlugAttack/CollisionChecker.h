#pragma once
#include "Player.h"
#include "Enemy.h"
#include <list>

class Player;
class Enemy;
class PlayerManager;
class EnemyManager;
class CollisionChecker
{
private:
	list<Player*> lPlayerCharacter;
	list<Player*>::iterator itlPlayerCharacter;
	list<Enemy*> lEnemyCharacter;
	list<Enemy*>::iterator itlEnemyCharacter;
public:
	void AddPlayerCharacter(Player* characterData) { lPlayerCharacter.push_back(characterData); }
	void EraseDeadPlayerCharacter(Player* characterData) { lPlayerCharacter.remove(characterData); }

	void AddEnemyCharacter(Enemy* characterData) { lEnemyCharacter.push_back(characterData); }
	void EraseDeadEnemyCharacter(Enemy* characterData) { lEnemyCharacter.remove(characterData); }

	void CheckAlive();
	void CheckEnemy();
	bool CheckEndGame();
};