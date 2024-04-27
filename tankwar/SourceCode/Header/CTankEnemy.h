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
//set方法

//get方法


    //其他函数
    void Init();
    void OnMove();
    void OnMove(float fDeltaTime);
    void OnFire(float fDeltaTime);
    void OnSpriteColSprite(CWeapon* pSprite);

    //构造函数
    CTankEnemy();
    CTankEnemy(const char*  szName);

    //析构函数
    virtual ~CTankEnemy();
};

#endif // CTANKENEMY_H
