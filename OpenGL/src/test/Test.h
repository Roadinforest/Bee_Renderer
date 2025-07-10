#pragma once

#include <string>
#include <vector>
#include <functional>

namespace test {
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}
		virtual void OnUpdate(float deltaTime = 0) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name);
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};

	template<typename T>
	void test::TestMenu::RegisterTest(const std::string& name)
	{
		std::cout << "Register test " << name << std::endl;
		m_Tests.push_back(std::make_pair(name, [] {return new T; }));
	}

}
