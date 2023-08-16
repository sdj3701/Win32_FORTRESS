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
    hDoubleBufferImage;
    rectView;

}

cMainGame::~cMainGame()
{
    
}

void cMainGame::Boom(HDC hdc, Vector2 _mousePos)
{
    hBrush = CreateSolidBrush(RGB(47, 75, 63));
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    hPen = CreatePen(PS_SOLID, 1, RGB(47, 75, 63));
    oldPen = (HPEN)SelectObject(hdc, hPen);

    Ellipse(hdc, (_mousePos.x + 10) - 20, (_mousePos.y +10)- 20, (_mousePos.x + 10) + 20, (_mousePos.y + 10) + 20);
    
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
}

void cMainGame::DeleteBitmap()
{
    DeleteObject(hbackImage);
    DeleteObject(hTransparentImage);
    DeleteObject(hcharImage);
    DeleteObject(hBMImage);
}

void cMainGame::Player(HDC hdc)
{
    COLORREF pixelColor = GetPixel(hdc, playerPos.x, playerPos.y + 34);
    COLORREF flyColor = RGB(47, 75, 63);
    if (pixelColor != flyColor)
    {
        playerPos.y -= 5;
        SetplayerPos(playerPos);
    }
}

HDC hMemDC, hMemDC1, hMemDC2, hMemDC3;
HBITMAP hOldBitmap, hOldBitmap1, hOldBitmap2, hOldBitmap3;
void cMainGame::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc, Vector2 _mousePos)
{
    HDC DoubleDC;
    HBITMAP hOldDoubleBitmap;

    int bx, by;
    
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

            BitBlt(DoubleDC, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);
            SelectObject(hMemDC, hOldBitmap);
            DeleteDC(hMemDC);
        }
        {

            hMemDC1 = CreateCompatibleDC(DoubleDC);
            hOldBitmap1 = (HBITMAP)SelectObject(hMemDC1, hTransparentImage);

            bx = bitTransparent.bmWidth;
            by = bitTransparent.bmHeight;

            TransparentBlt(DoubleDC, 0, 100, bx, by, hMemDC1, 0, 0, bx, by, RGB(47, 75, 63));
        }
        {
            hMemDC2 = CreateCompatibleDC(DoubleDC);
            hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hcharImage);

            bx = bitChar.bmWidth;
            by = bitChar.bmHeight;

            TransparentBlt(DoubleDC, playerPos.x, playerPos.y + 100, bx, by, hMemDC2, 0, 0, bx, by, RGB(47, 75, 63));
            DeleteDC(hMemDC2);
        }
        if (isFired)
        {
            hMemDC3 = CreateCompatibleDC(DoubleDC);
            hOldBitmap3 = (HBITMAP)SelectObject(hMemDC3, hBMImage);

            BM(hWnd, hMemDC3, BMPos, t);
            Vector2 result = BM(hWnd, hMemDC3, BMPos, t);
            bx = bitBM.bmWidth;
            by = bitBM.bmHeight;

            TransparentBlt(DoubleDC, result.x, result.y+100, bx, by, hMemDC3, 0, 0, bx, by, RGB(47, 75, 63));
            DeleteDC(hMemDC3);
        }

        Player(hMemDC1);
        DeleteDC(hMemDC1);
    }
    
    TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, DoubleDC, 0, 0, rectView.right, rectView.bottom, RGB(47, 75, 63));

    SelectObject(DoubleDC, hOldDoubleBitmap);
    DeleteDC(DoubleDC);

}

Vector2 cMainGame::BM(HWND hWnd,HDC hdc,Vector2 v,double t)
{
    double x = 50 * t * v.x;
    double y = 50 * t * v.y - (0.5 * g * t * t);
    
    Draw(hWnd, hdc, Vector2(x + playerPos.x, -(y)+(playerPos.y)));

    return Vector2(x + playerPos.x, -(y)+(playerPos.y));
}

Vector2 cMainGame::SetBMPos(Vector2 _BMPos, double _vec)
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
    vec = (angle * 3.141592) / 180.0;
    return vec;
}

void cMainGame::Draw(HWND hWnd,HDC hdc, Vector2 _mousePos)
{
    //_mousePos.y += 100;
    hBrush = CreateSolidBrush(RGB(47, 75, 63));
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    hPen = CreatePen(PS_SOLID, 1, RGB(47, 75, 63));
    oldPen = (HPEN)SelectObject(hdc, hPen);
    
    Ellipse(hdc, _mousePos.x - 10, _mousePos.y - 10, _mousePos.x + 10, _mousePos.y + 10);

    COLORREF pixelColor = GetPixel(hMemDC1, _mousePos.x, _mousePos.y + 10);
    COLORREF flyColor = RGB(47, 75, 63);
    if (pixelColor != flyColor)
    {
        //_mousePos.y -= 100;
        Boom(hMemDC1, _mousePos);
        isFired = false;
        t = 0;
    }
    SelectObject(hdc, oldPen);
    DeleteObject(hPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);
    
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