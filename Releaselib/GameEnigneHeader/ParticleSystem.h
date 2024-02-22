#pragma once
#include "headers.h"
#include "Component.h"
#include "random.h"
#include "Transform.h"
#include "Object.h"
#include "ObjectPool.h"
#include "Particle.h"
#include "random.h"

class Object;
class Particle;

/// <summary>
/// ��ƼŬ�ý��� Ŭ����
/// ���� �ۼ��� : 2023/08/11
/// ���� �ۼ��� : 2023/08/14
/// �ۼ��� : ����ȯ
/// 
/// ��ƼŬ�� ����� �����ϴ� Ŭ����
/// <\summry>

template<class P>
class ParticleSystem
	: public Component
{
private:
	std::list<P*> particleList;

	std::string iamgeName;
	int maxCount;
	int minCount;
	ObjectPool<P, 100>* objectPool;

public:
	ParticleSystem(Object* _Object);
	virtual ~ParticleSystem();

	void Update(float _dt = 0) override;
	void LateUpdate() override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	
	void GenerateParticle();

	int GetMaxCount() const { return maxCount; }
	void SetMaxCount(int val) { maxCount = val; }
	int GetMinCount() const { return minCount; }
	void SetMinCount(int val) { minCount = val; }
};


template<typename P>
ParticleSystem<P>::ParticleSystem(Object* _Object)
	: Component(CALL_ORDER::PARTICLE, "ParticleSystem", _Object)
	, maxCount(10)
	, minCount(5)
	, objectPool{ new ObjectPool<P, 100>(_Object->GetManagers()) }
{

}

template<typename P>
ParticleSystem<P>::~ParticleSystem()
{
	delete this->objectPool;
	for (auto particle : this->particleList)
	{
		delete particle;
	}
}

/// <summary>
/// ��� ��ƼŬ ������Ʈ
/// </summary>
/// <param name="_dt">dt</param>
template<typename P>
void ParticleSystem<P>::Update(float _dt /*= 0*/)
{
	auto particle = this->particleList.begin();

	while (particle != this->particleList.end())
	{
		// �̹� ���� ��ƼŬ �̶�� ����
		if ((*particle)->GetState() == OBJECT_STATE::DEAD)
		{
			this->objectPool->ReleaseObject(*particle);
			particle = this->particleList.erase(particle);
		}
		else
		{
			(*particle)->Update(_dt);
			particle++;
		}
	}
}
template<typename P>
void ParticleSystem<P>::LateUpdate()
{
}

/// <summary>
/// ��ƼŬ ����
/// </summary>
/// <param name="_graphicsEngine">�׷��� ����</param>
template<typename P>
void ParticleSystem<P>::Render(GraphicsEngine* _graphicsEngine)
{
	for (auto particle : this->particleList)
	{
		particle->Render(_graphicsEngine);
	}
}
template<typename P>
void ParticleSystem<P>::DebugRender(GraphicsEngine* _graphicsEngine)
{
	for (auto particle : this->particleList)
	{
		particle->DebugRender(_graphicsEngine);
	}
}

template<typename P>
void ParticleSystem<P>::GenerateParticle()
{
	int count = random::GetRandom<int>(this->GetMinCount(), this->GetMaxCount());

	for (int i = 0; i < count; i++)
	{
		P* particle = this->objectPool->GetObject();

		this->particleList.push_back(particle);
		particle->Start();
		particle->GetComponent<Transform>()->SetPosition(this->GetOwner()->GetComponent<Transform>()->GetPosition());
	}
}
