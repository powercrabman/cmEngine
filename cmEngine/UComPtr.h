#pragma once

//==========================================
// DirectX ��ü�� �����ϴ� Unique_ptr Wrapper
//==========================================

template <typename Ty>
class UComPtr
{
public:
	static_assert(std::is_base_of<IUnknown, Ty>::value, "Ty must derive from IUnknown.");

	UComPtr(std::nullptr_t)
		:ptr(nullptr)
	{
	}

	explicit UComPtr(Ty* p)
		: ptr(p)
	{
	}

	~UComPtr()
	{
		if (ptr)
		{
			ptr->Release();
		}
	}

	UComPtr(const UComPtr&) = delete;
	UComPtr& operator=(const UComPtr&) = delete;

	UComPtr(UComPtr&& other) noexcept
		: ptr(other.ptr)
	{
		other.ptr = nullptr;
	}

	bool operator==(std::nullptr_t) const
	{
		return ptr == nullptr;
	}

	bool operator!=(std::nullptr_t) const
	{
		return ptr != nullptr;
	}

	UComPtr& operator=(UComPtr&& other) noexcept
	{
		if (this != &other)
		{
			// ���� �ڿ� ����
			if (ptr)
			{
				ptr->Release();
			}

			// ������ ����
			ptr = other.ptr;
			other.ptr = nullptr;
		}
		return *this;
	}

	Ty* operator->() const
	{
		return ptr;
	}

	Ty& operator*() const
	{
		return *ptr;
	}

	Ty* Get() const
	{
		return ptr;
	}

	Ty** GetAddressOf()
	{
		return &ptr;
	}

	bool operator!() const
	{
		return this != nullptr;
	}

	void Reset(Ty* p = nullptr)
	{
		if (ptr != p)
		{
			ptr->Release();
		}
		ptr = p;
	}

	template<typename U>
	HRESULT As(UComPtr<U>* p) const
	{
		p.Reset();
		return ptr->QueryInterface(__uuidof(U), reinterpret_cast<void**>(p->GetAddressOf()));
	}

private:
	Ty* ptr = nullptr;
};
