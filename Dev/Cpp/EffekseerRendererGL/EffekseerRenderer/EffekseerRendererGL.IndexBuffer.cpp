﻿
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#include "EffekseerRendererGL.IndexBuffer.h"
#include "EffekseerRendererGL.GLExtension.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace EffekseerRendererGL
{
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
IndexBuffer::IndexBuffer( RendererImplemented* renderer, GLuint buffer, int maxCount, bool isDynamic )
	: DeviceObject		( renderer )
	, IndexBufferBase	( maxCount, isDynamic )
	, m_buffer			( buffer )
{
	m_resource = new uint8_t[m_indexMaxCount * sizeof(uint16_t)];
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
IndexBuffer::~IndexBuffer()
{
	delete [] m_resource;
	GLExt::glDeleteBuffers(1, &m_buffer);
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
IndexBuffer* IndexBuffer::Create( RendererImplemented* renderer, int maxCount, bool isDynamic )
{
	GLuint ib;
	GLExt::glGenBuffers(1, &ib);
	return new IndexBuffer( renderer, ib, maxCount, isDynamic );
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void IndexBuffer::OnLostDevice()
{
	GLExt::glDeleteBuffers(1, &m_buffer);
	m_buffer = 0;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void IndexBuffer::OnResetDevice()
{
	if (IsValid()) return;
	GLuint ib;
	GLExt::glGenBuffers(1, &ib);
	m_buffer = ib;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void IndexBuffer::Lock()
{
	assert( !m_isLock );

	m_isLock = true;
	m_indexCount = 0;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void IndexBuffer::Unlock()
{
	assert( m_isLock );

	GLExt::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
	GLExt::glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(uint16_t), m_resource, GL_DYNAMIC_DRAW);
	GLExt::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_isLock = false;
}


bool IndexBuffer::IsValid()
{
	return m_buffer != 0;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
