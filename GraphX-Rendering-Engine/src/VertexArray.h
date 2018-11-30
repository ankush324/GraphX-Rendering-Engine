#pragma once

namespace engine
{
	class VertexBuffer;
	class VertexBufferLayout;

	class VertexArray
	{
	private:
		/* Identifier for the vao */
		unsigned int m_RendererID;

	public:
		VertexArray();

		~VertexArray();

		/* Add new buffer to the vao object to be bound */
		void AddBuffer(VertexBuffer& vbo, VertexBufferLayout& layout);

		/* Bind the vao */
		void Bind() const;

		/* Un Bind the vao */
		void UnBind() const;
	};
}