#ifndef CTANKENEMY_H
#define CTANKENEMY_H
#include"CommonClass.h"
#include "CWeapon.h"

class CTankEnemy: public CWeapon
{
private:
    float m_fChangeDirTime;
    float m_fBulletCreateTime;
public:
//set����

//get����


    //��������
    void Init();
    void OnMove();
    void OnMove(float fDeltaTime);
    void OnFire(float fDeltaTime);
    void OnSpriteColSprite(CWeapon* pSprite);

    //���캯��
    CTankEnemy();
    CTankEnemy(const char*  szName);

    //��������
    virtual ~CTankEnemy();
};

#endif // CTANKENEMY_H
