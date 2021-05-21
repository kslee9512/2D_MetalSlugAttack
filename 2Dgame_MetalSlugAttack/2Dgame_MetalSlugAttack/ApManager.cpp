#include "ApManager.h"

void ApManager::ApCount()
{
	playerApTimer += TimerManager::GetSingleton()->GetElapsedTime();
	enemyApTimer += TimerManager::GetSingleton()->GetElapsedTime();
	apImageCount += TimerManager::GetSingleton()->GetElapsedTime();
	if (apImageCount >= 0.1f)
	{
		apImageCount = 0.0f;
		apCurrFrameX++;
		if (apFrame.canPurchase && (apCurrFrameX > apWalkFrame))
		{
			apCurrFrameX = 0;
		}
		else if (!apFrame.canPurchase && (apCurrFrameX > apPurchaseFrame))
		{
			apCurrFrameX = 0;
			apImageCount = 0.0f;
			apFrame.canPurchase = true;
		}
	}
	if (playerApTimer >= apChargeTime[playerApLevel])
	{
		playerApTimer = 0.0f;
		playerAP++;
		if (playerAP >= maxAp[playerApLevel])
		{
			playerAP = maxAp[playerApLevel];
		}
	}
	if (enemyApTimer >= apChargeTime[enemyApLevel])
	{
		enemyApTimer = 0;
		enemyAP++;
		if (enemyAP >= maxAp[enemyApLevel])
		{
			enemyAP = maxAp[enemyApLevel];
		}
	}
}
