#pragma once

enum class SUPPORTER_STATE
{
	IDLE,
	MOVE,
	HIT,
	HOLD,
	SHIELD,
	DEAD,
	END,
};

enum class DEALER_STATE
{
	IDLE,
	ATTACK,
	HIT,
	PROTECTED,
	DEAD,
	END,
};

enum class MONSTER_STATE
{
	IDLE,
	MOVE,
	HOLD,
	HOLD_DEAD_READY,
	DEAD_READY,
	DEAD,
	END
};

enum class GUARDIAN_STATE
{
	IDLE,
	MOVE,
	ATTACK,
	HIT,
	DEAD,
	END
};

enum class DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE,
	END
};

enum class MONSTER_TYPE
{
	TWO,
	THREE,
	END
};

const float GRID_SIZE = 96;
const float CENTER_POS_X = 902;
const float CENTER_POS_Y = 441;

// -----------------------------------
// 밸런스 시트 const 값들

const int Z_DEALER_MAX = 5;

const int HP_DEALER_MAX = 5;
const int HP_SUPPORTER_MAX = 3;
const int HP_GUARDIAN_MAX = 10;

// X축 왼쪽 이동 제한
const float LIMIT_X_MIN = 96.f;
// X축 오른쪽 이동 제한
const float LIMIT_X_MAX = 1920.f - (96.f * 2);
// Y축 위쪽 이동 제한
const float LIMIT_Y_MIN = 120.f;
// Y축 아래쪽 이동 제한
const float LIMIT_Y_MAX = 1080.f - (96.f * 2);

// 가면 안되는 곳 내부 여백
const float LIMIT_INBOX_GAP = 2.f;
// 가면 안되는 곳 체크할 때 더 가보는 여백
const float LIMIT_GOINSIDE_GAP = 5.f;

// X축 왼쪽 딜러 이동 제한
const float LIMIT_X_DEALER_MIN = 96.f * 8 + LIMIT_INBOX_GAP;
// X축 오른쪽 딜러 이동 제한
const float LIMIT_X_DEALER_MAX = 96.f * 11 - LIMIT_INBOX_GAP;
// Y축 위쪽 딜러 이동 제한
const float LIMIT_Y_DEALER_MIN = 120.f + 96.f * 2 + LIMIT_INBOX_GAP;
// Y축 아래쪽 딜러 이동 제한
const float LIMIT_Y_DEALER_MAX = 120.f + 96.f * 4 -  LIMIT_INBOX_GAP;


// 밸런스 시트 const 값들
	// -----------------------------------