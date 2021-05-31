#pragma once
#include "GameNode.h"
class Image;
class IntroScene : public GameNode
{
private:
	Image* introScene;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

