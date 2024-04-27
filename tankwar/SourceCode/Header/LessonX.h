/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include "CTankPlayer.h"
#include "CBulle.h"
#include"CTankEnemy.h"
/////////////////////////////////////////////////////////////////////////////////
//
// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
	int				m_iGameState;				// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������
	int             m_iBulletNum;
    int             m_iTankEnemyNumber;
	int             m_iScore;//����
    int             m_iEnemy;//��������
    int             m_iHight;//������߷�
    float           m_fDeltaTime;//��ʾ��Ϸʱ��
    float           m_fTankEnemyTime;

    int             m_iBulletState;


	CSprite         *m_pSplash;
	CSprite         *m_pStart;
    CWeapon         *m_pAim_nor;
	CTankPlayer     *m_pTankPlayer;
	CTextSprite	    *m_pScore; //��ʾ�������ı�����
    CTextSprite 	*m_pHight; //��ʾ��߷ֵ��ı�����
	CTextSprite 	*m_pEnemy;//��ʾ�����������ı�����


	//CTankEnemy      *m_pTankEnemy;

public:
	CGameMain();            //���캯��
	~CGameMain();           //��������

	// Get����
	int				GetGameState()											{ return m_iGameState; }

	// Set����
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// ��Ϸ��ѭ����
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();


	//   ����Ϊϵͳ�����ĸ�д
	void        OnMouseMove( const float fMouseX, const float fMouseY );
	void        OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );
	void        OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY );
	void        OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );
	void        OnKeyUp( const int iKey );
	void        OnSpriteColSprite( const char *szSrcName, const char *szTarName );
	void        OnSpriteColWorldLimit( const char *szName, const int iColSide );

	//����Ϊ��Ӻ���
	void        AddBullet(int iDir,float fPosX,float fPosY,int iOwner);
	void        LoadMap();
	CWeapon     *FindWeaponByName(const char*szName);
	void        DeleteWeaponByName(const char*szName);
	void        AddTankEnemy(float fDeltaTime);
	void	    DeleteAllSprite();
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
