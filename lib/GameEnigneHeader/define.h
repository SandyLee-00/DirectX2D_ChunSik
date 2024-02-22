#pragma once

/// enum class, ��� ���� ��Ƴ��� ���

/// <summary>
/// ������Ʈ Ÿ�Կ� ���� ������ ����
/// ���� ������ �� ���� ���߿� ������ �Ȱſ� ������
/// ���Ŀ� Ÿ���� �ʿ��ϸ� ����ȯ ���� ����!!!
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
/// ������Ʈ ����
/// �߰� ������ �����Ӱ� �ϵ�
/// LIVE, DEAD_READY, DEAD 3���� �ݵ�� �־�� ��!!!
/// </summary>
enum class OBJECT_STATE
{
	LIVE,
	DEAD_READY,
	DEAD,

	END,
};

/// <summary>
/// ������Ʈ ������Ʈ ����
/// ��ī���� �ڵ� ������
/// ���� ���� �� �� ����ȯ �θ� ��
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

