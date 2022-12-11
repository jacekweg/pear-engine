#pragma once

#include <miniaudio.h>

namespace Pear
{
	class Sound
	{
	public:
		explicit Sound(ma_sound* new_sound);
		~Sound();

		Sound(const Sound&) = delete;
		Sound& operator=(const Sound&) = delete;
		Sound(Sound&&) = delete;
		Sound& operator=(Sound&&) = delete;

		void Play() const;
		void Pause() const;
		void Stop() const;
		void Restart() const;

		void SetVolume(float volume) const;
		[[nodiscard]] float GetVolume() const;

		void Loop(bool is_looping) const;
		[[nodiscard]] bool IsLooping() const;

		[[nodiscard]] bool IsFinished() const;

	private:
		ma_sound* sound_ptr;
	};
}
