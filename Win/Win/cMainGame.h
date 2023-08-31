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
	HBITMAP hBcharImage;
	BITMAP bitBChar;
	//char
	HBITMAP hBMImage;
	BITMAP bitBM;
	HBITMAP hBBMImage;
	BITMAP bitBBM;
	//BM
	HBITMAP hUIImage;
	BITMAP bitUI;
	//UI
	HBITMAP hEnemyImage;
	BITMAP bitEnemy;
	HBITMAP hBEnemyImage;
	BITMAP bitBEnemy;
	//Enemy
	HBITMAP hEnemyBMImage;
	BITMAP bitEnemyBM;
	//EnemyBM

	HBITMAP hDoubleBufferImage;
	HDC m_MemDC;

	RECT rectView;

	Vector2 playerPos = { 132,104 };
	Vector2 EnemyPos = { 732,184 };

	Vector2 BMPos = { 0,0 };
	Vector2 mousePos = { 0,0 };

	Vector2 cameraPos = { 0,0 };
	Vector2 enemycameraPos = { 0,0 };

	Vector2 FEPos = { EnemyPos.x - 16,EnemyPos.y };
	Vector2 FPPos = { playerPos.x + 16, playerPos.y };

	double powerGauge = 0;
	double vec = { 35.0 };
	double Evec = { 35.0 };
	double revec;
	double t = 0;
	double bulletPosx;
	double bulletPosy;

	double bpAngle;
	double beAngle;
	const double g = 9.81;

	bool isFired = false;
	bool check = false;

	bool moveD = false;

	int playerHP = 100;
	int EnemyHP = 100;

	int turn = 0;


public:
	cMainGame();
	~cMainGame();
public:
	void Boom(HDC hdc, Vector2 _playerPos);
	void Player(HDC hdc);

	void CreateBitmap();
	void DeleteBitmap();
	void DrawBitmapDoubleBuffering(HWND hWNd, HDC hdc);

	void SetbpAngle(double _bpAngle);
	double& GetbpAngle();

	void SetbeAngle(double _beAngle);
	double& GetbeAngle();

	void SetplayerPos(Vector2 _playerPos);
	Vector2& GetplayerPos();

	void SetEnemyPos(Vector2 _EnemyPos);
	Vector2& GetEnemyPos();

	void SetrectView(RECT _rectView);
	RECT GetrectView();

	void SetAngle(double _vec);
	double& GetAngle();

	void SetEAngle(double _Evec);
	double& GetEAngle();

	void SetTime(double _t);
	double& GetTime();

	void SetFire(bool _isFired);
	bool& GetFire();

	void SetCheck(bool _check);
	bool& GetCheck();

	void SetmoveD(bool _moveD);
	bool& GetmoveD();

	void SetpowerGauge(double _powerGauge);
	double& GetpowerGauge();

	void SetmousePos(Vector2 _mousePos);
	Vector2& GetmousePos();

	void SetcameraPos(Vector2 _cameraPos);
	Vector2& GetcameraPos();

	void SetFEPos(Vector2 _playerPos);
	Vector2& GetFEPos();

	void SetFPPos(Vector2 _playerPos);
	Vector2& GetFPPos();

	void SetTurn(int _turn);
	int& GetTurn();


	Vector2 BM(HWND hWnd, HDC hdc, Vector2 v, double t, double _powerGauge);//계산된 탄 포물선 방적식을 계산해서 발사하는 함수
	Vector2 SetBMPos(double _vec); //(BMPos를 각도에 따라 계산 하기 위한 함수)
	Vector2& GetBMPos(); // 저장한 함수 사용하기
	double AngleInRadians(double angle);//각도에 따른 라디안 계산
	void Draw(HWND hWnd, HDC hdc, Vector2 _playerPos);
	void Damage(Vector2 _playerPos);
	void CharAngle(Vector2 _playerPos, Vector2 _FPPos);
	void EnemyAngle(Vector2 _EnemyPos, Vector2 _FEPos);
	void RotateImage(HDC hdc, HBITMAP hBitmap, int playerPosx,int plaeyrPosy, int dx, int dy, double angle);

};