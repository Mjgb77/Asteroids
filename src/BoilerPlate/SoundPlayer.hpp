#ifndef SOUNDPLAYER_HPP_
#define SOUNDPLAYER_HPP_

#include <irrKlang.h>
#include "Sound.hpp"

class SoundPlayer
{
public:
	/*CONSTRUCTOR*/
	SoundPlayer();
	~SoundPlayer();

	/*PUBLIC FUNCTIONS*/
	void AddSound(Sound*);
	void PlaySound(Sound*, bool = false);
	void StopSound(Sound*);

private:
	irrklang::ISoundEngine * m_engine;

};

#endif /* SOUNDPLAYER_HPP_ */

