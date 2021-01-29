#include "aepch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"

namespace ArtemEngine {

	struct Renderer2DStorage
	{
		Shared<VertexArray> vertexArray;
		Shared<Shader> shader;
	};

	static Renderer2DStorage* sData;

	void Renderer2D::Init()
	{
		sData = new Renderer2DStorage();

		sData->vertexArray = VertexArray::Create();

		float squareVerts[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		Shared<VertexBuffer> vertexBuffer = VertexBuffer::Create(squareVerts, sizeof(squareVerts));
		vertexBuffer->SetLayout({
				{ ShaderDataType::Float3, "position" }
			});
		sData->vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		Shared<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, 6);

		sData->vertexArray->SetIndexBuffer(indexBuffer);

		sData->shader = Shader::Create("E:/Work/Artem/ArtemEngine/res/Shaders/basic.glsl");
	}

	void Renderer2D::Terminate()
	{
		delete sData;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		sData->shader->Bind();
		sData->shader->SetUniformMat4("u_ProjectionView", camera.GetProjectionViewMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const Color& color, float rotation)
	{
		DrawQuad({ position.x, position.y, 0 }, size, color, rotation);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Color& color, float rotation)
	{
		sData->shader->SetUniformFloat4("u_Color", color);

		Math::Matrix4 transform = Math::Translate(position) * Math::Rotate(Math::Radians(rotation), Math::Vector3(0, 0, 1)) * Math::Scale(size);
		sData->shader->SetUniformMat4("u_Transform", transform);

		sData->vertexArray->Bind();
		RenderCommand::DrawIndexed(sData->vertexArray);
	}

}