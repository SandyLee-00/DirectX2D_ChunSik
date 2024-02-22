#include "Pawn.h"
#include "ClientDefines.h"
#include "ClientHeaders.h"

Pawn::Pawn(ManagerSet* _managers)
	: Object("Pawn", _managers, OBJECT_TYPE::PLAYER, { 0, 0 })
{
}

Pawn::~Pawn()
{
}

void Pawn::Start()
{
// 	pawnState = PAWN_STATE::IDLE;
// 	nextDirection = PAWN_DIRECTION::LEFT;
	MOVEDELAYTIME = 1.0f;
	moveElapsedTime = 0.0f;
}

void Pawn::Update(float _deltaTime)
{
	UpdateState(_deltaTime);
	UpdateAnimation(_deltaTime);
}

void Pawn::FinalUpdate(float _deltaTime)
{
	ComponentUpdate(_deltaTime);
}

void Pawn::Render(GraphicsEngine* _graphicsEngine)
{
	
}

void Pawn::DebugRender(GraphicsEngine* _graphicsEngine)
{
	ComponentRender(_graphicsEngine);
}

void Pawn::UpdateState(float _deltaTime)
{
// 	SPAWNED,
// 		MOVE,
// 		IDLE,
// 		ATTACK,
// 		DEAD_NOSCORE,
// 		HOLD,
// 		DEAD_SCORE,
// 	// 상태에 따라 Update 나눠놓기
// 	switch (pawnState)
// 	{
// 	case PAWN_STATE::SPAWNED:
// 		UpdateSPAWNED(_deltaTime);
// 		break;
// 	case PAWN_STATE::MOVE:
// 		UpdateMOVE(_deltaTime);
// 		break;
// 	case PAWN_STATE::IDLE:
// 		UpdateIDLE(_deltaTime);
// 		break;
// 	case PAWN_STATE::ATTACK:
// 		UpdateATTACK(_deltaTime);
// 		break;
// 	case PAWN_STATE::DEAD_NOSCORE:
// 		UpdateDEAD_NOSCORE(_deltaTime);
// 		break;
// 	
}

void Pawn::UpdateAnimation(float _deltaTime)
{

}
