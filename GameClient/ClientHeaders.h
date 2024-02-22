#pragma once
// _CrtDumpMemoryLeaks();
// _CrtSetBreakAlloc(번호넣기);

// Graphics Engine
#include "GraphicsEngine.h"

// Engine
#include "Scene.h"

// Manager
#include "ManagerSet.h"
#include "SceneManager.h"
#include "SoundManager.h"

// Component
#include "Transform.h"
#include "MouseEvent.h"
#include "Collider.h"
#include "Animation.h"

// Object
#include "Object.h"
#include "Button.h"
#include "Bar.h"
#include "Animator.h"

// ETC
#include "ObjectPool.h"
#include "random.h"
#include "Grid.h"


#include <windows.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <assert.h>
#include <algorithm>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

