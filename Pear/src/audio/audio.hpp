#pragma once

#include "sound.hpp"

namespace Pear
{
	/**
	 * @class Audio
	 * @brief The Audio class for handling audio in the Pear engine.
	 */
	class Audio
	{
	public:
		/**
		 * @brief Initializes the audio module.
		 */
		static void Start();

		/**
		 * @brief Shuts down the audio module.
		 */
		static void End();

		/**
		 * @brief Loads a Sound object from the specified file path.
		 * @param path The file path of the sound to be loaded.
		 * @return A unique pointer to the loaded Sound object.
		 */
		static std::unique_ptr<Sound> LoadSound(const std::string& path);
	private:
		inline static ma_engine sound_engine;
		inline static ma_resource_manager sound_resource_manager;
	};
}
