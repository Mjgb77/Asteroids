#include "SoundPlayer.hpp"
#include <string>

#include <iostream>

using namespace std;

SoundPlayer::SoundPlayer()
{
	m_engine = irrklang::createIrrKlangDevice();
	system("cls");
}

SoundPlayer::~SoundPlayer() {
	m_engine->drop();
}

void SoundPlayer::AddSound(Sound * sound) {
	sound->m_soundSource = m_engine->addSoundSourceFromFile(sound->m_filePath);
	sound->m_soundSource->setDefaultVolume(sound->m_volume);
}

void SoundPlayer::PlaySound(Sound * sound, bool looped) {
	m_engine->play2D(sound->m_soundSource, looped);
}

void SoundPlayer::StopSound(Sound * sound) {
	m_engine->stopAllSoundsOfSoundSource(sound->m_soundSource);
}
