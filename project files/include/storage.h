#pragma once

#include <cstddef>
#include "error.h"

template<typename T>
class Storage
{
public:
	Storage();
	Storage(size_t); //������ ������ � ��������� ����������� ��������� 

	Storage(const Storage<T>& original);

	~Storage();

	Storage& operator=(const Storage<T>& other);

	T& operator[](size_t index);

	const T& operator[](size_t index) const;

	void add(T value);

	void insert(size_t index, T value);

	void remove(size_t index);

	size_t size() const;

	class Marker
	{
	public:

		bool hasNext() const
		{
			// ���������� ����� ���������
			return m_marker < m_storage->m_data + m_storage->m_size - 1;
		}

		void next()
		{
			if (hasNext())
				m_marker++;
			else valid = false;
		}

		T& getValue()
		{
			// ���������� ����� ���������
			if (m_marker >= m_storage->m_data + m_storage->m_size)
				throw Error();

			return *m_marker;
		}

		void remove()
		{
			// ���������� ����� ���������
			m_storage->remove(m_marker - m_storage->m_data);
			valid = false;
		}

		bool isValid()
		{
			return valid;
		}

		friend class Storage;

	private:
		bool valid;
		T* m_marker;
		Storage<T>* m_storage;
	};


	Marker createMarker();


private:
	T* m_data;
	size_t m_size;

};


template<typename T>
typename Storage<T>::Marker Storage<T>::createMarker()
{
	Storage<T>::Marker m;
	m.m_marker = m_data;
	m.m_storage = this;
	m.valid = true;
	return m;
}

template<typename T>
Storage<T>::Storage()
{
	m_data = nullptr;
	m_size = 0;
}

template<typename T>
Storage<T>::Storage(size_t t)
{
	m_data = new T[t];
	m_size = t;
}

template<typename T>
Storage<T>::Storage(const Storage<T>& original)
{
	m_size = original.size();
	m_data = new T[m_size];
	for (size_t i = 0; i < m_size; ++i)
		m_data[i] = original[i];
}

template<typename T>
Storage<T>::~Storage()
{
	if (m_data != nullptr)
		delete[] m_data;
}

template<typename T>
Storage<T>& Storage<T>::operator=(const Storage<T>& other)
{
	if (this != &other)
	{
		m_size = other.size();
		if (m_data != nullptr)
			delete[] m_data;

		m_data = new T[m_size];

		for (size_t i = 0; i < m_size; ++i)
			m_data[i] = other[i];
	}

	return *this;
}

template<typename T>
T& Storage<T>::operator[](size_t index)
{
	if (index < 0 || index >= m_size)
		throw BadArgument();

	return m_data[index];
}

template<typename T>
const T& Storage<T>::operator[](size_t index) const
{
	if (index < 0 || index >= m_size)
		throw BadArgument();

	return m_data[index];
}

template<typename T>
void Storage<T>::add(T value)
{
	if (m_data == nullptr)
	{
		m_data = new T[1];
		m_data[0] = value;
		m_size = 1;
	}
	else
	{
		T* buffer = new T[m_size + 1];
		for (size_t i = 0; i < m_size; i++)
			buffer[i] = m_data[i];
		buffer[m_size] = value;
		delete[] m_data;
		m_data = buffer;
		++m_size;
	}
}

template<typename T>
void Storage<T>::insert(size_t index, T value)
{
	if (index < 0 || index > m_size)
		throw BadArgument();

	T* newData = new T[m_size + 1];

	for (size_t i = 0; i < index; ++i)
		newData[i] = m_data[i];

	newData[index] = value;

	for (size_t i = index; i < m_size; ++i)
		newData[i + 1] = m_data[i];

	delete[] m_data;
	m_data = newData;
	++m_size;
}

template<typename T>
void Storage<T>::remove(size_t index)
{
	if (index < 0 || index >= m_size)
		throw BadArgument();

	T* newData = new T[m_size - 1];

	for (size_t i = 0; i < index; i++)
		newData[i] = m_data[i];

	for (size_t i = index; i < m_size - 1; i++)
		newData[i] = m_data[i + 1];

	delete[] m_data;
	m_data = newData;
	--m_size;
}

template<typename T>
size_t Storage<T>::size() const
{
	return m_size;
}
