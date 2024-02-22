#pragma once
#include "ClientHeaders.h"
#include "BigInt.h"

class TextScore
	: public Object
{
private:
	bool isWorking;
	UINT64 score;

public:
	TextScore(ManagerSet* _managers);
	~TextScore();

	void Start() override;
	void Update(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;

	void SetScore(UINT64 _score) { score = _score; }
	UINT64 GetScore() { return score; }
};
