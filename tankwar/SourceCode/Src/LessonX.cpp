/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include<vector>
#include "CommonClass.h"
#include "LessonX.h"
#include "CTankPlayer.h"
#include "CBulle.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;

//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//

//��ͼ����:
int g_iMap[11][13]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,1,0,1,0,0,0,1,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,1,0,1,0,1,0,1,0,0,0},
    {0,0,0,1,0,0,0,0,0,1,0,0,0},
    {0,0,0,1,0,1,0,1,0,1,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,0,1,0,0,0,0,0,1,0,1,0},
    {0,0,0,0,0,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,1,0,1,0,0,0,0,0}
};

vector<CWeapon*>m_vWeapon;


// ���캯��
CGameMain::CGameMain()
{
	m_iGameState			=	0;
	m_pScore = new CTextSprite("score");
	m_pHight = new CTextSprite("hight");
    m_pEnemy = new CTextSprite("enemyNum");
    m_iScore=0;//����
    m_iEnemy=0;//��������
    m_iHight = 0;
    m_fDeltaTime = 0.f;
    m_iBulletState=0;

}
//==============================================================================
//
// ��������
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬.
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У�����������Ϸ�߼�
	case 2:
		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
            if(!m_pTankPlayer->IsDead() && !m_pAim_nor->IsDead() && m_fDeltaTime<100.f)
			{
				GameRun( fDeltaTime );
			}
			else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
			{
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit(){
    m_iBulletNum    =   0;
	m_iTankEnemyNumber  =  0;
	m_fTankEnemyTime = 4.f;
	m_iScore = 0;
	m_iHight = 0;
	m_iEnemy = 0;
    m_fDeltaTime = 0.f;
    m_iBulletNum=0;
	m_pSplash=new CSprite("splash");
	m_pStart=new CSprite("start");
    //m_pTankEnemy=new CTankEnemy("enemy");
	m_pTankPlayer=new CTankPlayer("player");
	m_pAim_nor=new CWeapon("myaim_nor");
    m_pSplash->SetSpriteVisible(false);
    m_pStart->SetSpriteVisible(false);
    LoadMap();
    m_pTankPlayer=new CTankPlayer("myplayer");
    m_pTankPlayer->CloneSprite("player");
    m_pTankPlayer->Init();
    m_vWeapon.push_back(m_pTankPlayer);
    m_pAim_nor->CloneSprite("aim_nor");
    m_vWeapon.push_back(m_pAim_nor);
    m_pAim_nor->SetSpriteCollisionReceive(true);
    m_pAim_nor->SetSpritePosition(0.f,20.f);
    //m_pTankEnemy->Init();

    FILE * fp =fopen("save.txt","r+");
    if(fp){
        fread(&m_iHight,sizeof(int),1,fp);
        fclose(fp);
    }
	m_pHight = new CTextSprite("hight");
	m_pHight->SetTextValue(m_iHight);

}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime ){
    AddTankEnemy(fDeltaTime);
    m_fDeltaTime += fDeltaTime;
    for(int i=0;i<(int)m_vWeapon.size();i++){
        if(!m_vWeapon[i]->IsDead()){
            m_vWeapon[i]->OnMove(fDeltaTime);
            m_vWeapon[i]->OnFire(fDeltaTime);
        }
        else{
            DeleteWeaponByName(m_vWeapon[i]->GetName());
        }
        m_pScore->SetTextValue(m_iScore);
        m_pHight->SetTextValue(m_iHight);
        m_pEnemy->SetTextValue(m_iEnemy);

    }
}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd(){
    FILE *fp=fopen("save.txt","w+");
    if(m_iScore>m_iHight){
        fwrite(&m_iScore,sizeof(int),1,fp);
    }
    fclose(fp);
    m_pSplash->SetSpriteVisible(true);
    m_pStart->SetSpriteVisible(true);
    SetGameState(0);
    for(auto it:m_vWeapon){
        it->DeleteSprite();
    }
    m_vWeapon.clear();
}


void CGameMain::OnMouseMove(  const float fMouseX, const float fMouseY  ){

}

void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY ){

}


void CGameMain::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY ){

}

void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress ){
    if(iKey==KEY_SPACE){
        if(m_iGameState==0){
            m_iGameState=1;
        }
    }
    if(m_iGameState==2){
        m_pTankPlayer->OnMove(iKey,true);
    }
    if(iKey==KEY_J){                //�жϰ��¼��ǹ�ΪJ��
            m_pTankPlayer->OnFire();
    }
    if(iKey==KEY_K){
        m_pTankPlayer->SetSpeedX(m_pTankPlayer->GetSpeedX()*2);
        m_pTankPlayer->SetSpeedY(m_pTankPlayer->GetSpeedY()*2);
    }
    if(iKey==KEY_L){
         m_iBulletState++;
    }
}

void CGameMain::OnKeyUp( const int iKey ){
    if(m_iGameState==2){
        if(iKey==KEY_W||iKey==KEY_A||iKey==KEY_S||iKey==KEY_D){
            m_pTankPlayer->OnMove(iKey,false);
        }

    }
}

