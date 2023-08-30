#include "framework.h"
#include "cMainGame.h"

using namespace Gdiplus;

ULONG_PTR gdiplusToken;

cMainGame::cMainGame()
{
    hBrush, oldBrush;
    hPen, oldPen;
    hbackImage;
    bitBack;
    //backgrund
    hTransparentImage;
    bitTransparent;
    //map
    hcharImage;
    bitChar;
    //char
    hBMImage;
    bitBM;
    //BM
    hUIImage;
    bitUI;
    //UI
    hEnemyImage;
    bitEnemy;
    //Enemy
    hEnemyBMImage;
    bitEnemyBM;
    //EnemyBM

    hDoubleBufferImage;
    rectView;

    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

cMainGame::~cMainGame()
{
    GdiplusShutdown(gdiplusToken);
}

void cMainGame::Boom(HDC hdc, Vector2 _playerPos)
{
    hBrush = CreateSolidBrush(RGB(47, 75, 63));
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    hPen = CreatePen(PS_SOLID, 1, RGB(47, 75, 63));
    oldPen = (HPEN)SelectObject(hdc, hPen);

    Ellipse(hdc, _playerPos.x - 20, _playerPos.y - 20, _playerPos.x + 20, _playerPos.y + 20);

    Damage(_playerPos);

    SelectObject(hdc, oldPen);
    DeleteObject(hPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);
}

void cMainGame::CreateBitmap()
{
    {
        hbackImage = (HBITMAP)LoadImage(NULL, TEXT("image/stage8-2back.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        //ÀÌ¹ÌÁö·Îµå(ÇÚµé,°æ·Î,ÀÌ¹ÌÁöÅ¸ÀÔ,ÀÌÁö¹Ì ³Êºñ,³ôÀÌ,ÀÌ¹ÌÁö¸¦ ÆÄÀÏ·ÎºÎÅÍ ·ÎµåÇÏ°í ¼½¼ÇÀ» »ý¼ºÇÏ´Â ¿É¼Ç )
        if (hbackImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("image load back error"), _T("error"), MB_OK);
            return;
        }
        GetObject(hbackImage, sizeof(BITMAP), &bitBack);
    }
    //backgrund
    {
        hTransparentImage = (HBITMAP)LoadImage(NULL, TEXT("image/stage8-1.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hTransparentImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("image load map error"), _T("error"), MB_OK);
            return;
        }
        GetObject(hTransparentImage, sizeof(BITMAP), &bitTransparent);
    }
    //map
    {
        hcharImage = (HBITMAP)LoadImage(NULL, TEXT("image/char06-0003-1.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        if (hcharImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("image load char error"), _T("error"), MB_OK);
            return;
        }
        GetObject(hcharImage, sizeof(BITMAP), &bitChar);
    }
    //char
    {
        hBMImage = (HBITMAP)LoadImage(NULL, TEXT("image/bullet06-0004.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        if (hBMImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("image load bullet error"), _T("error"), MB_OK);
            return;
        }
        GetObject(hBMImage, sizeof(BITMAP), &bitBM);
    }
    //BM
    {
        hUIImage = (HBITMAP)LoadImage(NULL, TEXT("image/play__0001.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        if (hUIImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("image load ui error"), _T("error"), MB_OK);
            return;
        }
        GetObject(hUIImage, sizeof(BITMAP), &bitUI);
    }
    //UI
    {
        hEnemyImage = (HBITMAP)LoadImage(NULL, TEXT("image/Enemy/char03-0004-0.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        if (hEnemyImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("image load enemychar error"), _T("error"), MB_OK);
            return;
        }
        GetObject(hEnemyImage, sizeof(BITMAP), &bitEnemy);
    }
    //Enemy
    {
        hEnemyBMImage = (HBITMAP)LoadImage(NULL, TEXT("image/Enemy/bullet03-0005.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        if (hEnemyBMImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("image load enemybullet error"), _T("error"), MB_OK);
            return;
        }
        GetObject(hEnemyBMImage, sizeof(BITMAP), &bitEnemyBM);
    }
    //EnemyBM
}

void cMainGame::DeleteBitmap()
{
    DeleteObject(hbackImage);
    DeleteObject(hTransparentImage);
    DeleteObject(hcharImage);
    DeleteObject(hBMImage);
    DeleteObject(hUIImage);
    DeleteObject(hEnemyImage);
    DeleteObject(hEnemyBMImage);
}

void cMainGame::Player(HDC hdc)
{
    COLORREF pixelColor = GetPixel(hdc, playerPos.x, playerPos.y);
    COLORREF flyColor = RGB(47, 75, 63);
    if (pixelColor != flyColor)
    {
        playerPos.y -= 5;
        SetplayerPos(playerPos);
    }
    COLORREF enemypixelColor = GetPixel(hdc, EnemyPos.x, EnemyPos.y);
    if (enemypixelColor != flyColor)
    {
        EnemyPos.y -= 5;
        SetEnemyPos(EnemyPos);
    }

    COLORREF pixelColor2 = GetPixel(hdc, FPPos.x, FPPos.y);
    COLORREF pixelColor3 = GetPixel(hdc, FEPos.x, FEPos.y);
    if (turn == 0)
    {
        if (pixelColor2 != flyColor)
        {
            FPPos.y -= 1;
            SetFPPos(FPPos);
            if (check)
            {
                CharAngle(playerPos, FPPos);
            }
        }
    }
    else 
    {
        if (pixelColor3 != flyColor)
        {
            FEPos.y -= 1;
            SetFEPos(FEPos);
            if (check)
            {
                EnemyAngle(EnemyPos, FEPos);
            }
        }
    }
    //printf("%lf\t %lf\n", FPPos.y, FEPos.y);

    //check 여기서 확인 함 여기서 버그 생김 앞에 좌표 찾는데 구덩이 들어가면 값이 튐
}

HDC hMemDC, hMemDC1, hMemDC2, hMemDC3, hMemDC4, hMemDCEnemy, hMemDCEnemyBM;
HBITMAP hOldBitmap, hOldBitmap1, hOldBitmap2, hOldBitmap3, hOldBitmap4, hOldBitmapEnemy, hOldBitmapEnemyBM;
HDC DoubleDC;
HBITMAP hOldDoubleBitmap;

void cMainGame::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    int bx, by;

    Vector2 result, Enemyresult;
    static int wx = rectView.right / 2, wy = rectView.bottom / 2;
    Vector2 bulletcameraPos;
    if (turn == 0)
    {
        if (!isFired)
        {
            cameraPos.x = playerPos.x - wx;
            cameraPos.y = playerPos.y - wy;
            if (playerPos.x + wx > 1536)
            {
                cameraPos.x = 1536 - 645;
            }
            if (playerPos.y + wy > 671)
            {
                cameraPos.y = 671 - 484;
            }
            if (playerPos.x - wx < 0)
            {
                cameraPos.x = 0;
            }
            if (playerPos.y - wy < 0)
            {
                cameraPos.y = 0;
            }
        }
        else
        {
            result = BM(hWnd, hMemDC3, BMPos, t, GetpowerGauge());

            bulletcameraPos.x = result.x - wx;
            bulletcameraPos.y = result.y - wy;

            if (result.x + wx > 1536)
            {
                bulletcameraPos.x = 1536 - 645;
                if (result.x >= 1536)
                {
                    isFired = false;
                    turn++;
                    t = 0;
                }
            }
            if (result.y + wy > 671)
            {
                bulletcameraPos.y = 671 - 484;
                if (result.y >= 671)
                {
                    isFired = false;
                    turn++;
                    t = 0;
                }
            }
            if (result.x - wx < 0)
            {
                bulletcameraPos.x = 0;
                if (result.x <= 0)
                {
                    isFired = false;
                    turn++;
                    t = 0;
                }
            }
            if (result.y - wy < 0)
            {
                bulletcameraPos.y = 0;
            }
        }
    }
    else
    {
        if (!isFired)
        {
            enemycameraPos.x = EnemyPos.x - wx;
            enemycameraPos.y = EnemyPos.y - wy;
            if (EnemyPos.x + wx > 1536)
            {
                enemycameraPos.x = 1536 - 645;
            }
            if (EnemyPos.y + wy > 671)
            {
                enemycameraPos.y = 671 - 484;
            }
            if (EnemyPos.x - wx < 0)
            {
                enemycameraPos.x = 0;
            }
            if (EnemyPos.y - wy < 0)
            {
                enemycameraPos.y = 0;
            }
        }
        else
        {
            Enemyresult = BM(hWnd, hMemDCEnemyBM, BMPos, t, GetpowerGauge());

            bulletcameraPos.x = Enemyresult.x - wx;
            bulletcameraPos.y = Enemyresult.y - wy;

            if (Enemyresult.x + wx > 1536)
            {
                bulletcameraPos.x = 1536 - 645;
                if (Enemyresult.x >= 1536)
                {
                    isFired = false;
                    turn = 0;
                    t = 0;
                }
            }
            if (Enemyresult.y + wy > 671)
            {
                bulletcameraPos.y = 671 - 484;
                if (Enemyresult.y >= 671)
                {
                    isFired = false;
                    turn = 0;
                    t = 0;
                }
            }
            if (Enemyresult.x - wx < 0)
            {
                bulletcameraPos.x = 0;
                if (Enemyresult.x <= 0)
                {
                    isFired = false;
                    turn = 0;
                    t = 0;
                }
            }
            if (Enemyresult.y - wy < 0)
            {
                bulletcameraPos.y = 0;
            }
        }
    }

    DoubleDC = CreateCompatibleDC(hdc);
    if (hDoubleBufferImage == NULL)
    {
        hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
    }
    hOldDoubleBitmap = (HBITMAP)SelectObject(DoubleDC, hDoubleBufferImage);

    {
        {
            hMemDC = CreateCompatibleDC(DoubleDC);
            hOldBitmap = (HBITMAP)SelectObject(hMemDC, hbackImage);

            bx = bitBack.bmWidth;
            by = bitBack.bmHeight;

            if (turn == 0)
            {
                if (!isFired)
                    BitBlt(DoubleDC, 0, 0, bx, by, hMemDC, cameraPos.x, cameraPos.y, SRCCOPY);
                else
                    BitBlt(DoubleDC, 0, 0, bx, by, hMemDC, bulletcameraPos.x, bulletcameraPos.y, SRCCOPY);
            }
            else
            {
                if (!isFired)
                    BitBlt(DoubleDC, 0, 0, bx, by, hMemDC, enemycameraPos.x, enemycameraPos.y, SRCCOPY);
                else
                    BitBlt(DoubleDC, 0, 0, bx, by, hMemDC, bulletcameraPos.x, bulletcameraPos.y, SRCCOPY);
            }


            SelectObject(hMemDC, hOldBitmap);
            DeleteDC(hMemDC);
        }
        {
            hMemDC1 = CreateCompatibleDC(DoubleDC);
            hOldBitmap1 = (HBITMAP)SelectObject(hMemDC1, hTransparentImage);

            bx = rectView.right;
            by = rectView.bottom;
            //화면 크기 

            //이미지 크기를 전체 크기를 불러오는 것이 아니라 화면 만금의 크기를 가져와야함
            //661, 543
            if (turn == 0)
            {
                if (!isFired)
                    TransparentBlt(DoubleDC, 0, 0, bx, by, hMemDC1, cameraPos.x, cameraPos.y, bx, by, RGB(47, 75, 63));
                else
                    TransparentBlt(DoubleDC, 0, 0, bx, by, hMemDC1, bulletcameraPos.x, bulletcameraPos.y, bx, by, RGB(47, 75, 63));
            }
            else
            {
                if (!isFired)
                    TransparentBlt(DoubleDC, 0, 0, bx, by, hMemDC1, enemycameraPos.x, enemycameraPos.y, bx, by, RGB(47, 75, 63));
                else
                    TransparentBlt(DoubleDC, 0, 0, bx, by, hMemDC1, bulletcameraPos.x, bulletcameraPos.y, bx, by, RGB(47, 75, 63));
            }
        }

        {
            hMemDC2 = CreateCompatibleDC(DoubleDC);
            hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hcharImage);
            //32/32
            hMemDCEnemy = CreateCompatibleDC(DoubleDC);
            hOldBitmapEnemyBM = (HBITMAP)SelectObject(hMemDCEnemy, hEnemyImage);
            //35/28

            bx = bitChar.bmWidth;
            by = bitChar.bmHeight;
            //캐릭터

            int ebx = bitEnemy.bmWidth;
            int eby = bitEnemy.bmHeight;
            //적 캐릭터

            

            if (turn == 0)
            {
                if (!isFired)
                {
                    RotateImage(DoubleDC, hcharImage, playerPos.x - cameraPos.x - 16, playerPos.y - cameraPos.y - 32, bx, by, bpAngle);
                    //TransparentBlt(DoubleDC, playerPos.x - cameraPos.x - 16, playerPos.y - cameraPos.y - 32, bx, by, hMemDC2, 0, 0, bx, by, RGB(47, 75, 63));
                }
                else
                    TransparentBlt(DoubleDC, playerPos.x - bulletcameraPos.x - 16, playerPos.y - bulletcameraPos.y - 32, bx, by, hMemDC2, 0, 0, bx, by, RGB(47, 75, 63));
                if (!isFired)
                    TransparentBlt(DoubleDC, EnemyPos.x - cameraPos.x - 17, EnemyPos.y - cameraPos.y - 28, ebx, eby, hMemDCEnemy, 0, 0, ebx, eby, RGB(47, 75, 63));
                else
                    TransparentBlt(DoubleDC, EnemyPos.x - bulletcameraPos.x - 17, EnemyPos.y - bulletcameraPos.y - 28, ebx, eby, hMemDCEnemy, 0, 0, ebx, eby, RGB(47, 75, 63));

            }
            else
            {
                if (!isFired)
                    TransparentBlt(DoubleDC, playerPos.x - enemycameraPos.x - 16, playerPos.y - enemycameraPos.y - 32, bx, by, hMemDC2, 0, 0, bx, by, RGB(47, 75, 63));
                else
                    TransparentBlt(DoubleDC, playerPos.x - bulletcameraPos.x - 16, playerPos.y - bulletcameraPos.y - 32, bx, by, hMemDC2, 0, 0, bx, by, RGB(47, 75, 63));
                if (!isFired)
                    TransparentBlt(DoubleDC, EnemyPos.x - enemycameraPos.x - 17, EnemyPos.y - enemycameraPos.y - 28, ebx, eby, hMemDCEnemy, 0, 0, ebx, eby, RGB(47, 75, 63));
                else
                    TransparentBlt(DoubleDC, EnemyPos.x - bulletcameraPos.x - 17, EnemyPos.y - bulletcameraPos.y - 28, ebx, eby, hMemDCEnemy, 0, 0, ebx, eby, RGB(47, 75, 63));
            }

            DeleteDC(hMemDC2);
            DeleteDC(hMemDCEnemy);
        }
        //캐릭터 까지 그리기는 완료
        if (turn == 0)
        {
            if (isFired)
            {
                hMemDC3 = CreateCompatibleDC(DoubleDC);
                hOldBitmap3 = (HBITMAP)SelectObject(hMemDC3, hBMImage);

                bx = bitBM.bmWidth;
                by = bitBM.bmHeight;

                Draw(hWnd, hdc, result);

                TransparentBlt(DoubleDC, result.x - bulletcameraPos.x, result.y - bulletcameraPos.y, bx, by, hMemDC3, 0, 0, bx, by, RGB(47, 75, 63));

                DeleteDC(hMemDC3);
            }
        }
        else
        {
            if (isFired)
            {
                hMemDCEnemyBM = CreateCompatibleDC(DoubleDC);
                hOldBitmapEnemyBM = (HBITMAP)SelectObject(hMemDCEnemyBM, hEnemyBMImage);

                bx = bitEnemyBM.bmWidth;
                by = bitEnemyBM.bmHeight;

                Draw(hWnd, hdc, Enemyresult);

                TransparentBlt(DoubleDC, Enemyresult.x - bulletcameraPos.x, Enemyresult.y - bulletcameraPos.y, bx, by, hMemDCEnemyBM, 0, 0, bx, by, RGB(47, 75, 63));

                DeleteDC(hMemDCEnemyBM);
            }
        }
        //여기서 터져서 원을 그리면 turn을 증가 시킴 아직 확인을 안함
        {
            hMemDC4 = CreateCompatibleDC(DoubleDC);
            hOldBitmap4 = (HBITMAP)SelectObject(hMemDC4, hUIImage);

            bx = bitUI.bmWidth;
            by = bitUI.bmHeight;
            TransparentBlt(DoubleDC, 0, rectView.bottom - 159, bx, by, hMemDC4, 0, 0, bx, by, RGB(47, 75, 63));

            DeleteDC(hMemDC4);
        }

        Player(hMemDC1);

        DeleteDC(hMemDC1);
    }

    TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, DoubleDC, 0, 0, rectView.right, rectView.bottom, RGB(47, 75, 63));

    SelectObject(DoubleDC, hOldDoubleBitmap);
    DeleteDC(DoubleDC);
}

void cMainGame::SetbpAngle(double _bpAngle)
{
    bpAngle = _bpAngle;
}

double& cMainGame::GetbpAngle()
{
    return bpAngle;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetbeAngle(double _beAngle)
{
    beAngle = _beAngle;
}

double& cMainGame::GetbeAngle()
{
    return beAngle;
    // TODO: 여기에 return 문을 삽입합니다.
}

double cMainGame::AngleInRadians(double angle)
{
    revec = (angle * PI) / 180.0;
    return revec;
}

Vector2 cMainGame::BM(HWND hWnd, HDC hdc, Vector2 _BMPos, double t, double _powerGauge)
{

    if (turn == 0)
    {
        bulletPosx = (_powerGauge / 10) * t * _BMPos.x;
        bulletPosy = (-1) * ((_powerGauge / 10) * t * _BMPos.y - (0.5 * g * t * t));

        return Vector2(bulletPosx + playerPos.x, bulletPosy + playerPos.y - 16);
    }
    else
    {
        bulletPosx = (-1) * (_powerGauge / 10) * t * _BMPos.x;
        bulletPosy = (-1) * ((_powerGauge / 10) * t * _BMPos.y - (0.5 * g * t * t));

        return Vector2(bulletPosx + EnemyPos.x, bulletPosy + EnemyPos.y - 16);
    }


}

void cMainGame::Draw(HWND hWnd, HDC hdc, Vector2 _playerPos) // 그리기
{
    COLORREF pixelColor = GetPixel(hMemDC1, _playerPos.x, _playerPos.y);
    COLORREF flyColor = RGB(47, 75, 63);

    if (_playerPos.y > 0)
    {
        if (turn == 0)
        {
            if (pixelColor != flyColor)
            {
                Boom(hMemDC1, _playerPos);
                isFired = false;
                t = 0;
            }
        }
        else
        {
            if (pixelColor != flyColor)
            {
                Boom(hMemDC1, _playerPos);
                isFired = false;
                t = 0;
            }
        }
    }
}

void cMainGame::Damage(Vector2 _playerPos)
{
    double direction, Edirection;
    double angleRad, EangleRad;
    double minDirection, EminDirection;

    direction = sqrt(pow(playerPos.x - _playerPos.x, 2) + pow(playerPos.y - _playerPos.y, 2));

    angleRad = atan((_playerPos.x - playerPos.x) / direction);
    minDirection = 16 / cos(angleRad);

    Edirection = sqrt(pow(EnemyPos.x - _playerPos.x, 2) + pow(EnemyPos.y - _playerPos.y, 2));

    EangleRad = atan((_playerPos.x - EnemyPos.x) / Edirection);
    EminDirection = 16 / cos(EangleRad);

    if (20 + minDirection > direction)
    {
        playerHP -= 20;
        printf("player : %d Enemy : %d\n", playerHP, EnemyHP);
        //자신 플레이어 한테 데미지 
        //추가로 넓이를 구해서 데미지 차별을 주면 좋을 텐데
    }
    else if (20 + EminDirection > Edirection)
    {
        EnemyHP -= 20;
        printf("player : %d Enemy : %d\n", playerHP, EnemyHP);
    }
    else
    {
        printf("NoDamage\n");
    }
    //적 위치를 추가해서 데미지를 주는 것 추가
    if (turn == 0)
        turn++;
    else
        turn = 0;
}

void cMainGame::CharAngle(Vector2 _playerPos, Vector2 _FPPos)
{
    double dx = _FPPos.x - _playerPos.x;
    double dy = _FPPos.y - _playerPos.y;
    double hypotenuse = sqrt(pow(dx, 2) + pow(dy, 2));
    //빗변 구하기

    double angleRad = atan(dy / dx);
    //각도로 변환

    double angleDeg = angleRad * (180.0 / PI);
    //vec에 더하는 도 단위 또는 이미지 회전에 사용하는 도
    //이미지 회전은 이녀석으로

    bpAngle = vec + (-1 * angleDeg);

    printf("bpAngle : %lf \t vec : %lf \t angleDeg : %lf \t playerPos : %lf %lf \t FPPos : %lf %lf\n \n", bpAngle, vec, angleDeg, playerPos.x, playerPos.y, FPPos.x, FPPos.y);
    check = false;

}

void cMainGame::EnemyAngle(Vector2 _EnemyPos, Vector2 _FEPos)
{
    double dx = _FEPos.x - _EnemyPos.x;
    double dy = _FEPos.y - _EnemyPos.y;
    double hypotenuse = sqrt(pow(dx, 2) + pow(dy, 2));
    //빗변 구하기

    double angleRad = atan(dy / dx);
    //각도로 변환

    double angleDeg = angleRad * (180.0 / PI);
    //vec에 더하는 도 단위 또는 이미지 회전에 사용하는 도
    //이미지 회전은 이녀석으로

    beAngle = Evec + (-1 * angleDeg);

    printf("beAngle : %lf \t vec : %lf \t angleDeg : %lf \t EnemyPos : %lf %lf \t FEPos : %lf %lf\n \n", beAngle, Evec, angleDeg, EnemyPos.x, EnemyPos.y, FEPos.x, FEPos.y);

    check = false;
}

void cMainGame::RotateImage(HDC hdc, HBITMAP hBitmap, int playerPosx, int playerPosy, int dx, int dy, double angle)
{

    Graphics graphics(hdc);
    Image* pImg = nullptr;
    pImg = Image::FromFile((WCHAR*)L"image/char06-0003-1.bmp");
    int xPos = playerPosx;
    int yPos = playerPosy;
    if (pImg)
    {
        int w = pImg->GetWidth();
        int h = pImg->GetHeight();

        Gdiplus::Matrix mat;
        mat.RotateAt(angle, Gdiplus::PointF(xPos + (float)(w / 2), yPos ));
        //돌리는 위치 
        graphics.SetTransform(&mat);
        graphics.DrawImage(pImg, xPos, yPos, w, h);

        //이미지가 좌 상단에 잡혀있어서 시계방향으로 돌고 있음

        mat.Reset();
        graphics.SetTransform(&mat);
        //이 그림에만 돌리는 reset
    }
}

void cMainGame::SetplayerPos(Vector2 _playerPos)
{
    playerPos.x = _playerPos.x;
    playerPos.y = _playerPos.y;
}
Vector2& cMainGame::GetplayerPos()
{
    return playerPos;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetEnemyPos(Vector2 _EnemyPos)
{
    EnemyPos.x = _EnemyPos.x;
    EnemyPos.y = _EnemyPos.y;
}

Vector2& cMainGame::GetEnemyPos()
{
    return EnemyPos;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetrectView(RECT _rectView)
{
    rectView.bottom = _rectView.bottom;
    rectView.left = _rectView.left;
    rectView.right = _rectView.right;
    rectView.top = _rectView.top;
}
RECT cMainGame::GetrectView()
{
    return rectView;
}

void cMainGame::SetAngle(double _vec)
{
    vec = _vec;
}
double& cMainGame::GetAngle()
{
    return vec;
}

void cMainGame::SetEAngle(double _Evec)
{
    Evec = _Evec;
}

double& cMainGame::GetEAngle()
{
    return Evec;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetTime(double _t)
{
    t = _t;
}
double& cMainGame::GetTime()
{
    return t;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetFire(bool _isFired)
{
    isFired = _isFired;
}
bool& cMainGame::GetFire()
{
    return isFired;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetCheck(bool _check)
{
    check = _check;
}

bool& cMainGame::GetCheck()
{
    return check;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetpowerGauge(double _powerGauge)
{
    powerGauge = _powerGauge;
}

double& cMainGame::GetpowerGauge()
{
    return powerGauge;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetmousePos(Vector2 _mousePos)
{
    mousePos.x = _mousePos.x;
    mousePos.y = _mousePos.y;
}

Vector2& cMainGame::GetmousePos()
{
    return mousePos;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetcameraPos(Vector2 _cameraPos)
{
    cameraPos.x = _cameraPos.x;
    cameraPos.y = _cameraPos.y;
}

Vector2& cMainGame::GetcameraPos()
{
    return cameraPos;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetFPPos(Vector2 _playerPos)
{
    FPPos.x = _playerPos.x;
    FPPos.y = _playerPos.y;
}

Vector2& cMainGame::GetFPPos()
{
    return FPPos;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetTurn(int _turn)
{
    turn = _turn;
}

int& cMainGame::GetTurn()
{
    return turn;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetFEPos(Vector2 _EnemyPos)
{
    FEPos.x = _EnemyPos.x;
    FEPos.y = _EnemyPos.y;
}

Vector2& cMainGame::GetFEPos()
{
    return FEPos;
    // TODO: 여기에 return 문을 삽입합니다.
}

Vector2 cMainGame::SetBMPos(double _vec)
{
    BMPos.x = cos(AngleInRadians(_vec));
    BMPos.y = sin(AngleInRadians(_vec));

    return Vector2(BMPos.x, BMPos.y);
}

Vector2& cMainGame::GetBMPos()
{
    return BMPos;
}