#pragma once
#include "Singleton.h"
#include "Config.h"

class DeckManager : public Singleton<DeckManager>
{
private:
	int deckNumber[5];
public:
	HRESULT Init();
	void Release();

	void SetDeckNumber(int* deckNum, int deckCount);
	int GetDeckNumber(int deckNum);
};

