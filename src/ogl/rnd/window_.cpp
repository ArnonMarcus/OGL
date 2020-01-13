#include "window_.h"

#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

ogl::rnd::Window::Window(const char* title, const int width, const int height) : title_(title), width_(width), height_(height)
{
	if (!init())
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	for (bool& m_mouse_button : mouse_buttons_) m_mouse_button = false;
	for (bool& m_key_pressed : keys_pressed_) m_key_pressed = false;
}

ogl::rnd::Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window_);
	glfwTerminate();
}

bool ogl::rnd::Window::init()
{
	glfwSetErrorCallback(on_error);

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize!\n");
		return false;
	}
		
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
	if (!window_)
	{
		fprintf(stderr, "Failed to create a window!\n");
		return false;
	}

	glfwMakeContextCurrent(window_);
	glfwSwapInterval(1); // Enable v-sync

	glfwSetWindowUserPointer(window_, this);
	glfwSetKeyCallback(window_, on_key_pressed);
	glfwSetWindowSizeCallback(window_, on_resize);

	if (!gladLoadGL())
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return false;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window_, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	return true;
}

void ogl::rnd::Window::update()
{
	current_test_.OnUpdate(0.0f);
}

void ogl::rnd::Window::render()
{
	current_test_.OnRender();
}

void ogl::rnd::Window::renderGUI()
{
	current_test_.OnRenderGUI();
}

void ogl::rnd::Window::start()
{
	while (!glfwWindowShouldClose(window_))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		update();
		render();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		renderGUI();

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window_);
		glfwPollEvents();
	}
}

void ogl::rnd::Window::on_resize(GLFWwindow* window, int width, int height)
{
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	win->width_ = width;
	win->height_ = height;
	glViewport(0, 0, width, height);
}

void ogl::rnd::Window::on_key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		return glfwSetWindowShouldClose(window, GLFW_TRUE);

	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	win->keys_pressed_[key] = action != GLFW_RELEASE;
}

void ogl::rnd::Window::on_error(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}
