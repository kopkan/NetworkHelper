#pragma once


template <typename T>
class Buffer
{
public:
	Buffer(size_t size = 0)
	{
		if (size != 0)
		{
			_size = size;
			_buffer = new T[_size];
		}
	}

	Buffer(char* data, size_t size)
	{
		if (size != 0)
		{
			_size = size;
			_buffer = new T[_size];
			memcpy(_buffer, data, _size);
		}
	}

	Buffer(std::string strig)
	{
		if (strig.size() != 0)
		{
			_size = strig.size();
			_buffer = new T[_size];
			memcpy(_buffer, strig.c_str(), _size);
		}
	}

	Buffer(const Buffer& buffer)
	{
		if (buffer.getSize() > 0)
		{
			_size = buffer.getSize();
			_buffer = new T[_size];
			memcpy(_buffer, buffer.getBuff(), _size);
		}
	}

	~Buffer()
	{
		remove();
	}


	void remove()
	{
		if (_buffer)
		{
			delete _buffer;
			_buffer = NULL;
			_size = 0;
		}
	}

	void resize(size_t size)
	{
		if (size != _size)
		{
			remove();
			_size = size;
			_buffer = new T[_size];
		}
	}

	T* getBuff() const
	{
		return _buffer;
	}

	size_t getSize() const
	{
		return _size;
	}

	T& operator[](int n)
	{
		return _buffer[n];
	}

private:
	T* _buffer = NULL;
	size_t _size = 0;
};