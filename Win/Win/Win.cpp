// Win.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win.h"
#include "cMainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      300, 300, 661, 543, nullptr, nullptr, hInstance, nullptr);
   //645, 484
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

#define TIMER_1 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static cMainGame* game = new cMainGame();
    static Vector2 mousePos = game->GetmousePos();
    //선언을 전역 변수로 선언을 해서 값을 계속 가지고 있음
    static RECT rectView;
    Vector2& playerPos = game->GetplayerPos();
    Vector2& BMPos = game->GetBMPos();
    double& vec = game->GetAngle();
    //주소로 보내지 않으면 값을 변경하지 못함

    bool& isFired = game->GetFire();
    double& t = game->GetTime();
    //시간을 점차 줄여야 함
    static DWORD startTime = 0;
    static DWORD endTime = 0;
    static int count = 0;
    static double powerGauge = game->GetpowerGauge();

    //캐릭터는 하나 생성하는 클래스 구현S
    switch (message)
    {
    case WM_CREATE:
    {
        GetClientRect(hWnd,&rectView);
        game->SetrectView(rectView);
        SetTimer(hWnd, TIMER_1, 30, NULL);
        game->CreateBitmap();
        //비트맵 처음 생성
    }
    break;
    case WM_TIMER:
    {
        if (wParam == TIMER_1)
        {
            playerPos.y += 5;//중력
            game->SetplayerPos(playerPos);
            InvalidateRect(hWnd, NULL, FALSE);
        }
    }
        break;

    case WM_KEYDOWN:

        if (wParam == 'A' || wParam == 'a')
        {
            playerPos.x -= 5;
            game->SetplayerPos(playerPos);

            InvalidateRect(hWnd, NULL, FALSE);
        }
        if (wParam == 'D' || wParam == 'd')
        {
            playerPos.x += 5;
            game->SetplayerPos(playerPos);
            InvalidateRect(hWnd, NULL, FALSE);
        }
        if (wParam == 'W' || wParam == 'w')
        {
            if (vec == 55)  return vec;
            else    vec += 1;
            game->SetAngle(vec);
            InvalidateRect(hWnd, NULL, FALSE);
        }
        if (wParam == 'S' || wParam == 's')
        {
            if (vec == 10)  return vec;
            else    vec -= 1;
            game->SetAngle(vec);
            InvalidateRect(hWnd, NULL, FALSE);
        }
        if (wParam == VK_SPACE)
        {

            if (count == 0)
            {
                startTime = GetTickCount();
                count++;
                //스페이스바를 사용했을 때 시간 측정
            }
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;

    case WM_KEYUP:
        if (wParam == VK_SPACE)
        {
            if (!isFired)
            {
                endTime = GetTickCount();
                //끝나는 시간 측정
                DWORD elapsedTime = endTime - startTime;
                //시간 누르는 시간 체크
                powerGauge += elapsedTime;
                if (powerGauge > 1500)    powerGauge = 1500;
                game->SetpowerGauge(powerGauge);
                game->SetBMPos(vec);
                isFired = true;
                game->SetFire(isFired);
                count = 0;
                powerGauge = 0;
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_LBUTTONDOWN:
    {
        mousePos.x = LOWORD(lParam);
        mousePos.y = HIWORD(lParam); //위치를 내가 옮겨서 빼줘야함
        game->SetmousePos(mousePos);
        InvalidateRect(hWnd, NULL, FALSE);
    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            
            game->DrawBitmapDoubleBuffering(hWnd, hdc);
            //비트맵 그려주기
            
            if (isFired)    t += 0.1;
            // 데미지가 있을 때에만 맵을 다시 그려야 함

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        game->DeleteBitmap();
        //생성된 비트맵 삭제
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}