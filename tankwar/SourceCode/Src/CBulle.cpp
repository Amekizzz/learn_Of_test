#include "CBulle.h"
#include<stdio.h>
#include "LessonX.h"
#include "CommonClass.h"
CBullet::CBullet():CWeapon(NULL)
{
    //ctor

}

CBullet::CBullet(const char* szName):CWeapon(szName){

}

CBullet::~CBullet()
{

}


void CBullet::OnMove(int iDir){
    SetDir(iDir);
    switch (GetDir()){
        case 0:
            SetSpeedX(0);
            SetSpeedY(-10);
            break;
        case 1:
            SetSpeedX(10);
            SetSpeedY(0);
            break;
        case 2:
            SetSpeedX(0);
            SetSpeedY(10);
            break;
        case 3:
            SetSpeedX(-10);
            SetSpeedY(0);
            break;
    }
    SetSpriteRotation(90*GetDir());
    SetSpriteLinearVelocity(GetSpeedX(),GetSpeedY());
}



void CBullet::OnSpriteColSprite(CWeapon* pSprite){
	if(pSprite == NULL){
		return;
	}
	SetHp(0);
	if(GetOwner() == 1 && strstr(pSprite->GetName(),"aim_nor") != NULL){  //�ҷ�̹���ӵ����Ӫ������ײ
		return;
	}
	if(GetOwner() == 0 && strstr(pSprite->GetName(),"enemy") != NULL){ //�з�̹���ӵ����еط�̹��
		return;
	}
    pSprite->SetHp(pSprite->GetHp()-1);
}

