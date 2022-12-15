#include "pch.hpp"
#include "audio/audio.hpp"

#include "utils/logging.hpp"

namespace Pear
{
	void Audio::Start()
	{
		ma_engine_config engine_config;
        ma_resource_manager_config resource_manager_config;

        resource_manager_config = ma_resource_manager_config_init();
        ma_result result = ma_resource_manager_init(&resource_manager_config, &sound_resource_manager);
        if (result != MA_SUCCESS)
        {
            ASSERT(false, "Initializing sound resource manager didn't succeed")
            return;
        }

        engine_config = ma_engine_config_init();
        engine_config.pResourceManager = &sound_resource_manager;

        result = ma_engine_init(&engine_config, &sound_engine);
        if (result != MA_SUCCESS)
        {
            ASSERT(false, "Initializing sound engine didn't succeed")
            return;
        }
	}

	void Audio::End()
	{
        ma_resource_manager_uninit(&sound_resource_manager);
        ma_engine_uninit(&sound_engine);
	}

	std::unique_ptr<Sound> Audio::LoadSound(const std::string& path)
	{
        auto sound2 = new ma_sound;
        if (const ma_result result = ma_sound_init_from_file(&sound_engine, path.c_str(),
            MA_SOUND_FLAG_ASYNC, nullptr, nullptr, sound2);
            result != MA_SUCCESS)
        {
            ASSERT(false, "Error in while initializing sound from file")
        }

        return std::make_unique<Sound>(sound2);
	}
}
