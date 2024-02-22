#include "GameProcess.h"
#include "ClientHeaders.h"

#include "TitleScene.h"
#include "TutorialScene.h"
#include "OpeningScene.h"
#include "MainGameScene.h"
#include "RankingScene.h"
#include "CreditScene.h"
#include "RankingRenewalScene.h"

#include "SoundManager.h"

GameProcess::GameProcess()
	: hwnd(nullptr)
	, isDebug(false)
{
	this->graphicsEngine = new GraphicsEngine();
	this->manager = new ManagerSet();
}

GameProcess::~GameProcess()
{
	delete this->manager;
	delete this->graphicsEngine;
	SoundManager::DestroyInstance();
}

void GameProcess::Initialize(HWND _hwnd)
{
	this->hwnd = _hwnd;
	this->graphicsEngine->Initialize(hwnd);
	manager->InitializeAllManager(this->hwnd, this->graphicsEngine);

	//이미지 로드
	ResourceManager* rm = manager->GetResourceManager();
	PathManager* pm = manager->GetPathManager();
	rm->LoadImage("player", pm->GetResourcePath(L"character\\Sup_idle.png")); //0
	rm->LoadImage("monster1IdleL", pm->GetResourcePath(L"mon\\mon_1-idleL.png"));//1
	rm->LoadImage("monster2IdleL", pm->GetResourcePath(L"mon\\mon_2-idleL.png"));//2
	rm->LoadImage("guardian", pm->GetResourcePath(L"gdn\\gdn.png"));//3
	rm->LoadImage("dealer", pm->GetResourcePath(L"character\\Deal_idle.png"));//4
	rm->LoadImage("Mainbg", pm->GetResourcePath(L"bg\\bg.png"));//5
	rm->LoadImage("maintree", pm->GetResourcePath(L"bg\\bg_tree.png"));//6

	rm->LoadImage("playeridleL", pm->GetResourcePath(L"character\\Sup\\Sup_idle_ani_left.png"));//7
	rm->LoadImage("playeridleR", pm->GetResourcePath(L"character\\Sup\\Sup_idle_ani_right.png"));//8
	rm->LoadImage("playerMoveL", pm->GetResourcePath(L"character\\Sup\\Sup_move_ani_left.png"));//9
	rm->LoadImage("playerMoveR", pm->GetResourcePath(L"character\\Sup\\Sup_move_ani_right.png"));//10
	rm->LoadImage("playerHitL", pm->GetResourcePath(L"character\\Sup\\Sup_hit_ani_left.png"));//11
	rm->LoadImage("playerHitR", pm->GetResourcePath(L"character\\Sup\\Sup_hit_ani_right.png"));//12
	rm->LoadImage("playersldL", pm->GetResourcePath(L"character\\Sup\\Sup_sld_ani_left.png"));//13
	rm->LoadImage("playersldR", pm->GetResourcePath(L"character\\Sup\\Sup_sld_ani_right.png"));//14

	rm->LoadImage("dealerIdle", pm->GetResourcePath(L"character\\Deal\\Deal_idle_ani.png"));//15
	rm->LoadImage("dealerHit", pm->GetResourcePath(L"character\\Deal\\Deal_hit_ani.png"));//16
	rm->LoadImage("dealerSkill", pm->GetResourcePath(L"character\\Deal\\Deal_skill_ani.png"));//17

	rm->LoadImage("mon1MoveL", pm->GetResourcePath(L"mon\\move\\mon_1-leftt.png"));//18
	rm->LoadImage("mon1MoveR", pm->GetResourcePath(L"mon\\move\\mon_1-right.png"));//19
	rm->LoadImage("mon2MoveL", pm->GetResourcePath(L"mon\\move\\mon_2-left.png"));//20
	rm->LoadImage("mon2MoveR", pm->GetResourcePath(L"mon\\move\\mon_2-right.png"));//21
	rm->LoadImage("mon2HoldR", pm->GetResourcePath(L"mon\\move\\Mon_hold_img_right.png"));//22
	rm->LoadImage("monDeath", pm->GetResourcePath(L"mon\\death\\Mon_1_death_ani-Sheet.png"));//23

	rm->LoadImage("frozeCount", pm->GetResourcePath(L"ui\\ingame\\UI_froz_count.png"));//24
	rm->LoadImage("rank", pm->GetResourcePath(L"ui\\rank\\RANK.png"));//25
	rm->LoadImage("ShieldEftLeft", pm->GetResourcePath(L"eft\\Sup_sld_eft_ani_left-Sheet.png"));//26
	rm->LoadImage("ShieldEftRight", pm->GetResourcePath(L"eft\\Sup_sld_eft_ani_right-Sheet.png"));//27

	rm->LoadImage("nullptr", pm->GetResourcePath(L"Example\\emptyImage.png"));//28

	rm->LoadImage("monster1IdleR", pm->GetResourcePath(L"mon\\mon_1-idleR.png"));//29
	rm->LoadImage("monster2IdleR", pm->GetResourcePath(L"mon\\mon_2-idleR.png"));//30
	rm->LoadImage("mon2HoldL", pm->GetResourcePath(L"mon\\move\\Mon_hold_img_left.png"));//31
	rm->LoadImage("mon1HoldL", pm->GetResourcePath(L"mon\\move\\Mon_hold_img2_left.png"));//32
	rm->LoadImage("mon1HoldR", pm->GetResourcePath(L"mon\\move\\Mon_hold_img2_right.png"));//33

	rm->LoadImage("supMoveEftL", pm->GetResourcePath(L"eft\\Sup_move_left_eft-Sheet.png"));//34
	rm->LoadImage("supMoveEftR", pm->GetResourcePath(L"eft\\Sup_move_right_eft-Sheet.png"));//35
	rm->LoadImage("dealSkillEft", pm->GetResourcePath(L"eft\\Deal_skill_eft_ani-Sheet.png"));//36

	rm->LoadImage("HPBar", pm->GetResourcePath(L"ui\\ingame\\HP bar\\UI_Player_HP_bar_1.png"));//37
	rm->LoadImage("HPBar1", pm->GetResourcePath(L"ui\\ingame\\HP bar\\UI_Player_HP_bar_2.png"));//38
	rm->LoadImage("HPBa2", pm->GetResourcePath(L"ui\\ingame\\HP bar\\UI_Player_HP_bar_3.png"));//39
	rm->LoadImage("HPBar3", pm->GetResourcePath(L"ui\\ingame\\HP bar\\UI_Player_HP_bar_4.png"));//40
	rm->LoadImage("HPBar4", pm->GetResourcePath(L"ui\\ingame\\HP bar\\UI_Player_HP_bar_5.png"));//41
	rm->LoadImage("HPBar5", pm->GetResourcePath(L"ui\\ingame\\HP bar\\UI_Player_HP_bar_6.png"));//42

	rm->LoadImage("skillbar", pm->GetResourcePath(L"ui\\ingame\\skill bar\\UI_Player_skill_bar1.png"));//43
	rm->LoadImage("skillbar1", pm->GetResourcePath(L"ui\\ingame\\skill bar\\UI_Player_skill_bar2.png"));//44
	rm->LoadImage("skillbar2", pm->GetResourcePath(L"ui\\ingame\\skill bar\\UI_Player_skill_bar3.png"));//45
	rm->LoadImage("skillbar3", pm->GetResourcePath(L"ui\\ingame\\skill bar\\UI_Player_skill_bar4.png"));//46
	rm->LoadImage("skillbar4", pm->GetResourcePath(L"ui\\ingame\\skill bar\\UI_Player_skill_bar5.png"));//47
	rm->LoadImage("skillbar5", pm->GetResourcePath(L"ui\\ingame\\skill bar\\UI_Player_skill_bar6.png"));//48

	rm->LoadImage("shieldEft", pm->GetResourcePath(L"eft\\Sup_sld_ani-Sheet.png"));//49
	rm->LoadImage("dealDeath", pm->GetResourcePath(L"character\\Deal\\Deal_death_ani.png"));//50
	rm->LoadImage("fullShieldEft", pm->GetResourcePath(L"eft\\Sup_sld_ani2-Sheet.png"));//51

	rm->LoadImage("gdnMoveL", pm->GetResourcePath(L"gdn\\Gdn_move_left_ani-Sheet.png"));//52
	rm->LoadImage("gdnMoveR", pm->GetResourcePath(L"gdn\\Gdn_move_right_ani-Sheet.png"));//53
	rm->LoadImage("gdnShieldEft", pm->GetResourcePath(L"eft\\gdn_sld_ani-Sheet.png"));//54
	rm->LoadImage("gdnFullShieldEFt", pm->GetResourcePath(L"eft\\gdn_sld_ani2-Sheet.png"));//55

	rm->LoadImage("cutScene", pm->GetResourcePath(L"ui\\cutscene\\Deal_skill_cutscene_img.png"));//56

	rm->LoadImage("gdnDeathL", pm->GetResourcePath(L"gdn\\gdn_death_left-Sheet.png"));//57
	rm->LoadImage("gdnDeathR", pm->GetResourcePath(L"gdn\\gdn_death_right-Sheet.png"));//58
	rm->LoadImage("gdnGetHitL", pm->GetResourcePath(L"gdn\\gdn_hit_left-sheet.png"));//59
	rm->LoadImage("gdnGetHitR", pm->GetResourcePath(L"gdn\\gdn_hit_right-Sheet.png"));//60

	rm->LoadImage("supDeathL", pm->GetResourcePath(L"character\\Sup\\Sup_death_ani_left.png"));//61
	rm->LoadImage("supDeathR", pm->GetResourcePath(L"character\\Sup\\Sup_death_ani_right.png"));//62
	rm->LoadImage("supDeadL", pm->GetResourcePath(L"character\\Sup\\death_ani_left.png"));//63
	rm->LoadImage("supDeadR", pm->GetResourcePath(L"character\\Sup\\death_ani_right.png"));//64
	rm->LoadImage("dealDead", pm->GetResourcePath(L"character\\Deal\\death_ani.png"));//65

	rm->LoadImage("frozBox", pm->GetResourcePath(L"ui\\ingame\\UI_FrozBox_img.png"));//66
	rm->LoadImage("scoreBox", pm->GetResourcePath(L"ui\\ingame\\UI_ScoreBox_img.png"));//67
	rm->LoadImage("timeBox", pm->GetResourcePath(L"ui\\ingame\\UI_Time_img.png"));//68

	rm->LoadImage("dealFace", pm->GetResourcePath(L"ui\\ingame\\interface\\Deal_face.png"));//69
	rm->LoadImage("gdnFace", pm->GetResourcePath(L"ui\\ingame\\interface\\gdn_face.png"));//70
	rm->LoadImage("supFace", pm->GetResourcePath(L"ui\\ingame\\interface\\Sup_face.png"));//71
	rm->LoadImage("frozEft", pm->GetResourcePath(L"eft\\Sup_atk_eft-Sheet.png"));//72

	rm->LoadImage("opening1", pm->GetResourcePath(L"ui\\cutscene\\Opening_img_1.png"));//73
	rm->LoadImage("opening2", pm->GetResourcePath(L"ui\\cutscene\\Opening_img_2.png"));//74
	rm->LoadImage("opening3", pm->GetResourcePath(L"ui\\cutscene\\Opening_img_3.png"));//75

	rm->LoadImage("Effect", pm->GetResourcePath(L"white.png"));//76

	rm->LoadImage("gdnAtkL", pm->GetResourcePath(L"gdn\\gdn_atk_left-ani-Sheet.png"));//77
	rm->LoadImage("gdnAtkR", pm->GetResourcePath(L"gdn\\gdn_atk_right-ani-Sheet.png"));//78
	rm->LoadImage("gdnAtkEft", pm->GetResourcePath(L"eft\\Gdn_atk_eft-Sheet.png"));//79

	rm->LoadImage("closebutton", pm->GetResourcePath(L"ui\\title_btn\\UI_Close_btn.png"));//80
	rm->LoadImage("interfaceOverHP", pm->GetResourcePath(L"ui\\ingame\\interface\\interface.png"));//81

	rm->LoadImage("dealerEffect1", pm->GetResourcePath(L"eft\\Deal_skill_eft_ani_1.png"));//82
	rm->LoadImage("dealerEffect2", pm->GetResourcePath(L"eft\\Deal_skill_eft_ani_2.png"));//83
	rm->LoadImage("dealerEffect3", pm->GetResourcePath(L"eft\\Deal_skill_eft_ani_3.png"));//84
	rm->LoadImage("dealerEffect4", pm->GetResourcePath(L"eft\\Deal_skill_eft_ani_4.png"));//85
	rm->LoadImage("dealerEffect5", pm->GetResourcePath(L"eft\\Deal_skill_eft_ani_5.png"));//86

	rm->LoadImage("tutorial1", pm->GetResourcePath(L"ui\\cutscene\\Tutorial_img_1.png"));//87
	rm->LoadImage("tutorial2", pm->GetResourcePath(L"ui\\cutscene\\Tutorial_img_2.png"));//88
	rm->LoadImage("tutorial3", pm->GetResourcePath(L"ui\\cutscene\\Tutorial_img_3.png"));//89
	rm->LoadImage("tutorial4", pm->GetResourcePath(L"ui\\cutscene\\Tutorial_img_4.png"));//90
	rm->LoadImage("tutorial5", pm->GetResourcePath(L"ui\\cutscene\\Tutorial_img_5.png"));//91
	rm->LoadImage("tutorial6", pm->GetResourcePath(L"ui\\cutscene\\Tutorial_img_6.png"));//92
	rm->LoadImage("tutorial7", pm->GetResourcePath(L"ui\\cutscene\\Tutorial_img_7.png"));//93

	rm->LoadImage("titleImage", pm->GetResourcePath(L"ui\\title_btn\\Title_img.png"));//94

	rm->LoadImage("creditbtn", pm->GetResourcePath(L"ui\\title_btn\\UI_Credit_btn.png"));//95
	rm->LoadImage("rankingbtn", pm->GetResourcePath(L"ui\\title_btn\\UI_Rank_btn.png"));//96
	rm->LoadImage("startbtn", pm->GetResourcePath(L"ui\\title_btn\\UI_Start_btn.png"));//97

	rm->LoadImage("skipbtn", pm->GetResourcePath(L"ui\\cutscene\\UI_skip_btn.png"));//98
	rm->LoadImage("gototitlebtn", pm->GetResourcePath(L"ui\\rank\\UI_Title_btn.png"));//99

	rm->LoadImage("credit", pm->GetResourcePath(L"ui\\credit\\credit.jpg"));//100

	//사운드 초기화
	SoundManager::GetInstance()->SoundInit(this->manager->GetPathManager());

	// 사용하는 전체 씬 SceneManager에 추가해놓기
	TitleScene* titleScene = new TitleScene(this->manager);
	manager->GetSceneManager()->AddScene("TitleScene", titleScene);
	manager->GetSceneManager()->SetCurrentScene(titleScene);

	OpeningScene* openingScene = new OpeningScene(this->manager);
	manager->GetSceneManager()->AddScene("OpeningScene", openingScene);

	TutorialScene* tutorialScene = new TutorialScene(this->manager);
	manager->GetSceneManager()->AddScene("TutorialScene", tutorialScene);

	MainGameScene* mainGameScene = new MainGameScene(this->manager);
	manager->GetSceneManager()->AddScene("MainGameScene", mainGameScene);

	RankingScene* rankingScene = new RankingScene(this->manager);
	manager->GetSceneManager()->AddScene("RankingScene", rankingScene);

	CreditScene* creditScene = new CreditScene(this->manager);
	manager->GetSceneManager()->AddScene("CreditScene", creditScene);

	RankingRenewalScene* renewalScene = new RankingRenewalScene(this->manager);
	manager->GetSceneManager()->AddScene("RenewalScene", renewalScene);

	rankingScene->SetMainGameScene(mainGameScene);
	mainGameScene->SetRankingScene(rankingScene);

	// graphicsEngine->SetIsEffOn();
	// graphicsEngine->SetEffect(1.f, 56, 0, 300.f);
}

void GameProcess::Process()
{
	Update();
	FinalUpdate();
	Render();
}

void GameProcess::Update()
{
	manager->Update();
	SoundManager::GetInstance()->Update();
	if (this->manager->GetKeyManager()->GetKeyState(KEY::F_1) == KEY_STATE::DOWN)
	{
		this->isDebug = !this->isDebug;
	}
}

void GameProcess::Render()
{
	graphicsEngine->BDraw();
	graphicsEngine->ColorSet(D2D1::ColorF::Black);
	manager->Render(this->graphicsEngine);
	//graphicsEngine->SetEffect(0.8f, 56);

	if (this->isDebug)
	{
		manager->DebugRender(this->graphicsEngine);
	}
	graphicsEngine->EDraw();
}

void GameProcess::FinalUpdate()
{
	manager->FinalUpdate();
}
