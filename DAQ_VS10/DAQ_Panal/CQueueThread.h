#pragma  once

#include <queue>

template<class T>
class QueueThread
{

public:
	QueueThread();
	~QueueThread();

	bool isEmpty();
	void Push(const T&obj);
	void Pop();
	int Size();

	T& Front();
	T& Back();
	void Clear();

private:
	std::queue<T>Queue;
	int  size;
	HANDLE mutexHandle;
};

template <class T> QueueThread<T>::QueueThread()
{
	mutexHandle = CreateMutex(NULL, FALSE, NULL);
	size = 0;
}

template <class T> QueueThread<T>::~QueueThread()
{
	CloseHandle(mutexHandle);
}
template <class T> bool QueueThread<T>::isEmpty()
{
	if(0 == size)
	{
		return true;
	}
	return false;
}

template<class T> void QueueThread<T>::Push(const T&obj)
{
	WaitForSingleObject(mutexHandle, INFINITE);
	Queue.push(obj);
	size = Queue.size();
	ReleaseMutex(mutexHandle);
}
template<class T> void QueueThread<T>::Pop()
{
	WaitForSingleObject(mutexHandle, INFINITE);
	Queue.pop();
	size = Queue.size();
	ReleaseMutex(mutexHandle);
}
template<class T> int QueueThread<T>::Size()
{
	return size;
}
template <class T> T& QueueThread<T>::Front()
{
	WaitForSingleObject(mutexHandle, INFINITE);
	T& obj = Queue.front();
	ReleaseMutex(mutexHandle);
	return obj;
}

template <class T> T& QueueThread<T>::Back()
{
	WaitForSingleObject(mutexHandle, INFINITE);
	T& obj = Queue.back();
	ReleaseMutex(mutexHandle);
	return obj;
}

template <class T> void QueueThread<T>::Clear()
{
	WaitForSingleObject(mutexHandle, INFINITE);
	while(!Queue.empty())
	{
		Queue.pop();
	}
	size = 0;
	ReleaseMutex(mutexHandle);
}