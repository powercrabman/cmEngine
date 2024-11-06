#pragma once

class cmStaticTextBufferBase
{
public:
	cmStaticTextBufferBase() = default;
	virtual ~cmStaticTextBufferBase() = default;

	virtual void Clear() abstract;
	virtual void Append(const char* fmt, ...) abstract;
	virtual void Append(const char* fmt, const va_list& args) abstract;
	virtual void Print(const char* fmt, ...) abstract;
	virtual void Print(const char* fmt, const va_list& args) abstract;
	virtual const char* c_str() const abstract;
	virtual char* data() abstract;
	virtual size_t Length() const abstract;
	virtual size_t capacity() const abstract;
};

template <size_t SIZE>
class cmStaticTextBuffer : public cmStaticTextBufferBase
{
public:
	cmStaticTextBuffer() = default;
	virtual ~cmStaticTextBuffer() = default;

	char& operator[](size_t idx)
	{
		assert(idx < SIZE); 
		return mBuffer[idx];
	}

	void Clear() override
	{
		mBuffer[0] = '\0';
	}

	void Append(const char* fmt, ...) override
	{
		va_list args;
		va_start(args, fmt);
		Append(fmt, args);
		va_end(args);
	}

	void Append(const char* fmt, const va_list& args) override
	{
		size_t len = Length();
		if (len >= SIZE) return;

		std::vsnprintf(mBuffer + len, SIZE - len, fmt, args);
	}

	void Print(const char* fmt, ...) override
	{
		va_list args;
		va_start(args, fmt);
		Print(fmt, args);
		va_end(args);
	}

	void Print(const char* fmt, const va_list& args) override
	{
		std::vsnprintf(mBuffer, SIZE, fmt, args);
	}

	const char* c_str() const override { return mBuffer; }
	char* data() override { return mBuffer; }

	size_t Length() const override { return std::strlen(mBuffer); }
	size_t capacity() const override { return SIZE; }

private:
	char mBuffer[SIZE] = {};
};