#ifndef __DIALOGUE_WINDOW__
#define __DIALOGUE_WINDOW__

#include "Window.hpp"
#include "../../Observer.hpp"
#include "../../Dialogue.hpp"
#include "../../UserActions.hpp"
#include <string>
#include <vector>

class Actor;
class DialogueWindow : public NCurseWindow, public Observer {
	private:
	std::vector<std::string> m_vDialogue = {};
	Dialogue &m_dialogues;
	UserActions &m_userActions;

	public:
	DialogueWindow(UserActions &userActions, Dialogue &dialogues);
	bool hasDialogue();
	void setDialogue(std::string dialogue);
	void onNotify(E_Event event, Actor *actor);
	void update();
	void render();
};

#endif
