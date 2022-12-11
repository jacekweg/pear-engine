#pragma once

#include <imconfig.h>

namespace Pear
{
	class ImGuiInstance
	{
	public:
		static void BeginRender();
		static void EndRender();

		static void BeginFrame();
		static void RenderWindow(float time_step);
		static void EndFrame();

		static void OnUpdate(float time_step);
	};

}
