#pragma once

#include "Test.h"

namespace test
{
	class TestClearColor :public Test
	{
	public:
		TestClearColor();
		~TestClearColor();
		void OnUpdate(float deltaTime = 0)override;
		void OnRender()override;
		void OnImGuiRender()override;
	private:
		float m_ClearColor[4];
	};
}
