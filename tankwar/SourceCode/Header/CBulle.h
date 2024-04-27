#ifndef CBULLE_H
#define CBULLE_H
#include "CommonClass.h"
#include "LessonX.h"
#include "CWeapon.h"

class CBullet :public CWeapon
{
public:
    CBullet();
    CBullet(const char*  szName);
    virtual ~CBullet();

    void SetOwner(int Owner){
        m_iOwner=Owner;
    }

    int GetOwner(){
        return m_iOwner;
    }

    void OnMove(int iDir);
    void OnSpriteColSprite(CWeapon* pSprite);
    protected:

    private:
        int m_iDir;
        int m_iHp;
        int m_iOwner;
        float m_fSpeedX;
        float m_fSpeedY;
};

#endif // CBULLE_H
