#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../tests/TestClearColor.h"

namespace ogl
{
	namespace rnd
	{		
		class Window
		{
			GLFWwindow* window;
			int m_width, m_height;
			test::Test m_current_test;
			
		public:
			Window(const char* title, const int width, const int height)
				: m_width(width), m_height(height)
			{
				glfwSetErrorCallback(on_error);

				if (!glfwInit())
					exit(EXIT_FAILURE);

				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				
				window = glfwCreateWindow(width, height, title, nullptr, nullptr);
				if (!window) {
					glfwTerminate();
					exit(EXIT_FAILURE);
				}

				glfwMakeContextCurrent(window);
				glfwSwapInterval(1);  // Enable v-sync
				glfwSetKeyCallback(window, on_key_pressed);

				if (!gladLoadGL()) {
					fprintf(stderr, "Failed to initialize OpenGL loader!\n");
					glfwTerminate();
					exit(EXIT_FAILURE);
				}
				
				// Setup Dear ImGui context
				IMGUI_CHECKVERSION();
				ImGui::CreateContext();
				//ImGuiIO& io = ImGui::GetIO(); (void)io;
				ImGui::StyleColorsDark();

				// Setup Platform/Renderer bindings
				ImGui_ImplGlfw_InitForOpenGL(window, true);
				ImGui_ImplOpenGL3_Init("#version 330 core");
			}

			~Window()
			{
				ImGui_ImplOpenGL3_Shutdown();
				ImGui_ImplGlfw_Shutdown();
				ImGui::DestroyContext();

				glfwDestroyWindow(window);
				glfwTerminate();
				exit(EXIT_SUCCESS);
			};
			
			void update()
			{
				m_current_test.OnUpdate(0.0f);
				m_current_test.OnRender();
				m_current_test.OnRenderGUI();
			}

			static void on_key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
					glfwSetWindowShouldClose(window, GLFW_TRUE);
			}

			static void on_error(int error, const char* description)
			{
				fprintf(stderr, "Error %d: %s\n", error, description);
			}

			void start()
			{
				while (!glfwWindowShouldClose(window)) {
					glfwGetFramebufferSize(window, &m_width, &m_height);
					glViewport(0, 0, m_width, m_height);
					glClear(GL_COLOR_BUFFER_BIT);

					// Start the Dear ImGui frame
					ImGui_ImplOpenGL3_NewFrame();
					ImGui_ImplGlfw_NewFrame();
					ImGui::NewFrame();
					
					update();

					// Rendering
					ImGui::Render();
					ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

					glfwSwapBuffers(window);
					glfwPollEvents();
				}
			}
		};
	}
}

