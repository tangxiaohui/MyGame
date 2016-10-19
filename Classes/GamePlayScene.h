#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DebugSimpleServer.h"
#include "TimeLayer.h"
#include "SettingMenuInPlaying.h"
#include "UserProfileUI.h"
#include "ChatLayer.h"
#include "NetworkManger.h"
#include "SiteManager.h"
#include "PorkerManager.h"

class NiuPoker;
class NiuPlayer;
USING_NS_CC;
using namespace ui;

/** 更新状态 */
enum UpdateType{
    /** 准备状态 */
    StartState,
    /** 发牌状态 */
    SendPokerState,
    /** 抢庄状态 */
    HogState,
    /** 选择倍数状态 */
    ChooseMultipleState,
    /** 比大小状态 */
    CompareState
};


class GamePlayScene : public cocos2d::Layer
{
public:
    GamePlayScene(unsigned long long playerID,int roomID);
    ~GamePlayScene();
	static cocos2d::Scene* createScene(unsigned long long playerID,int roomID);
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	static GamePlayScene* create(unsigned long long playerID,int roomID);

	//virtual void onExit();
	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);
	void update(float delta);
	void func(Node* pSender, void* pData);
private:
	bool initBackground();
	bool initButtons();
	bool initPlayerProfile();	//初始化玩家信息
	bool initPlayerLeftProfile();	//初始化左侧玩家信息
	bool initPlayerRightProfile();	//初始化右侧玩家信息
	bool initPlayerTopLeftProfile();//初始化顶部左一侧玩家信息
	bool initPlayerTopRightProfile();//初始化顶部左二侧玩家信息
	/** 初始化玩家信息 */
	bool initPlayer();
	/** 生成一个牌 */
	NiuPoker* selectPoker(int huaSe, int num);
	/** 创建一副扑克牌 */
	bool createPokers();
	/** 洗牌 */
	bool xiPai();
	/** 发牌 */
	void SendPk();
	/** 发牌移动动画 */
	void MovePk(NiuPlayer* play, NiuPoker* pk);

	
    
    /** 初始化抢庄和不抢按钮 */
    void showHogButton();
    /** 显示倍数按钮 */
    void showChooseMultipleButton();
    /** 显示结果 */
    void showCompare();
    /** 重新开局 */
    void startNewPlay();
    /** 不抢和抢庄超时事件 */
    void notHogBtnAction();
    /** 选择倍数超时事件 */
    void notChooseMulAction(float dt);
private:
	//其余4个玩家的玩家位置和头像位置
	struct PlayerAndProfilePos 
	{
		Point playerPos;
		Point profilePos;
		int profileType;		//0为水平，1为垂直
	};

	TimeLayer* m_timeLayer;
	ChatLayer* m_chatLayer;

	IUserProfileUIInGame* m_pUser;	//当前用户
	IUserProfileUIInGame* m_pUserLeft;	//玩家左
	IUserProfileUIInGame* m_pUserRight;	//玩家右
	IUserProfileUIInGame* m_pUserTopLeft;	//玩家顶部左一
	IUserProfileUIInGame* m_pUserTopRight;	//玩家顶部左二
	/** 设置 */
	SettingMenuInPlaying *m_btnSetting;
	/** 聊天 */
	Button* m_chatBtn;
    /** 准备按钮 */
    Button* m_startGameBtn;
    /** 不抢按钮 */
    Button* m_notHogBtn;
    /** 抢庄按钮 */
    Button* m_HogBtn;
    /** 一倍按钮 */
    Button* m_OneBtn;
    /** 二倍按钮 */
    Button* m_TwoBtn;
    /** 三倍按钮 */
    Button* m_ThreeBtn;
    /** 四倍按钮 */
    Button* m_FourBtn;
    /** 五倍按钮 */
    Button* m_FiveBtn;
	bool m_bReady;
	/** 所有的牌 */
	__Array* m_arrPokers;
	/** 玩家 */
	CC_SYNTHESIZE(NiuPlayer*, m_player, Player);
	/** 玩家右 */
	NiuPlayer* m_playerRight;
	/** 玩家上二 */
	NiuPlayer* m_playerTopRight;
	/** 玩家上一 */
	NiuPlayer* m_playerTopLeft;
	/** 玩家左 */
	NiuPlayer* m_playerLeft;
	/** 玩家坐标 */
	cocos2d::Point playerDiZhuLablePt;
	/** 玩家右一坐标 */
	cocos2d::Point playerOneLablePt;
	/** 玩家上二坐标 */
	cocos2d::Point playerTwoLablePt;
	/** 玩家左三坐标 */
	cocos2d::Point playerThreeLablePt;
	/**  是否发完牌 */
	bool m_isSend;
	/** 已发出第几张牌 */
	int m_iSendPk;
	/** 当前状态 0：发牌状态  */
	UpdateType m_iState;
    /** 是否创建抢庄按钮 */
    bool m_creatHogBtn;
    /** 是否创建倍数按钮 */
    bool m_creatMulBtn;
    int m_playNum;
    LabelTTF *m_pNoticeLabel;
	Label *m_pRoomNumberLabel;
	LabelTTF *m_pModelLabel;
    Button *m_recordBtn;
	void Load_File_JSON(const char* filename);//二进制读取录音文件SiteManager* m_pSiteManager;	unsigned long long m_playerID;
	int m_roomID;
	unsigned long long m_playerID;
	SiteManager* m_pSiteManager;
	PorkerManager* m_pPorkerManager;
	vector<PlayerAndProfilePos> m_playerProfileInfo;
	vector<int> m_playerInRoom;									//房间里的坑位，0表示没人坐，1表示有人坐

	//本地测试用
	vector<unsigned long long> m_testID;
};


#endif // __GAMESCENE_SCENE_H__
