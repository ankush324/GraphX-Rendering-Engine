#include "pch.h"

#include "Renderer2D.h"
#include "Shaders/Shader.h"
#include "Model/Mesh/Mesh2D.h"
#include "Buffers/IndexBuffer.h"

namespace engine
{
	void Renderer2D::Submit(const Mesh2D& mesh)
	{
		m_RenderQueue.emplace_back(&mesh);
	}

	void Renderer2D::Render()
	{
		// While the queue is not empty
		while (!m_RenderQueue.empty())
		{
			const Mesh2D* mesh = m_RenderQueue.front();
			m_RenderQueue.pop_front();

			// Enable the object for rendering
			mesh->Enable();

			// Render the object
			Shader& shader = mesh->GetShader();

			// Set the transformation matrix
			gm::Matrix4 Model = mesh->GetModelMatrix();
			shader.SetUniformMat4f("u_Model", Model);

			// Normal Transform Matrix (Could be done in the vertex shader, but more efficient here since vertex shader runs for each vertex)
			gm::Matrix3 Normal = gm::Matrix3(Model);
			shader.SetUniformMat3f("u_Normal", Normal);

			// Draw the object
			GLCall(glDrawElements(GL_TRIANGLES, mesh->GetIBO()->GetCount(), GL_UNSIGNED_INT, nullptr));

			// Disable the mesh after drawing
			mesh->Disable();
		}
	}

	void Renderer2D::Render(Shader& DepthShader)
	{
		for (unsigned int i = 0; i < m_RenderQueue.size(); i++)
		{
			const Mesh2D* Mesh = m_RenderQueue.at(i);

			Mesh->BindBuffers();

			// Set the transformation matrix
			gm::Matrix4 Model = Mesh->GetModelMatrix();
			DepthShader.SetUniformMat4f("u_Model", Model);

			// Draw the object
			GLCall(glDrawElements(GL_TRIANGLES, Mesh->GetIBO()->GetCount(), GL_UNSIGNED_INT, nullptr));

			Mesh->UnBindBuffers();
		}
	}
}