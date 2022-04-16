#include "Scene1.h"
#include "Application.h"
#include "Rendering/Renderer.h"
#include "Rendering/Camera.hpp"
#include "Rendering/Primitives/Renderer.h"

#include <glm/glm.hpp>

#include <iostream>
#include <optional>

std::ostream& operator<<(std::ostream& os, const glm::vec3 &vec) {
	os << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z;
	return os;
}

std::ostream& operator<<(std::ostream& os, const glm::mat4 &mat) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			os << mat[j][i] << " ";
		os << std::endl;
	}
	return os;
}

void CameraPositionController(InputManager &input, Camera &camera) {
	constexpr float velocity = 3.0f;
	constexpr float sensitivity = 0.5f;
	constexpr float constant = 0.01f;

	static std::optional<MousePosition> previousPosition;

	auto position = camera.GetPosition();
	auto rotations = camera.GetRotations();
	auto &direction = camera.GetDirection();

	if (input.GetStateForKey(KeyboardKey::W) == KeyState::Pressed) {
		position += velocity * direction.Forward * constant;
	}
	if (input.GetStateForKey(KeyboardKey::S) == KeyState::Pressed) {
		position -= velocity * direction.Forward * constant;
	}

	if (input.GetStateForKey(KeyboardKey::A) == KeyState::Pressed) {
		position -= velocity * direction.Rightward * constant;
	}
	if (input.GetStateForKey(KeyboardKey::D) == KeyState::Pressed) {
		position += velocity * direction.Rightward * constant;
	}

	if (input.GetStateForKey(KeyboardKey::LEFT_SHIFT) == KeyState::Pressed) {
		position -= velocity * direction.Upward * constant;
	}
	if (input.GetStateForKey(KeyboardKey::SPACE) == KeyState::Pressed) {
		position += velocity * direction.Upward * constant;
	}

	if (input.GetStateForKey(KeyboardKey::KP_8) == KeyState::Pressed) {
		rotations.x -= sensitivity * constant;
	}
	if (input.GetStateForKey(KeyboardKey::KP_2) == KeyState::Pressed) {
		rotations.x += sensitivity * constant;
	}

	if (input.GetStateForKey(KeyboardKey::KP_6) == KeyState::Pressed) {
		rotations.y -= sensitivity * constant;
	}
	if (input.GetStateForKey(KeyboardKey::KP_4) == KeyState::Pressed) {
		rotations.y += sensitivity * constant;
	}

	if (input.GetStateForKey(KeyboardKey::TAB) == KeyState::Pressed) {
		std::cout << "Camera Properties: " << std::endl;
		std::cout << "------------------------------------------" << std::endl;
		std::cout << "[Position]: " << position << std::endl;
		std::cout << "[Rotations]: " << rotations << std::endl;
		std::cout << "------------------------------------------" << std::endl;
		std::cout << "[Upward]: " << direction.Upward << std::endl;
		std::cout << "[Forward]: " << direction.Forward << std::endl;
		std::cout << "[Rightward]: " << direction.Rightward << std::endl;
	}

	auto mousePosition = input.GetMousePosition();
	if (previousPosition) {
		auto mouseOffset = mousePosition;
		mouseOffset.xPosition -= previousPosition->xPosition;
		mouseOffset.yPosition -= previousPosition->yPosition;
		rotations.x -= mouseOffset.yPosition * sensitivity;
		rotations.y -= mouseOffset.xPosition * sensitivity;
	}
	previousPosition = mousePosition;

	if (input.GetStateForKey(KeyboardKey::F1) == KeyState::Pressed) {
		std::cout << "Mouse position: " << mousePosition.xPosition << " " << mousePosition.yPosition << std::endl;
	}

	camera.SetPositioning(position, rotations);
}

void Scene1::Init() {
	auto &window = Application::GetMainWindow();
	uint32_t width = window->GetWidth();
	uint32_t height = window->GetHeight();

	PerspectiveCamera::Properties properties(
		  glm::radians(45.0f),
		  ((float) width) / ((float) height),
		  0.1f,
		  100.0f
	);
	camera.reset(new PerspectiveCamera(glm::vec3(0), glm::vec3(0), properties));
	shader = std::make_shared<ShaderProgram>(
		  ShaderProgram::LoadFrom(
			    "res/shaders/3DModel.vert.glsl",
			    "res/shaders/3DModel.frag.glsl"
			    )
	);

	model = std::make_shared<Model>(ModelLoader().LoadModel("res/models/Model.obj"));
	gridLine = std::make_shared<GridLine>();
	cubeProps.Init(
		  1.0f,
		  Primitive3DProps(
			    glm::vec3(0, 0, 0),
			    glm::vec3(0, 0, 0),
			    PrimitiveBody(PrimitiveBody::SHAPED, Color(0, 1.0f, 0), 20.0f)
		  )
	);

	Renderer::SetCamera(camera);
	uiController = std::make_shared<Scene1_UIController>();
	Application::GetUIRenderer().BindController(uiController);
}

void Scene1::Deinit() {
	camera.reset();
}

void Scene1::OnPreUpdate() {

}

void Scene1::OnUpdate() {
	CameraPositionController(Application::GetMainWindow()->GetInput(),*camera);
}

void Scene1::OnPostUpdate() {

}

void Scene1::OnPreRendering() {
	for (auto& mesh : model->GetMeshes()) {
		Renderer::SubmitForRendering(
			  &mesh.GetVertexArray(),
			  &mesh.GetIndexBuffer(),
			  shader.get(),
			  glm::scale(glm::mat4(1), glm::vec3(0.5f))
			  );
	}
}

void Scene1::OnPostRendering() {
	Renderer::RenderCube(*cubeProps);
	gridLine->Draw(camera->GetView(), camera->GetProjection());
}
