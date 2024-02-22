///ZICO�� �ڵ� SAVAGE
///��ü �� �̰˻簡 �ʿ����� �𸣰ڴ�. �׳� �ϸ� �ȵǳ�? ���߿� ���ƺ����ҵ�
///namespace �ڵ������� ���
#pragma once
#include <exception>
#include <winnt.h>
#include <stdio.h>
#include <wrl.h>
namespace DX
{
	// Helper class for COM exceptions
	class com_exception : public std::exception
	{
	public:
		com_exception(HRESULT hr) : result(hr) {}

		const char* what() const noexcept override
		{
			static char s_str[64] = {};
			sprintf_s(s_str, "Failure with HRESULT of %08X",
				static_cast<unsigned int>(result));
			return s_str;
		}

	private:
		HRESULT result;
	};

	// Helper utility converts D3D API failures into exceptions.
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw com_exception(hr);
		}
	}
}