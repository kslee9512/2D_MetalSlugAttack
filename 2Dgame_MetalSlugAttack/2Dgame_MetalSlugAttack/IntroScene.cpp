#include "IntroScene.h"
#include "Image.h"

HRESULT IntroScene::Init()
{
	ImageManager::GetSingleton()->AddImage("Intro", "Image/Ui/Intro.bmp", 1020, 600, false);
	introScene = ImageManager::GetSingleton()->FindImage("Intro");
	return S_OK;
}

void IntroScene::Release()
{
}

void IntroScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		SceneManager::GetSingleton()->ChangeScene("CustomScene", "LoadingScene");
		return;
	}
}

void IntroScene::Render(HDC hdc)
{
	introScene->Render(hdc, 0, 0, false);
}
