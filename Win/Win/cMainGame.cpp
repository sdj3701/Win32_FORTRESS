#include "framework.h"
#include "cMainGame.h"

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
    hDoubleBufferImage;
    rectView;

}

cMainGame::~cMainGame()
{
    
}

void cMainGame::Boom(HDC hdc, Vector2 _playerPos)
{
    hBrush = CreateSolidBrush(RGB(47, 75, 63));
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    hPen = CreatePen(PS_SOLID, 1, RGB(47, 75, 63));
    oldPen = (HPEN)SelectObject(hdc, hPen);
    //playerPos는 플레이어 가운데 위치
    //여기서 겹치는지 확인
    Ellipse(hdc, _playerPos.x  - 20, _playerPos.y - 20, _playerPos.x  + 20, _playerPos.y  + 20);
    
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
}

void cMainGame::DeleteBitmap()
{
    DeleteObject(hbackImage);
    DeleteObject(hTransparentImage);
    DeleteObject(hcharImage);
    DeleteObject(hBMImage);
    DeleteObject(hUIImage);
}

void cMainGame::Player(HDC hdc)
{
    //여기는 색이 같다고 오류가 남
    COLORREF pixelColor = GetPixel(hdc, playerPos.x, playerPos.y);
    COLORREF flyColor = RGB(47, 75, 63);
    if (pixelColor != flyColor)
    {
        playerPos.y -= 5;
        SetplayerPos(playerPos);
    }
}

HDC hMemDC, hMemDC1, hMemDC2, hMemDC3, hMemDC4;
HBITMAP hOldBitmap, hOldBitmap1, hOldBitmap2, hOldBitmap3, hOldBitmap4;
HDC DoubleDC;
HBITMAP hOldDoubleBitmap;

void cMainGame::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    int bx, by;
    
    Vector2 result;
    static int wx=rectView.right/2, wy= rectView.bottom/2;
    Vector2 bulletcameraPos;
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
                t = 0;
            }
        }
        if (result.y + wy > 671)
        {
            bulletcameraPos.y = 671 - 484;
            if (result.y >= 671)
            {
                isFired = false;
                t = 0;
            }
        }
        if (result.x - wx < 0)
        {
            bulletcameraPos.x = 0;
            if (result.x <= 0)
            {
                isFired = false;
                t = 0;
            }
        }
        if (result.y - wy < 0)
        {
            bulletcameraPos.y = 0;
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

            //Ellipse(hMemDC, playerPos.x - 10, playerPos.y - 10, playerPos.x + 10, playerPos.y + 10);
            if(!isFired)
                BitBlt(DoubleDC, 0, 0, bx, by, hMemDC, cameraPos.x, cameraPos.y, SRCCOPY);
            else
                BitBlt(DoubleDC, 0, 0, bx, by, hMemDC, bulletcameraPos.x, bulletcameraPos.y, SRCCOPY);

            SelectObject(hMemDC, hOldBitmap);
            DeleteDC(hMemDC);
        }
        {
            hMemDC1 = CreateCompatibleDC(DoubleDC);
            hOldBitmap1 = (HBITMAP)SelectObject(hMemDC1, hTransparentImage);

            bx = rectView.right;
            by = rectView.bottom ;
            //화면 크기 
            
            //이미지 크기를 전체 크기를 불러오는 것이 아니라 화면 만금의 크기를 가져와야함
            //661, 543
            if (!isFired)
                TransparentBlt(DoubleDC, 0, 0, bx, by, hMemDC1, cameraPos.x, cameraPos.y, bx, by, RGB(47, 75, 63));
            else
                TransparentBlt(DoubleDC, 0, 0, bx, by, hMemDC1, bulletcameraPos.x, bulletcameraPos.y, bx, by, RGB(47, 75, 63));

        }
        {
            hMemDC2 = CreateCompatibleDC(DoubleDC);
            hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hcharImage);
            //32/32
            bx = bitChar.bmWidth;
            by = bitChar.bmHeight;
            //캐릭터

            //Rectangle(hdc, playerPos.x - 16, playerPos.y - 16, playerPos.x + 16, playerPos.y + 16);

            if (!isFired)
                TransparentBlt(DoubleDC, playerPos.x- cameraPos.x -16, playerPos.y - cameraPos.y-32, bx, by, hMemDC2, 0 , 0 , bx, by, RGB(47, 75, 63));
            else
                TransparentBlt(DoubleDC, playerPos.x - bulletcameraPos.x- 16 , playerPos.y- bulletcameraPos.y - 32, bx, by, hMemDC2, 0, 0, bx, by, RGB(47, 75, 63));
            
            DeleteDC(hMemDC2);
        }
        if (isFired)
        {
            hMemDC3 = CreateCompatibleDC(DoubleDC);
            hOldBitmap3 = (HBITMAP)SelectObject(hMemDC3, hBMImage);

            bx = bitBM.bmWidth;
            by = bitBM.bmHeight;
            
            Draw(hWnd, hdc, result);

            TransparentBlt(DoubleDC, result.x - bulletcameraPos.x, result.y - bulletcameraPos.y , bx, by, hMemDC3, 0, 0, bx, by, RGB(47, 75, 63));

            DeleteDC(hMemDC3);
        }
        {
            hMemDC4 = CreateCompatibleDC(DoubleDC);
            hOldBitmap4 = (HBITMAP)SelectObject(hMemDC4, hUIImage);

            bx = bitUI.bmWidth;
            by = bitUI.bmHeight;
            TransparentBlt(DoubleDC, 0, rectView.bottom-159, bx, by, hMemDC4, 0, 0, bx, by, RGB(47, 75, 63));
            
            DeleteDC(hMemDC4);
        }
        Player(hMemDC1);
        DeleteDC(hMemDC1);
    }
    
    TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, DoubleDC, 0, 0, rectView.right, rectView.bottom, RGB(47, 75, 63));

    SelectObject(DoubleDC, hOldDoubleBitmap);
    DeleteDC(DoubleDC);
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

double cMainGame::AngleInRadians(double angle)
{
    revec = (angle * 3.141592) / 180.0;
    return revec;
}

Vector2 cMainGame::BM(HWND hWnd, HDC hdc, Vector2 _BMPos, double t, double _powerGauge)
{
    bulletPosx = (_powerGauge / 10) * t * _BMPos.x;
    bulletPosy = (-1) * ((_powerGauge / 10) * t * _BMPos.y - (0.5 * g * t * t));

    return Vector2(bulletPosx + playerPos.x, bulletPosy + playerPos.y-16);
}

void cMainGame::Draw(HWND hWnd,HDC hdc, Vector2 _playerPos) // 그리기
{
    COLORREF pixelColor = GetPixel(hMemDC1, _playerPos.x, _playerPos.y);
    COLORREF flyColor = RGB(47, 75, 63);

    if (_playerPos.y > 0)
    {
        if (pixelColor != flyColor)
        {
            Boom(hMemDC1, _playerPos);
            isFired = false;
            t = 0;
        }
    }
    
}

void cMainGame::Damage(Vector2 _playerPos)
{
    double direction = sqrt(pow(playerPos.x - _playerPos.x, 2) + pow(playerPos.y - _playerPos.y, 2));

    double angleRad = atan((_playerPos.x - playerPos.x) / direction);
    double minDirection = 16 / cos(angleRad);

    if (20 + minDirection > direction)
    {
        printf("20");
        //자신 플레이어 한테 데미지 
        //추가로 넓이를 구해서 데미지 차별을 주면 좋을 텐데
    }
    else
    {
        printf("NoDamage");
    }
    //적 위치를 추가해서 데미지를 주는 것 추가
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
