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

	void VertexArray::add_vertex_buffer(const VertexBuffer& vertex_buffer)
	{
		bind();
		vertex_buffer.bind();

		// Этот цикл перебирает все элементы (атрибуты) в макете буфера вершин.
		for (const BufferElement& current_element : vertex_buffer.get_layout().get_elements()) {
			// Включает массив вершинных атрибутов для текущего элемента.
			glEnableVertexAttribArray(m_elements_count);

			// Настраивает указатель на атрибут вершины для текущего элемента.
			glVertexAttribPointer(
				m_elements_count,
				static_cast<GLint>(current_element.components_count),
				current_element.component_type,
				GL_FALSE,
				static_cast<GLsizei>(vertex_buffer.get_layout().get_stride()),
				reinterpret_cast<const void*>(current_element.offset)
			);
			++m_elements_count;
		}
	}


	void VertexArray::set_index_buffer(const IndexBuffer& index_buffer)
	{
		bind();
		index_buffer.bind();
		m_indices_count = index_buffer.get_count();
	}
}