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
	HBITMAP hDoubleBufferImage;
	HDC m_MemDC;
	RECT rectView;

	Vector2 playerPos = { 150,50 };
	Vector2 BMPos = { 0,0 };

	double vec = {35.0};
	
public:
	cMainGame();
	~cMainGame();
public:
	void Boom(HDC hdc, POINT _mousePos);
	void Player(HDC hdc);

	void CreateBitmap();
	void DeleteBitmap();
	void DrawBitmapDoubleBuffering(HWND hWNd, HDC hdc, POINT _mousePos);

	void SetplayerPos(Vector2 _playerPos);
	Vector2& GetplayerPos();

	void SetrectView(RECT _rectView);
	RECT GetrectView();

	void SetAngle(double _vec);
	double& GetAngle();

	Vector2 BM(Vector2 v, double t);//계산된 탄 포물선 방적식을 계산해서 발사하는 함수
	Vector2 SetBMPos(Vector2 _BMPos,double _vec); //(BMPos를 각도에 따라 계산 하기 위한 함수)
	Vector2& GetBMPos(); // 저장한 함수 사용하기
	double AngleInRadians(double angle);//각도에 따른 라디안 계산
	Vector2 launchPos(Vector2 _playerPos, Vector2 _BMPos); // 실제 계산한 각도 위치 벡터

};

