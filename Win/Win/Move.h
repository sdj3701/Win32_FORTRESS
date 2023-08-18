#pragma once
class Move
{
private:
	double posr, posl, post, posb;
public:
	Move();
	Move(double _posr,double _posl, double _post, double _posb);
	~Move();
	void SetposR(double _posr);
	double GetposR();
	void SetposL(double _posl);
	double GetposL();
	void SetposT(double _post);
	double GetposT();
	void SetposB(double _posb);
	double GetposB();
}; 