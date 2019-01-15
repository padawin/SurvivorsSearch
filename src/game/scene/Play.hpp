#ifndef __GAME_STATE__
#define __GAME_STATE__

class PlayScene : public State {
	private:
	//std::shared_ptr<GameActor> m_player;
	// City m_city;
	// NCurseWindow m_gameView;
	// NotificationWindow m_messagesView;
	// DialogueWindow m_dialogueView;
	// NCursesMap m_cityRenderer;
	// NCursesActor m_actorRenderer;
	// BehaviourFactory m_behaviourFactory;
	// S_Rectangle m_camera = {};

	void _renderGame();

	public:
	PlayScene(UserActions &userActions);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
