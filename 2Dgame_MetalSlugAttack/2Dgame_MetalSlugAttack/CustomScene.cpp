#include "CustomScene.h"
#include "CommonFunction.h"
#include "Image.h"

HRESULT CustomScene::Init()
{
    startGame = false;
    inImageCurrFrameX = 0;
    attackImageCurrFrameX = 0;
    numberSelected = false;
    ImageManager::GetSingleton()->AddImage("selectBackground", "Image/Background/CustomSceneBackground.bmp", 1020, 600, false);
    ImageManager::GetSingleton()->AddImage("customFrame", "Image/Ui/customFrame.bmp", 108, 154, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("eri_portrait", "Image/Ui/eri_portrait_able.bmp", 80, 80, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("trevor_portrait", "Image/Ui/trevor_portrait_able.bmp", 80, 80, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("ralf_portrait", "Image/Ui/ralf_portrait_able.bmp", 80, 80, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("marco_portrait", "Image/Ui/marco_portrait_able.bmp", 80, 80, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("amber_portrait", "Image/Ui/amber_portrait_able.bmp", 80, 80, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("customNum1", "Image/Ui/customNum1.bmp", 30, 30, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("customNum2", "Image/Ui/customNum2.bmp", 30, 30, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("customNum3", "Image/Ui/customNum3.bmp", 30, 30, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("customNum4", "Image/Ui/customNum4.bmp", 30, 30, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("customNum5", "Image/Ui/customNum5.bmp", 30, 30, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("selectedUnitFrame", "Image/Ui/unit_Frame.bmp", 80, 80, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("In", "Image/Ui/in.bmp", 440, 40, 11, 1, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("attackBackground", "Image/Ui/attackBackground.bmp", 160, 160, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("slug", "Image/Ui/slug.bmp", 1600, 80, 20, 1, true, RGB(255, 0, 255));
    attackBackground = ImageManager::GetSingleton()->FindImage("attackBackground");
    attackRect = { 820, 445, 920, 545 };
    metalSlug = ImageManager::GetSingleton()->FindImage("slug");
    for (int i = 0; i < 5; i++)
    {
        inImage[i] = ImageManager::GetSingleton()->FindImage("In");
    }
    deckNumber[0] = ImageManager::GetSingleton()->FindImage("customNum1");
    deckNumber[1] = ImageManager::GetSingleton()->FindImage("customNum2");
    deckNumber[2] = ImageManager::GetSingleton()->FindImage("customNum3");
    deckNumber[3] = ImageManager::GetSingleton()->FindImage("customNum4");
    deckNumber[4] = ImageManager::GetSingleton()->FindImage("customNum5");
    backGround = ImageManager::GetSingleton()->FindImage("selectBackground");
    //상단 유닛 선택 프레임
    for (int i = 0; i < 5; i++)
    {
        unitSelectFrame[i] = ImageManager::GetSingleton()->FindImage("customFrame");
        unitSelectRect[i] = { 50 + (200 * i), 85, 150 + (200 * i), 225 };
    }
    //유닛 선택 ID값 저장
    for (int i = 0; i < 5; i++)
    {
        selectNum[i] = i + 1;
        deckUnitNum[i] =  1;
    }
    //상단 유닛 선택 프레임 초상화 계산
    for (int i = 0; i < 5; i++)
    {
        if (selectNum[i] == 1)
        {
            unitSelectPortrait[i] = ImageManager::GetSingleton()->FindImage("eri_portrait");
        }
        else if (selectNum[i] == 2)
        {
            unitSelectPortrait[i] = ImageManager::GetSingleton()->FindImage("trevor_portrait");
        }
        else if (selectNum[i] == 3)
        {
            unitSelectPortrait[i] = ImageManager::GetSingleton()->FindImage("ralf_portrait");
        }
        else if (selectNum[i] == 4)
        {
            unitSelectPortrait[i] = ImageManager::GetSingleton()->FindImage("marco_portrait");
        }
        else if (selectNum[i] == 5)
        {
            unitSelectPortrait[i] = ImageManager::GetSingleton()->FindImage("amber_portrait");
        }
    }
    //하단 선택된 유닛 초상화 계산
    for (int i = 0; i < 5; i++)
    {
        if (deckUnitNum[i] == 1)
        {
            selectedUnitPortrait[i] = ImageManager::GetSingleton()->FindImage("eri_portrait");
        }
        else if (deckUnitNum[i] == 2)
        {
            selectedUnitPortrait[i] = ImageManager::GetSingleton()->FindImage("trevor_portrait");
        }
        else if (deckUnitNum[i] == 3)
        {
            selectedUnitPortrait[i] = ImageManager::GetSingleton()->FindImage("ralf_portrait");
        }
        else if (deckUnitNum[i] == 4)
        {
            selectedUnitPortrait[i] = ImageManager::GetSingleton()->FindImage("marco_portrait");
        }
        else if (deckUnitNum[i] == 5)
        {
            selectedUnitPortrait[i] = ImageManager::GetSingleton()->FindImage("amber_portrait");
        }
    }
    for (int i = 0; i < 5; i++)
    {
        deckFrame[i] = ImageManager::GetSingleton()->FindImage("selectedUnitFrame");
        deckRect[i] = { 40 + (150 * i), 440, 120 + (150 * i), 520 };
    }
    inputNum = 0;
    return S_OK;
}

void CustomScene::Release()
{

}

void CustomScene::Update()
{
    if (!startGame)
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            SelectUnit();
            ClickAttack();
        }
        FrameUpdate();
    }
    else if (startGame)
    {
        AttackUpdate();
    }
}

void CustomScene::Render(HDC hdc)
{
    backGround->Render(hdc, 0, 0, false);
    //상단 유닛 프레임
    for (int i = 0; i < 5; i++)
    {
        unitSelectFrame[i]->Render(hdc, 100 + (200 * i), 150, true);
    }
    //for (int i = 0; i < 5; i++)
    //{
    //    Rectangle(hdc, unitSelectRect[i].left, unitSelectRect[i].top, unitSelectRect[i].right, unitSelectRect[i].bottom);
    //}
    //상단 유닛 초상화
    for (int i = 0; i < 5; i++)
    {
        unitSelectPortrait[i]->Render(hdc, 100 + (200 * i), 160, true);
    }
    //In 이미지 출력
    if (numberSelected)
    {
        for (int i = 0; i < 5; i++)
        {
            if (inputNum != deckUnitNum[i])
            {
                inImage[i]->FrameRender(hdc, 80 + (150 * i), 380, inImageCurrFrameX, 0, true, 2);
            }
        }
    }
    //하단 유닛 프레임
    for (int i = 0; i < 5; i++)
    {
        deckFrame[i]->Render(hdc, 80 + (150 * i), 480, true);
    }
    //for (int i = 0; i < 5; i++)
    //{
    //    Rectangle(hdc, deckRect[i].left, deckRect[i].top, deckRect[i].right, deckRect[i].bottom);
    //}
    //하단 유닛 초상화
    for (int i = 0; i < 5; i++)
    {
        selectedUnitPortrait[i]->Render(hdc, 80 + (150 * i), 485, true);
    }
    //하단 유닛 순서 표기용
    for (int i = 0; i < 5; i++)
    {
        deckNumber[i]->Render(hdc, 80 + (150 * i), 550, true);
    }
    attackBackground->Render(hdc, 870, 500, true);
    metalSlug->FrameRender(hdc, 870, 480, attackImageCurrFrameX, 0, true, 2);
}

void CustomScene::SelectUnit()
{
    for (int i = 0; i < 5; i++)
    {
        if (PtInRect(&unitSelectRect[i], g_ptMouse))
        {
            int overlapCount = 0;
            inputNum = selectNum[i];
            numberSelected = true;
            for (int j = 0; j < 5; j++)
            {
                if (deckUnitNum[j] == inputNum)
                {
                    overlapCount++;
                    if (overlapCount == 5)
                    {
                        inputNum = 0;
                        numberSelected = false;
                    }
                }
            }
        }
        if (numberSelected && PtInRect(&deckRect[i], g_ptMouse))
        {
            deckUnitNum[i] = inputNum;
            numberSelected = false;
            ImageUpdate();
        }
    }
}

void CustomScene::ClickAttack()
{
    if (PtInRect(&attackRect, g_ptMouse))
    {
        changeTime = 0.0f;
        startGame = true;
    }
}

void CustomScene::FrameUpdate()
{
    if (numberSelected)
    {
        changeTime += TimerManager::GetSingleton()->GetElapsedTime();
        if (changeTime >= 0.07)
        {
            changeTime = 0.0f;
            inImageCurrFrameX++;
            if (inImageCurrFrameX > 11)
            {
                inImageCurrFrameX = 0;
            }
        }
    }
}

void CustomScene::ImageUpdate()
{
    for (int i = 0; i < 5; i++)
    {
        if (deckUnitNum[i] == 1)
        {
            selectedUnitPortrait[i] = ImageManager::GetSingleton()->FindImage("eri_portrait");
        }
        else if (deckUnitNum[i] == 2)
        {
            selectedUnitPortrait[i] = ImageManager::GetSingleton()->FindImage("trevor_portrait");
        }
        else if (deckUnitNum[i] == 3)
        {
            selectedUnitPortrait[i] = ImageManager::GetSingleton()->FindImage("ralf_portrait");
        }
        else if (deckUnitNum[i] == 4)
        {
            selectedUnitPortrait[i] = ImageManager::GetSingleton()->FindImage("marco_portrait");
        }
        else if (deckUnitNum[i] == 5)
        {
            selectedUnitPortrait[i] = ImageManager::GetSingleton()->FindImage("amber_portrait");
        }
    }
}

void CustomScene::AttackUpdate()
{
    changeTime += TimerManager::GetSingleton()->GetElapsedTime();
    if (changeTime >= 0.07f)
    {
        changeTime = 0.0f;
        attackImageCurrFrameX++;
        if (attackImageCurrFrameX > 19)
        {
            SceneManager::GetSingleton()->ChangeScene("BattleScene", "LoadingScene", deckUnitNum);
            return;
        }
    }
}
