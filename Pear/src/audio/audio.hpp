#pragma once

#include "sound.hpp"

namespace Pear
{
	class Audio
	{
	public:
		static void Start();
		static void End();

		static std::unique_ptr<Sound> LoadSound(const std::string& path);
	private:
		inline static ma_engine sound_engine;
		inline static ma_resource_manager sound_resource_manager;
	};
}
