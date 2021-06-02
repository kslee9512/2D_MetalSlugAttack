#include "DeckManager.h"

HRESULT DeckManager::Init()
{
    return S_OK;
}

void DeckManager::Release()
{
}

void DeckManager::SetDeckNumber(int* deckNum, int deckCount)
{
    for (int i = 0; i < deckCount; i++)
    {
        deckNumber[i] = deckNum[i];
    }
}

int DeckManager::GetDeckNumber(int deckNum)
{
    return deckNumber[deckNum];
}
