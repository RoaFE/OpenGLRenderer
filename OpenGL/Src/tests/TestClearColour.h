#ifndef TESTCLEARCOLOUR_H
#define TESTCLEARCOLOUR_H


#include "Test.h"

namespace test {

	class TestClearColour : public Test
	{
	public:
		TestClearColour();
		~TestClearColour();


		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_ClearColour[4];
	};
}

#endif