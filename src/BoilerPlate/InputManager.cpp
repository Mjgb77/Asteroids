#include "InputManager.hpp"

InputManager* InputManager::s_instance = nullptr;

InputManager::InputManager()
	: m_isKeyPressed(false) {

	m_currentKeys = std::vector <bool>(KEYCOUNT);
	m_previousKeys = std::vector <bool>(KEYCOUNT);

}

void InputManager::Update() {
	m_previousKeys = m_currentKeys;
}

/*Singleton logic*/

void InputManager::Create() {
	if (!s_instance) {
		s_instance = new InputManager;
	}
}

void InputManager::Destroy() {
	if (s_instance) {
		delete s_instance;
		s_instance = nullptr;
	}
}

/*getInstance*/

InputManager& InputManager::Instance() {
	if (!s_instance) {
		Create();
	}
	return *s_instance;
}


bool InputManager::IsKeyDown(unsigned char key) {
	return m_currentKeys[key];
}

bool InputManager::IsKeyReleased(unsigned char key) const {
	return (m_currentKeys[key] == false && m_previousKeys[key] == true);
}

void InputManager::KeyDown(unsigned char key) {
	m_currentKeys[key] = true;
}

bool InputManager::IsKeyPressed(unsigned char key) {
	return m_currentKeys[key] && !m_previousKeys[key];
}

void InputManager::KeyUp(unsigned char key) {
	m_previousKeys[key] = true;
	m_currentKeys[key] = false;
}

void InputManager::ResetInput() {
	m_previousKeys = std::vector <bool>(KEYCOUNT);
	m_currentKeys = std::vector <bool>(KEYCOUNT);
}

void OnKeyboardDownEvent(unsigned char key) {
	InputManager::Instance().KeyDown(key);
}

void OnKeyboardReleasedEvent(unsigned char key) {
	InputManager::Instance().KeyUp(key);
}

void KeyboardPollEvent(){
	InputManager::Instance().Update();
}

