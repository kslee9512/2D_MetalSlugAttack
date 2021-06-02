#pragma once
#include "Player.h"
#include "Enemy.h"
#include <list>

class Player;
class Enemy;
class PlayerManager;
class EnemyManager;
class CollisionChecker : public GameNode
{
private:
	Image* player_Hpbar;
	Image* enemy_Hpbar;
	char sztext[128];
	float maxPlayerBaseHp;
	float maxEnemyBaseHp;
	float playerBaseHp;
	float enemyBaseHp;
	list<Player*> lPlayerCharacter;
	list<Player*>::iterator itlPlayerCharacter;
	list<Enemy*> lEnemyCharacter;
	list<Enemy*>::iterator itlEnemyCharacter;
	RECT playerBaseHitBox;
	RECT enemyBaseHitBox;
public:
	HRESULT Init();
	void Release();
	void Render(HDC hdc);
	void AddPlayerCharacter(Player* characterData) { lPlayerCharacter.push_back(characterData); }
	void EraseDeadPlayerCharacter(Player* characterData) { lPlayerCharacter.remove(characterData); }

	void AddEnemyCharacter(Enemy* characterData) { lEnemyCharacter.push_back(characterData); }
	void EraseDeadEnemyCharacter(Enemy* characterData) { lEnemyCharacter.remove(characterData); }

	void CheckAlive();
	void CheckEnemy();
	void CheckPlayer();
	void SetEnemyBaseHp(float damage) { this->enemyBaseHp -= damage; }
	void SetPlayerBaseHp(float damage) { this->playerBaseHp -= damage; }
	bool CheckBaseHp();
	float GetPlayerBaseHp() { return this->playerBaseHp; }
	float GetEnemyBaseHp() { return this->enemyBaseHp; }
	bool CheckPlayerWin();
	bool CheckPlayerDefeat();
};