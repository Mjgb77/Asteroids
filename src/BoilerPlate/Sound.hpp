#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <irrKlang.h>
#include "Sound.hpp"
#include <string>

class Sound
{
	friend class SoundPlayer; //Give acces to private members
public:
	/*CONSTRUCTORS*/
	Sound(char *);
	Sound(char *, float);

private:
	/*PRIVATE MEMBERS*/
	char * m_filePath;
	float m_volume;
	irrklang::ISoundSource * m_soundSource;
};

#endif /* SOUND_HPP_ */
