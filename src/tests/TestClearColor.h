#pragma once
#include "Test.h"

namespace test {
	class TestClearColor :
		public Test
	{
		float clear_color[4];
		
	public:
		TestClearColor(): clear_color{0.2f, 0.3f, 0.8f, 1.0f}
		{
		};
		~TestClearColor() {};

		void OnUpdate(float delta_time) override;
		void OnRender() override;
		void OnRenderGUI() override;
	};
}
