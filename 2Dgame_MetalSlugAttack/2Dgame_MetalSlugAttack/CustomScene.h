#pragma once
#include "GameNode.h"

class Image;
class CustomScene : public GameNode
{
private:
	Image* backGround;
	Image* unitSelectFrame[5];
	Image* deckFrame[5];
	Image* deckNumber[5];
	Image* unitSelectPortrait[5];
	Image* selectedUnitPortrait[5];
	Image* inImage[5];
	Image* attackBackground;
	Image* metalSlug;
	RECT unitSelectRect[5];
	RECT deckRect[5];
	RECT attackRect;
	int selectNum[5];
	int deckUnitNum[5]; //BattleScene에 넘겨줄 변수배열
	int inputNum;
	int inImageCurrFrameX;
	int attackImageCurrFrameX;
	bool numberSelected;
	bool startGame;
	float changeTime;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	
	void SelectUnit();
	void ClickAttack();
	void FrameUpdate();
	void ImageUpdate();
	void AttackUpdate();
	virtual ~CustomScene() {};
};

