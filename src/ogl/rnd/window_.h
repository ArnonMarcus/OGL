#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../tests/TestClearColor.h"

constexpr auto MAX_KEYS = 1024;
constexpr auto MAX_BUTTONS = 32;
constexpr auto glsl_version = "#version 330 core";

namespace ogl
{
	namespace rnd
	{		
		class Window
		{	
			GLFWwindow* window_;
			
			const char* title_;
			int width_, height_;
			int x_ = 0;
			int y_ = 0;

			bool keys_pressed_[MAX_KEYS];
			bool mouse_buttons_[MAX_BUTTONS];

			test::TestClearColor current_test_;
			
		public:
			Window(const char* title, const int width, const int height);
			~Window();;

			bool init();
			void update();
			void render();
			void renderGUI();
			void start();

			static void on_resize(GLFWwindow* window, int width, int height);
			static void on_key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void on_error(int error, const char* description);
		};
	}
}

