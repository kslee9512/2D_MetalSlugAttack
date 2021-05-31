#include "LoadingScene.h"
#include "Image.h"
HRESULT LoadingScene::Init()
{
    ImageManager::GetSingleton()->AddImage("loading", "Image/Ui/loading.bmp", 4080, 600, 4, 1, true, RGB(255, 0, 255));
    loadingScene = ImageManager::GetSingleton()->FindImage("loading");
    currFrameX = 0;
    changeTime = 0.0f;
    return S_OK;
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
    changeTime += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTime >= 0.1f)
    {
        changeTime = 0.0f;
        currFrameX++;
        if (currFrameX > 3)
        {
            currFrameX = 0;
        }
    }
}

void LoadingScene::Render(HDC hdc)
{
    loadingScene->FrameRender(hdc, 0, 0, currFrameX, 0, false);
}
