#include "CWeapon.h"

CWeapon::CWeapon():CSprite(NULL)
{
    //ctor
}

CWeapon::CWeapon(const char *szName):CSprite(szName){
    m_iDir=0;
    m_iHp=2;
    m_fSpeedX=0.f;
    m_fSpeedY=0.f;
}

CWeapon::~CWeapon()
{
    //dtor
}


bool CWeapon::IsDead(){
    if(m_iHp==0){
        return true;
    }
    return false;
}

