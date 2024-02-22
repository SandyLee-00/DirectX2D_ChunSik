#pragma once
#define SAFE_DELETE(p)	{ if(p != nullptr){delete p; p = nullptr;}}
#define SAFE_DELETE_ARRAY(p) if(p != nullptr){{delete[] p; p = nullptr}}

template <typename T>
class Singleton
{
private:
	static T* instance;

protected:
	Singleton() {};
	~Singleton() {};

	virtual void Init() = 0;

public:
	static T* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new T();
			instance->Init();
		}
		return instance;
	}

	static void DestroyInstance()
	{
		// GameManager ��ü�� ������
		if (instance != nullptr)
		{
			// GameManager ��ü �޸� ��ȯ
			SAFE_DELETE(instance);
		}
	}
};

template<typename T> T* Singleton<T>::instance = nullptr;