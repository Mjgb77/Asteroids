#ifndef INPUTMANGER_HPP_
#define INPUTMANAGER_HPP_

#include <vector>

const int KEYCOUNT = 256;
const int _KEY_INVALID = -2;

class InputManager {

public:

	static void Create();
	static void Destroy();
	static InputManager& Instance();

	bool IsKeyDown(unsigned char key);
	bool IsKeyPressed(unsigned char key);
	bool IsKeyReleased(unsigned char key) const;
	void KeyDown(unsigned char key);
	void KeyUp(unsigned char key);
	void ResetInput();
	void Update();


private:
	/*Constuctor*/

	InputManager();
	InputManager(InputManager const&) : m_isKeyPressed(false) {}

	static InputManager* s_instance;

	std::vector <bool> m_currentKeys;
	std::vector <bool> m_previousKeys;
	bool m_isKeyPressed;

};


extern void OnKeyboardDownEvent(unsigned char key);

extern void OnKeyboardReleasedEvent(unsigned char key);
extern void KeyboardPollEvent();


#endif // !INPUTMANAGER_HPP_