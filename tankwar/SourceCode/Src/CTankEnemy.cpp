#include "CTankEnemy.h"
#include"LessonX.h"
#include<stdio.h>

CTankEnemy::CTankEnemy():CWeapon(NULL)
{
    //ctor
}

CTankEnemy::CTankEnemy(const char*  szName):CWeapon(szName){

    m_fChangeDirTime=0.f;
    m_fBulletCreateTime=0.f;
}

CTankEnemy::~CTankEnemy()
{
    //dtor
}


void CTankEnemy::Init(){
    int iPos=CSystem::RandomRange(0,2);
    float fPosX;
    SetDir(2);
    SetHp(2);
    switch(iPos){
        case 0:
            fPosX=-23.f;
            break;
        case 1:
            fPosX=0.f;
            break;
        case 2:
            fPosX=23.f;
            break;
        default:
            break;
    }
    SetSpritePosition(fPosX,-19.f);
    SetSpriteLinearVelocity(0.f,8.f);
    SetSpriteCollisionActive(1,1);//设置可以接受和发送碰撞
    SetSpriteRotation(float(90*GetDir()));
    SetSpriteWorldLimit(WORLD_LIMIT_NULL,-26,-22,26,22);
}

void CTankEnemy::OnMove(){
    int iDir=0;
    if(GetDir()==0||GetDir()==1||GetDir()==2){
        iDir=GetDir()+1;
    }
    else{                   //如果方向值等于3,设为0
        iDir=0;
    }
    SetDir(iDir);

    switch (GetDir()){
        case 0:
            SetDir(0);
            SetSpeedX(0);
            SetSpeedY(-8);
            break;
        case 1:
            SetDir(1);
            SetSpeedX(8);
            SetSpeedY(0);
            break;
        case 2:
            SetDir(2);
            SetSpeedX(0);
            SetSpeedY(8);
            break;
        case 3:
            SetDir(3);
            SetSpeedX(-8);
            SetSpeedY(0);
            break;
    }
    SetSpriteRotation(float(90*GetDir()));//用方向值乘于90得到精灵旋转度数
    SetSpriteLinearVelocity(GetSpeedX(),GetSpeedY());


}

void CTankEnemy::OnMove(float fDeltaTime){
    m_fChangeDirTime+=fDeltaTime;
    if(m_fChangeDirTime>2.0f){
        OnMove();
        m_fChangeDirTime=0.f;
    }
}

void CTankEnemy::OnFire(float fDeltaTime){
    m_fBulletCreateTime+=fDeltaTime;
    if(m_fBulletCreateTime>5.0f){
        m_fBulletCreateTime=0.0f;
        float x,y;
        x=GetSpritePositionX();
        y=GetSpritePositionY();
        switch(GetDir()){
            case 0:
                y=y-GetSpriteHeight()/2-1;
                break;
            case 1:
                x=x+GetSpriteWidth()/2+1;
                break;
            case 2:
                y=y+GetSpriteHeight()/2+1;
                break;
            case 3:
                x=x-GetSpriteWidth()/2-1;
                break;
        }
            g_GameMain.AddBullet(GetDir(),x,y,0);
        }
}


void CTankEnemy::OnSpriteColSprite(CWeapon* pSprite)
{
	if(pSprite == NULL){
		return;
	}
	SetSpriteLinearVelocity(0.f,0.f);
    m_fChangeDirTime = 1.8;
}

