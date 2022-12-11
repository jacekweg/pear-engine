#include "pch.hpp"
#include "sound.hpp"

namespace Pear
{
	Sound::Sound(ma_sound* new_sound)
		:sound_ptr(new_sound)
	{
	}

	Sound::~Sound()
	{
		ma_sound_uninit(sound_ptr);
		delete sound_ptr;
	}

	void Sound::Play() const
	{
		ma_sound_start(this->sound_ptr);
	}

	void Sound::Pause() const
	{
		ma_sound_stop(this->sound_ptr);
	}

	void Sound::Stop() const
	{
		ma_sound_stop(this->sound_ptr);
		ma_sound_seek_to_pcm_frame(this->sound_ptr, 0);
	}

	void Sound::Restart() const
	{
		ma_sound_seek_to_pcm_frame(this->sound_ptr, 0);
		ma_sound_start(this->sound_ptr);
	}

	void Sound::SetVolume(const float volume) const
	{
		ma_sound_set_volume(this->sound_ptr, volume);
		
	}

	float Sound::GetVolume() const
	{
		return ma_sound_get_volume(this->sound_ptr);
	}

	void Sound::Loop(const bool is_looping) const
	{
		ma_sound_set_looping(this->sound_ptr, is_looping);
	}

	bool Sound::IsLooping() const
	{
		return ma_sound_is_looping(this->sound_ptr);
	}

	bool Sound::IsFinished() const
	{
		return ma_sound_at_end(this->sound_ptr);
	}
}
