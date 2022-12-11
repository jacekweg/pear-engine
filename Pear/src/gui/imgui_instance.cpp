#include <pch.hpp>
#include "imgui_instance.hpp"

#include "controller.hpp"
#include "commands.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace Pear
{
	void ImGuiInstance::BeginRender()
	{
		#ifdef _IMGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.FontGlobalScale = 2.0f;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		const Controller& ctrl = Controller::GetInstance();

		ImGui_ImplGlfw_InitForOpenGL(ctrl.GetWindow().GetInstance(), true);
		ImGui_ImplOpenGL3_Init("#version 460");
		#endif
	}

	void ImGuiInstance::EndRender()
	{
		#ifdef _IMGUI
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		#endif
	}

	void ImGuiInstance::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiInstance::RenderWindow(const float time_step)
	{
		static bool enable_vsync = true;
		static bool draw_wire_frames = false;
		ImGui::Begin("Stats");
		ImGui::Text("Delta time: %.4fs (%.2fms)", static_cast<double>(time_step), static_cast<double>(time_step * 1000.0f));
		ImGui::Text("FPS: %.2f", static_cast<double>(1.0f / time_step));
		ImGui::Checkbox("VSync", &enable_vsync);
		ImGui::Checkbox("Draw wire frames", &draw_wire_frames);

		Commands::DrawWireFrames(draw_wire_frames);

		if(enable_vsync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		ImGui::End();
	}

	void ImGuiInstance::EndFrame()
	{
		const ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::Render();
		const Controller& ctrl = Controller::GetInstance();
		int display_w = ctrl.GetWindow().GetWidth(), display_h = ctrl.GetWindow().GetHeight();
		glfwGetFramebufferSize(ctrl.GetWindow().GetInstance(), &display_w, &display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiInstance::OnUpdate(const float time_step)
	{
		#ifdef _IMGUI
		BeginFrame();
		RenderWindow(time_step);
		EndFrame();
		#endif
	}
}
