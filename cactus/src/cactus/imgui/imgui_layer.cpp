#include "cactuspch.h"
#include "imgui_layer.h"
#include "cactus/application.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "platform/opengl/imgui_opengl_renderer.h"

namespace cactus {

	imgui_layer::imgui_layer() : layer("imgui layer") {}

	imgui_layer::~imgui_layer() {}

	void imgui_layer::on_attach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// key mapping here
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void imgui_layer::on_detach() {}

	void imgui_layer::on_update() {
		ImGuiIO& io = ImGui::GetIO();
		application& app = application::get();
		io.DisplaySize = ImVec2(app.get_window().get_width(), app.get_window().get_height());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
		m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void imgui_layer::on_event(event& event) {}
}