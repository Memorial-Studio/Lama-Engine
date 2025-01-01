//
// Created by Ganza on 02.1.2025.
// 

#include "VertexArray.h"

#include "LECore/Log.h"

#include <glad/glad.h>

namespace LamaEngine
{
	VertexArray::VertexArray() 
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray() 
	{
		glDeleteVertexArrays(1, &m_id);
	}

	VertexArray::VertexArray(VertexArray&& vertex_array) noexcept
		: m_id(vertex_array.m_id)
		, m_elements_count(vertex_array.m_elements_count) 
	{
		vertex_array.m_id = 0;
		vertex_array.m_elements_count = 0;
	}

	void VertexArray::bind() const 
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::add_buffer(const VertexBuffer& vertex_buffer)
	{
		bind();
		vertex_buffer.bind();

		//TODO - use buffer layout

		glEnableVertexAttribArray(m_elements_count);
		glVertexAttribPointer(m_elements_count, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		++m_elements_count;
	}
}