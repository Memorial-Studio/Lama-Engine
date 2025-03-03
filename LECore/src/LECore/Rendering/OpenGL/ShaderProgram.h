//
// Created by Ganza on 01.1.2025.
// 

#pragma once

namespace LamaEngine
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);
		ShaderProgram(ShaderProgram&&);
		ShaderProgram& operator = (ShaderProgram&&);
		~ShaderProgram();

		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;

		void bind() const;
		static void unbind();
		bool isCompiled() const { return m_isCompiled; }

	private:
		bool m_isCompiled;
		unsigned int m_id = 0;
	};
}	