#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

#include <map>

enum InputType {KEYBOARD_KEY, NULL_TYPE};

class InputHandler {
	protected:
	/**
	 * State of the pressed keys on the keyboard;
	 */

	/**
	 * Maps joysticks ids and buttons state, each joystick has a list of
	 * buttons set to true or false depending on if the button is pressed
	 */
	std::map<int, bool> m_mKeysStates = {};

	virtual void _processEvents() = 0;

	/**
	 * Method called when a keyboard key is pressed or released.
	 */
	virtual void _handleKeyEvent(const int key, const bool isDown);

	public:
	virtual ~InputHandler() {}

	/**
	 * Method used to process the events poll.
	 */
	void update();

	/**
	 * Returns true if the provided key (from the keyboard) is pressed, false
	 * otherwise
	 */
	bool getKeyState(const int key);

	/**
	 * Method to set the state of a given key
	 */
	void setKeyState(const int key, bool value);
};

#endif
