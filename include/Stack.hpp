#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <new>
#include <exception>


class OutOfRange : public std::exception {
public:
	const char* what() {
		return "Out of Range";
	}
};

class EmptyStack : public std::exception {
public:
	const char* what() {
		return "Empty stack";
	}
};


class InvalidStack : public std::exception {
public:
	const char* what() {
		return "Invalid stack";
	}
};

class FailedCopyAssigment : public std::exception {
public:
	const char* what() {
		return "Failed Copy Assigment";
	}
};

class FailedMoveAssigment : public std::exception {
public:
	const char* what() {
		return "Failed Move Assigment";
	}
};


template <typename T>
class Stack
{
private: 
	T* data_ = nullptr;
	size_t size_ = 0;
	size_t capacity_ = 0;

	void Resize(size_t newSz);
public:
	Stack();
	Stack(size_t size);
	Stack(const Stack& other);
	Stack(Stack&& other);
	~Stack();

	size_t Size() const { return size_; }
	size_t Capacity() const { return capacity_; }
	T* GetData() const { return data_; }
	bool IsEmpty() const { return size_ == 0; }

	Stack& operator=(const Stack& other);
	Stack& operator=(Stack&& other);

	void Pop();
	void Push(const T& v);
	void Push(T&& v);
	T& Top() const;
};
	
template <typename T>
void Stack<T>::Resize(size_t newSz)
{
	if (newSz > capacity_)
	{
		capacity_ *= 2;
		T* new_data = new T[capacity_];
		for (size_t i = 0; i < size_; i++)
		{
			new_data[i] = std::move(data_[i]);
		}

		delete[] data_;
		data_ = new_data;
	}
	size_ = newSz;
}

template <typename T>
Stack<T>::Stack()
{
	data_ = new T[1];
	capacity_ = 1;
	size_ = 0;
}

template <typename T>
Stack<T>::Stack(size_t size)
{
	size_ = 0;
	capacity_ = size;
	data_ = new T[capacity_];

	if (data_ == nullptr)
	{
		throw InvalidStack();
	}
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other)
{
	if (other.data_ == 0)
	{
		throw InvalidStack();
	}

	data_ = new T[other.capacity_]();
	size_ = other.size_;
	capacity_ = other.capacity_;
	std::copy(other.data_, other.data_ + capacity_, data_);
}

template <typename T>
Stack<T>::Stack(Stack<T>&& other)
{
	if (other.data_ == nullptr)
	{
		throw InvalidStack();
	}

	data_ = other.data_;
	size_ = other.size_;
	capacity_ = other.capacity_;

	other.capacity_ = 0U;
	other.size_ = 0U;
	other.data_ = nullptr;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
	if (data_ == nullptr || other.data_ == nullptr)
	{
		throw InvalidStack();
	}

	if (this == &other)
	{
		return *this;
	}

	delete[] data_;
	data_ = new T[other.capacity_];
	capacity_ = other.capacity_;
	size_ = other.size_;

	std::copy(other.data_, other.data_ + capacity_, data_);
	
	if (data_ == nullptr)
	{
		throw FailedCopyAssigment();
	}
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other)
{
	if (data_ == nullptr || other.data_ == nullptr)
	{
		throw InvalidStack();
	}

	delete[] data_;
	data_ = other.data_;
	size_ = other.size_;
	capacity_ = other.capacity_;

	other.data_ = nullptr;
	other.size_ = 0U;
	other.capacity_ = 0U;

	if (data_ == nullptr || other.data_ != nullptr)
	{
		throw FailedMoveAssigment();
	}

	return *this;
}


template <typename T>
Stack<T>::~Stack()
{
	if (data_ != nullptr)
	{
		delete[] data_;
	}
}

template <typename T>
void Stack<T>::Pop()
{
	if (data_ == nullptr)
	{
		throw InvalidStack();
	}
	if (size_ == 0U)
	{
		throw EmptyStack();
	}

	size_--;
}

template <typename T>
void Stack<T>::Push(const T& v)
{
	if (data_ == nullptr)
	{
		throw InvalidStack();
	}
	Resize(size_ + 1);
	data[size_ - 1] = v;
}

template <typename T>
void Stack<T>::Push(T&& v)
{
	if (data_ == nullptr)
	{
		throw InvalidStack();
	}
	Resize(size_ + 1);
	data_[size_ - 1] = std::move(v);
}

template <typename T>
T& Stack<T>::Top() const
{
	if (data_ == nullptr)
	{
		throw InvalidStack();
	}
	if (size_ == 0)
	{
		throw EmptyStack();
	}

	return data_[size_ - 1];
}


#endif