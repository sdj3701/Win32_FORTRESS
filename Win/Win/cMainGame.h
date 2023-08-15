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
	
public:
	cMainGame();
	~cMainGame();
public:
	void Boom(HDC hdc, POINT _mousePos);
	void CreateBitmap();
	void DeleteBitmap();
	void Player(HDC hdc);
	void SetplayerPos(Vector2 _playerPos);
	Vector2& GetplayerPos();
	void SetrectView(RECT _rectView);
	RECT GetrectView();
	void DrawBitmapDoubleBuffering(HWND hWNd, HDC hdc, POINT _mousePos);

};

