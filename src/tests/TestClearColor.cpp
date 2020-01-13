#include "TestClearColor.h"
#include "glad/glad.h"
#include "imgui/imgui.h"

namespace test {
	void TestClearColor::OnUpdate(float delta_time)
	{
	}

	void TestClearColor::OnRender()
	{
		glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestClearColor::OnRenderGUI()
	{
		ImGui::ColorEdit4("Clear color", clear_color);
	}
}