void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName ){
    CWeapon* tarSprite = FindWeaponByName(szTarName);
	if(strstr(szSrcName,"bullet") != NULL){//������ײΪ�ӵ�
		CBullet *tmpBullet = (CBullet*)FindWeaponByName(szSrcName);
		tmpBullet->OnSpriteColSprite(tarSprite);
		if( tmpBullet->GetOwner()==1 && strstr(szTarName,"enemy") != NULL){
		    CWeapon *tmpEnemy;
            tmpEnemy=FindWeaponByName(szTarName);
            if(tmpEnemy->GetHp()==0){
                m_iScore++;
                m_iEnemy--;
            }

		}

	}
	else if(strcmp(szSrcName,"myplayer")==0){ //������ײΪ�ҷ�̹��
		m_pTankPlayer->OnSpriteColSprite(tarSprite);
	}
	else if(strstr(szSrcName,"enemy") != NULL){//������ײΪ�з�̹��
		CTankEnemy* tmpEnemy = (CTankEnemy*)FindWeaponByName(szSrcName);
		tmpEnemy->OnSpriteColSprite(tarSprite);
	}
}

void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide ){
    if(strstr(szName,"player")!=NULL){          //�ж���������߽��̹���Ƿ�Ϊ�ҷ�̹��
        m_pTankPlayer->SetSpriteLinearVelocity(0,0);
    }
//    if(m_pTankEnemy&&strcmp(m_pTankEnemy->GetName(),szName)==0){
//            m_pTankEnemy->OnMove();
//    }
    else if(strstr(szName,"enemy")!=NULL){
        CWeapon *pEnemy=FindWeaponByName(szName);
        pEnemy->SetSpriteLinearVelocity(0.f,0.f);
        pEnemy->OnMove();
    }
    else if(strstr(szName,"bullet")!=NULL){
        CWeapon*pBullet=FindWeaponByName(szName);
        pBullet->SetHp(0);
    }
}



void CGameMain::AddBullet(int iDir,float fPosX,float fPosY,int iOwner){
    char*szName=CSystem::MakeSpriteName("bullet",2+m_iBulletNum);//����̹������
    CBullet *pBullet=new CBullet(szName);
    if( m_iBulletState%2==0){
        pBullet->CloneSprite("bullet1");
    }
    else{
        pBullet->CloneSprite("bullet2");
    }
    pBullet->SetSpriteWorldLimit(WORLD_LIMIT_NULL,-26,-22,26,22);//��������߽�
    pBullet->SetSpritePosition(fPosX,fPosY);
    pBullet->SetSpriteCollisionSend(true);//���ý�����ײ
    pBullet->OnMove(iDir);
    m_iBulletNum++;//�ӵ�������1
    if(iOwner==1){
        pBullet->SetOwner(1);//1��ʾ�ҷ�̹�˷�����ӵ�
    }
    else{
        pBullet->SetOwner(0);//0��ʾ�ط�̹�˷�����ӵ�
    }
    m_vWeapon.push_back(pBullet);
}


void CGameMain::LoadMap(){
    char *szName;
    int i,j;
    float x,y;
    for(i=0;i<11;i++){
        for(j=0;j<13;j++){
            if(g_iMap[i][j]==1){
                szName=CSystem::MakeSpriteName("wall",j+i*13+i);//��������
                CWeapon *pWall=new CWeapon(szName);//�½�����
                pWall->SetHp(2);
                pWall->CloneSprite("wall");//��¡ǽ��
                pWall->SetSpriteCollisionActive(0,1);//����Ϊ������ײ
                pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
                x=float(-24+4*j);y=float(-20+4*i);
                pWall->SetSpritePosition(x,y);
                m_vWeapon.push_back(pWall);
            }
        }
    }
}


CWeapon* CGameMain::FindWeaponByName(const char* szName)//�������ֲ��ҵ�����
{
	for(int i=0; i<(int)m_vWeapon.size(); i++)
	{
			if(strcmp(szName,m_vWeapon[i]->GetName()) == 0)
			{
				return m_vWeapon[i];
			}
	}
	return NULL;
}


void CGameMain::DeleteWeaponByName(const char* szName)//�������ְѾ����������ɾ��
{
	for(vector<CWeapon*>::iterator it=m_vWeapon.begin();it!=m_vWeapon.end();)
	{
		CWeapon* cw =*it;
		if(strcmp(szName,cw->GetName()) == 0)
		{
			m_vWeapon.erase(it);
			cw->DeleteSprite();
			delete cw;
			break;
		}
		else
		{
			it++;
		}
	}
}


void CGameMain::AddTankEnemy(float fDeltaTime){
    m_fTankEnemyTime+=fDeltaTime;
    if(m_fTankEnemyTime>5.f){
        char *szName=CSystem::MakeSpriteName("enemy",m_iTankEnemyNumber);
        CTankEnemy *m_pTankEnemy=new CTankEnemy(szName);
        m_pTankEnemy->CloneSprite("enemy");
        m_pTankEnemy->Init();
        m_iTankEnemyNumber++;
        m_iEnemy++;
        m_vWeapon.push_back(m_pTankEnemy);
        m_fTankEnemyTime=0.f;
    }
}



void	CGameMain::DeleteAllSprite(){
	int n=(int)m_vWeapon.size();
	while(m_vWeapon.size()!=0){
		vector<CWeapon*>::iterator itr=m_vWeapon.begin();
		CWeapon* cw = *itr;
		m_vWeapon.erase(itr);
		cw->DeleteSprite();
		delete cw;
	}
}

