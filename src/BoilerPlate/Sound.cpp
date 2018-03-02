#include "Sound.hpp"



Sound::Sound(char * filePath) : m_filePath(filePath), m_volume(1.0f) {
}

Sound::Sound(char * filePath, float volume) : m_filePath(filePath), m_volume(volume) {
}

