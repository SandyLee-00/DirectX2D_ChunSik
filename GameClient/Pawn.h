#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

class Pawn
	: public Object
{
protected:
// 	PAWN_STATE pawnState;
// 	PAWN_DIRECTION nextDirection;
	float MOVEDELAYTIME;
	float moveElapsedTime;

public:
	Pawn(ManagerSet* _managers);
	virtual ~Pawn();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;
	virtual void FinalUpdate(float _deltaTime) override;
	virtual void Render(GraphicsEngine* _graphicsEngine) override;
	virtual void DebugRender(GraphicsEngine* _graphicsEngine) override;

	virtual void UpdateState(float _deltaTime);
	virtual void UpdateAnimation(float _deltaTime);

	virtual void UpdateIDLE(float _deltaTime) abstract;
	virtual void UpdateMOVE(float _deltaTime) abstract;
	virtual void UpdateATTACK(float _deltaTime) abstract;
	virtual void UpdateDAMAGED(float _deltaTime) abstract;
	virtual void UpdateDEAD(float _deltaTime) abstract;

// 	void SetGameState(PAWN_STATE _state) { pawnState = _state; };
// 	void SetNextDirection(PAWN_DIRECTION _direction) { nextDirection = _direction; };
// 
// 	PAWN_STATE GetGameState() { return pawnState; };
// 	PAWN_DIRECTION GetNextDirection() { return nextDirection; };

};

