#ifndef CTANKPLEAR_H_INCLUDED
#define CTANKPLEAR_H_INCLUDED

#include<windows.h>
#include"CommonClass.h"
#include "CWeapon.h"

// #include"CBulle.h"

class CTankPlayer : public CWeapon
{

private:

public:

    //���캯��
    CTankPlayer(void);
    CTankPlayer(const char*  szName);

    //��������

    //��������
    void OnMove(int iKey,bool bPress);
    void Init();
    void OnFire();
    void OnSpriteColSprite(CWeapon *sSprit);

};



#endif // CTANKPLEAR_H_INCLUDED
