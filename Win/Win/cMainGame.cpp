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
    COLORREF pixelColor = GetPixel(hdc, playerPos.x, playerPos.y);
    COLORREF flyColor = RGB(47, 75, 63);
    if (pixelColor != flyColor)
    {
        /*post -= 5;
        SetposT(post);*/
        playerPos.y -= 5;
        SetplayerPos(playerPos);
        if (playerPos.y - rectView.bottom / 2 < 0)
        {
            post -= 5;
            SetposT(post);
        }
    }
}

HDC hMemDC, hMemDC1, hMemDC2, hMemDC3, hMemDC4;
HBITMAP hOldBitmap, hOldBitmap1, hOldBitmap2, hOldBitmap3, hOldBitmap4;
void cMainGame::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    HDC DoubleDC;
    HBITMAP hOldDoubleBitmap;

    int bx, by;
    static int posr = 0, posb = 0,posl =0,post=0;
    
    int wx=rectView.right/2, wy= rectView.bottom/2;

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

            cameraPos.x = playerPos.x - wx;
            cameraPos.y = playerPos.y - wy;
            //캐릭터 위치로 중심으로 카메라가 움직였으면

            bx = rectView.right;
            by = rectView.bottom ;
            //화면 크기 
            
            //이미지 크기를 전체 크기를 불러오는 것이 아니라 화면 만금의 크기를 가져와야함
            //661, 543

            TransparentBlt(DoubleDC, 0, 0, bx, by, hMemDC1, cameraPos.x , cameraPos.y, bx, by, RGB(47, 75, 63));

            if (playerPos.x + wx > 1536)//이미지 크기x
            {
                TransparentBlt(DoubleDC, 0, 0, bx, by, hMemDC1, cameraPos.x - GetposR(), cameraPos.y, bx, by, RGB(47, 75, 63));
            }
            if (playerPos.y + wy > 671)//이미지 크기y
            {
                //오류 잘나오다가 마지막에 계속 올라감
                TransparentBlt(DoubleDC, 0, 0, bx, by, hMemDC1, cameraPos.x, cameraPos.y - GetposB() , bx, by, RGB(47, 75, 63));
            }
            if (playerPos.x - wx < 0)
            {
                TransparentBlt(DoubleDC, 0, 0, bx, by, hMemDC1, cameraPos.x + GetposL(), cameraPos.y, bx, by, RGB(47, 75, 63));
            }
            if (playerPos.y - wy < 0)
            {
                TransparentBlt(DoubleDC, 0, 0, bx, by, hMemDC1, cameraPos.x , cameraPos.y + GetposT(), bx, by, RGB(47, 75, 63));
            }
            //xy위치를 땡겨 와야 한다.
            //mapPos 처음 실행 될때는 0,0이다
            //playerPos 150,50
        }
        {
            hMemDC2 = CreateCompatibleDC(DoubleDC);
            hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hcharImage);
            //32/32
            bx = bitChar.bmWidth;
            by = bitChar.bmHeight;
            //캐릭터
            TransparentBlt(DoubleDC, playerPos.x- cameraPos.x -16, playerPos.y - cameraPos.y-32, bx, by, hMemDC2, 0 , 0 , bx, by, RGB(47, 75, 63));
            DeleteDC(hMemDC2);
        }
        if (isFired)
        {

            hMemDC3 = CreateCompatibleDC(DoubleDC);
            hOldBitmap3 = (HBITMAP)SelectObject(hMemDC3, hBMImage);

            Vector2 result = BM(hWnd, hMemDC3, BMPos, t, GetpowerGauge());
            bx = bitBM.bmWidth;
            by = bitBM.bmHeight;

            TransparentBlt(DoubleDC, result.x, result.y, bx, by, hMemDC3, 0, 0, bx, by, RGB(47, 75, 63));
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

Vector2 cMainGame::BM(HWND hWnd,HDC hdc,Vector2 v,double t,double _powerGauge)
{
    double x =  (_powerGauge/10) * t * v.x;
    double y =  (_powerGauge/10) * t * v.y - (0.5 * g * t * t);
    
    Draw(hWnd, hdc, Vector2(x + playerPos.x, -(y)+(playerPos.y)));
     
    return Vector2(x + playerPos.x, -(y)+(playerPos.y));
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

void cMainGame::Draw(HWND hWnd,HDC hdc, Vector2 _playerPos) // 그리기
{
    hBrush = CreateSolidBrush(RGB(47, 75, 63));
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    hPen = CreatePen(PS_SOLID, 1, RGB(47, 75, 63));
    oldPen = (HPEN)SelectObject(hdc, hPen);
    
    Ellipse(hdc, _playerPos.x - 10, _playerPos.y - 10, _playerPos.x + 10, _playerPos.y + 10);

    COLORREF pixelColor = GetPixel(hMemDC1, _playerPos.x, _playerPos.y);
    COLORREF flyColor = RGB(47, 75, 63);
    if (pixelColor != flyColor)
    {
        Boom(hMemDC1, _playerPos);
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

void cMainGame::SetpowerGauge(double _powerGauge)
{
    powerGauge = _powerGauge;
}

double& cMainGame::GetpowerGauge()
{

    return powerGauge;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetmapPos(Vector2 _mapPos)
{
    mapPos.x = _mapPos.x;
    mapPos.y = _mapPos.y;
}

Vector2& cMainGame::GetmapPos()
{
    return mapPos;
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

void cMainGame::SettestPos(double _testPos)
{
    testPos = _testPos;
}

double& cMainGame::GettestPos()
{
    return testPos;
}

void cMainGame::SetposR(double _posr)
{
    posr = _posr;
}

double& cMainGame::GetposR()
{
    return posr;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetposL(double _posl)
{
    posl = _posl;
}

double& cMainGame::GetposL()
{
    return posl;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetposT(double _post)
{
    post = _post;
}

double& cMainGame::GetposT()
{
    return post;
    // TODO: 여기에 return 문을 삽입합니다.
}

void cMainGame::SetposB(double _posb)
{
    posb = _posb;
}

double& cMainGame::GetposB()
{
    return posb;
    // TODO: 여기에 return 문을 삽입합니다.
}
