#pragma once

#include <Windows.h>
#pragma comment(lib,"msimg32.lib")

class cMainGame
{
private:
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	HBITMAP hbackImage;
	BITMAP bitBack;
	//backgrund
	HBITMAP hTransparentImage;
	BITMAP bitTransparent;
	//map
	HBITMAP hcharImage;
	BITMAP bitChar;
	//char
	HBITMAP hBMImage;
	BITMAP bitBM;
	//BM
	HBITMAP hUIImage;
	BITMAP bitUI;
	//UI

	HBITMAP hDoubleBufferImage;
	HDC m_MemDC;
	
	RECT rectView;

	Vector2 playerPos = { 832,244 };
	Vector2 BMPos = { 0,0 };
	Vector2 mousePos = { 0,0 };
	Vector2 cameraPos = { 0,0 };

	double testPos=0;
	double powerGauge = 0;
	double vec = {35.0};
	double revec;
	double t = 0;
	const double g = 9.81;
	bool isFired = false;


public:
	cMainGame();
	~cMainGame();
public:
	void Boom(HDC hdc, Vector2 _playerPos);
	void Player(HDC hdc);

	void CreateBitmap();
	void DeleteBitmap();
	void DrawBitmapDoubleBuffering(HWND hWNd, HDC hdc);

	void SetplayerPos(Vector2 _playerPos);
	Vector2& GetplayerPos();

	void SetrectView(RECT _rectView);
	RECT GetrectView();

	void SetAngle(double _vec);
	double& GetAngle();

	void SetTime(double _t);
	double& GetTime();

	void SetFire(bool _isFired);
	bool& GetFire();

	void SetpowerGauge(double _powerGauge);
	double& GetpowerGauge();

	void SetmousePos(Vector2 _mousePos);
	Vector2& GetmousePos();

	void SetcameraPos(Vector2 _cameraPos);
	Vector2& GetcameraPos();

	void SettestPos(double _testPos);
	double& GettestPos();



	Vector2 BM(HWND hWnd, HDC hdc, Vector2 v, double t, double _powerGauge);//계산된 탄 포물선 방적식을 계산해서 발사하는 함수
	Vector2 SetBMPos(double _vec); //(BMPos를 각도에 따라 계산 하기 위한 함수)
	Vector2& GetBMPos(); // 저장한 함수 사용하기
	double AngleInRadians(double angle);//각도에 따른 라디안 계산
	void Draw(HWND hWnd,HDC hdc, Vector2 _playerPos);
};

