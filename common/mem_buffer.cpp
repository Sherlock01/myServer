#include "mem_buffer.h"

#include <cstring>

MemBuffer::MemBuffer(uint32_t capacity)
{
	Init(capacity);
}

MemBuffer::~MemBuffer()
{
	UnInit();
}

bool MemBuffer::Init(uint32_t capacity)
{
	m_buffer = new char[capacity]; //TODO 内存申请和释放方式待定
	if (NULL == m_buffer)
	{
		return false;
	}
	m_capacity = capacity;
	m_head = 0;
	m_tail = 0;
	return true;
}

void MemBuffer::UnInit()
{
	delete[] m_buffer;
	m_buffer = NULL;
	m_head = 0;
	m_tail = 0;
}

bool MemBuffer::Write(const char* str, uint32_t len)
{
	if (NULL == str || 0 == len)
	{
		return false;
	}
	if (m_tail + len > m_capacity)
	{
		return false;
	}
	memcpy(m_buffer + m_tail, str, len);	
	m_tail += len;
	return true;
}

bool MemBuffer::ReadOnly(char* str, uint32_t len)
{
	if (NULL == str || 0 == len)
	{
		return false;
	}
	if (m_head + len > m_tail)
	{
		return false;
	}
	memcpy(str, m_buffer + m_head, len);
	return true;
}

bool MemBuffer::Remove(uint32_t len)
{
	if (m_head + len > m_tail)
	{
		return false;
	}
	m_head += len;
	return true;
}

bool MemBuffer::ReadAndRemove(char* str, uint32_t len)
{
	if (ReadOnly(str, len))	
	{
		return Remove(len);
	}
	return false;
}

void MemBuffer::Reset()
{
	m_head = m_tail = 0;
}

