#ifndef CWEAPON_H
#define CWEAPON_H
#include"CommonClass.h"


class CWeapon : public CSprite
{
private:
    int m_iDir;
    int m_iHp;
    float m_fSpeedX;
    float m_fSpeedY;
public:
    //
    CWeapon();
    CWeapon(const char *szName);

    //
    virtual ~CWeapon();

    //set����
    void SetHp(int hp){
        m_iHp=hp;
    }
    void SetDir(int dir){
        m_iDir=dir;
    }
    void SetSpeedX(float speedX){
        m_fSpeedX=speedX;
    }
    void SetSpeedY(float speedY){
        m_fSpeedY=speedY;
    }
//get����
    int GetHp(){
        return m_iHp;
    }
    int GetDir(){
        return m_iDir;
    }
    float GetSpeedX(){
        return m_fSpeedX;
    }
    float GetSpeedY(){
        return m_fSpeedY;
    }

    //
    bool IsDead();//�жϾ����Ƿ�����
    virtual void Init(){};//��ʼ������
    virtual void OnMove(float fDeltaTime){};//�з�̹���ƶ�����
    virtual void OnMove(){};
    virtual void OnFire(float deltaTime){};//�����ӵ�����
    virtual void OnSpriteColSprite(CWeapon *pSprite){};//�����뾫����ײʱ������

    boolIsDead();

};

#endif // CWEAPON_H
