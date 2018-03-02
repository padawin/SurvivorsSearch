#ifndef __DIALOGUE_WINDOW__
#define __DIALOGUE_WINDOW__

#include "Window.hpp"
#include "../../Observer.hpp"
#include "../../Dialogue.hpp"
#include <string>

class Actor;
class DialogueWindow : public NCurseWindow, public Observer {
	private:
	std::string m_sDialogue = "";
	Dialogue &m_dialogues;

	public:
	DialogueWindow(Dialogue &dialogues);
	void setDialogue(std::string dialogue);
	void onNotify(E_Event event, Actor *actor);
	void render();
};

#endif
