#include <Toy.h>
#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Toy::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Toy::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0,
		};

		Toy::Ref<Toy::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Toy::VertexBuffer::Create(vertices, sizeof(vertices)));
		Toy::BufferLayout layout = {
			{ Toy::ShaderDataType::Float3, "a_Position" },
			{ Toy::ShaderDataType::Float4, "a_Color" }
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		Toy::Ref<Toy::IndexBuffer> indexBuffer;
		indexBuffer.reset(Toy::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Toy::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Toy::Ref<Toy::VertexBuffer> squareVB;
		squareVB.reset(Toy::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Toy::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Toy::Ref<Toy::IndexBuffer> squareIB;
		squareIB.reset(Toy::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 450 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Toy::Shader::Create(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader.reset(Toy::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Toy::Timestep timestep) override
	{
		if (Toy::Input::IsKeyPressed(TOY_KEY_LEFT) || Toy::Input::IsKeyPressed(TOY_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		else if (Toy::Input::IsKeyPressed(TOY_KEY_RIGHT) || Toy::Input::IsKeyPressed(TOY_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		if (Toy::Input::IsKeyPressed(TOY_KEY_UP) || Toy::Input::IsKeyPressed(TOY_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		else if (Toy::Input::IsKeyPressed(TOY_KEY_DOWN) || Toy::Input::IsKeyPressed(TOY_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;

		if (Toy::Input::IsKeyPressed(TOY_KEY_Q))
			m_CameraRotation += m_CameraRotateSpeed * timestep;
		else if(Toy::Input::IsKeyPressed(TOY_KEY_E))
			m_CameraRotation -= m_CameraRotateSpeed * timestep;

		Toy::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Toy::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Toy::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		
		std::dynamic_pointer_cast<Toy::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Toy::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0), pos) * scale;
				Toy::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		Toy::Renderer::Submit(m_Shader, m_VertexArray);

		Toy::Renderer::EndScene();

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Toy::Event& event) override
	{

	}

private:
	Toy::Ref<Toy::Shader> m_Shader;
	Toy::Ref<Toy::Shader> m_FlatColorShader;

	Toy::Ref<Toy::VertexArray> m_VertexArray;
	Toy::Ref<Toy::VertexArray> m_SquareVA;

	Toy::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotateSpeed = 180.0f;


	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Toy::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Toy::Application* Toy::CreateApplication()
{
	return new Sandbox();
}