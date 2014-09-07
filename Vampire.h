// Vampire.h: interface for the CVampire class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VAMPIRE_H__BC4C3FF1_9255_4420_818B_3A7C2A106C03__INCLUDED_)
#define AFX_VAMPIRE_H__BC4C3FF1_9255_4420_818B_3A7C2A106C03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace VampireIvo {


class CVampire;
class CAnimation;
class CSprite;


class CVampires
{

public:

	enum // move methods
	{
		MV_HORIZONTAL = 0,
		MV_VERTICAL = 1,
		MV_SINUS_HORIZ = 2,
		MV_SINUS_VERT = 3
	};



	CVampires();
	virtual ~CVampires();

	void Destroy();
	bool CreateVampire( CSprite *pSpriteFly, CSprite *pSpriteDie );
	int CheckHit( int mx, int my, int mw, int mh );
	void Update( SDL_Surface *pScreen, float *mpf );
	
	int getSize() { return m_vampires.size(); };

private:
	vector<CVampire*> m_vampires;



};


class CVampire  
{
public:
	CVampire();
	virtual ~CVampire();

	float m_x, m_y;
	float m_speed;
	float m_angle;
	float m_speed_angle;

	int   m_life;
	int   m_move_method;
	
	CAnimation *m_panimFly;
	CAnimation *m_panimDie;

	bool m_bKilled;

};



} //end namespace

#endif // !defined(AFX_VAMPIRE_H__BC4C3FF1_9255_4420_818B_3A7C2A106C03__INCLUDED_)