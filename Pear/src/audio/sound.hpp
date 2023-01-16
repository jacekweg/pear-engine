#pragma once

#include <miniaudio.h>

namespace Pear
{
	/**
	 * @class Sound
	 * @brief The Sound class representing an individual sound.
	 */
	class Sound
	{
	public:
		/**
		 * @brief Constructs a new Sound object from the specified miniaudio sound.
		 * @param new_sound The miniaudio sound to be used in the Sound object.
		 */
		explicit Sound(ma_sound* new_sound);
		/**
		 * @brief Destroys the Sound object.
		 */
		~Sound();

		Sound(const Sound&) = delete;
		Sound& operator=(const Sound&) = delete;
		Sound(Sound&&) = delete;
		Sound& operator=(Sound&&) = delete;

		/**
		 * @brief Plays the sound.
		 */
		void Play() const;

		/**
		 * @brief Pauses the sound.
		 */
		void Pause() const;

		/**
		 * @brief Stops the sound.
		 */
		void Stop() const;

		/**
		 * @brief Restarts the sound.
		 */
		void Restart() const;

		/**
		 * @brief Sets the volume of the sound.
		 * @param volume The volume to set.
		 */
		void SetVolume(float volume) const;

		/**
		 * @brief Gets the current volume of the sound.
		 * @return The current volume of the sound.
		 */
		[[nodiscard]] float GetVolume() const;

		/**
		 * @brief Sets whether the sound should loop or not.
		 * @param is_looping Whether the sound should loop or not.
		 */
		void Loop(bool is_looping) const;

		/**
		 * @brief Gets whether the sound is currently looping or not.
		 * @return Whether the sound is currently looping or not.
		 */
		[[nodiscard]] bool IsLooping() const;

		/**
		 * @brief Gets whether the sound has finished playing or not.
		 * @return Whether the sound has finished playing or not.
		 */
		[[nodiscard]] bool IsFinished() const;

	private:
		ma_sound* sound_ptr;
	};
}
