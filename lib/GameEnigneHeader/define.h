#pragma once

/// enum class, 상수 등을 모아놓은 헤더

/// <summary>
/// 오브젝트 타입에 따른 렌더링 순서
/// 먼저 렌더링 된 것이 나중에 렌더링 된거에 가려짐
/// 추후에 타입이 필요하면 김형환 한테 문의!!!
/// </summary>
enum class OBJECT_TYPE
{
	BACK_GROUND,
	MONSTER,
	DEALER,
	GUARDIAN,
	SUPPORTER,
	ATTACHMENT,
	EEFECT,

	CAN_PAUSE,

	UI,
	WHITEEFFECT,
	END,
};

/// <summary>
/// 오브젝트 상태
/// 추가 삭제는 자유롭게 하되
/// LIVE, DEAD_READY, DEAD 3개는 반드시 있어야 됨!!!
/// </summary>
enum class OBJECT_STATE
{
	LIVE,
	DEAD_READY,
	DEAD,

	END,
};

/// <summary>
/// 컴포넌트 업데이트 순서
/// 포카리팀 코드 참고함
/// 순서 변경 할 때 김형환 부를 것
/// </summary>
enum class CALL_ORDER
{
	MONO_BEHAVIOUR,
	RENDERER,
	ANIMATOR,
	PARTICLE,
	RIGID_BODY,
	TRANSFORM,
	COLLIDER,
	UI,
	END,
};


enum class COLLIDER_SHPAE
{
	BOX,
	CIRCLE,
	POLYGON,
	END,
};

