#ifndef TESTRENDERTEXTURE_H
#define TESTRENDERTEXTURE_H

#include "Test.h"

namespace test {

	class TestRenderTexture : public Test
	{
	public:
		TestRenderTexture();
		~TestRenderTexture();


		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
	};
}

#endif