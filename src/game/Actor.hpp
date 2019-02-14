#ifndef __ACTOR__
#define __ACTOR__

#include "./types.hpp"
#include "behaviour/Behaviour.hpp"
#include "Map.hpp"
#include <memory>

class Actor {
	private:
	std::shared_ptr<Behaviour> m_behaviour = 0;
	E_ActorRace m_eRace;
	E_ActorType m_eType;
	std::string m_sName = "";

	std::string m_sScript = "";
	int m_iScriptState = 0;

	protected:
	S_Coordinates m_location = S_Coordinates();

	public:
	Actor(E_ActorRace race, E_ActorType type);
	virtual ~Actor() {}
	void setBehaviour(std::shared_ptr<Behaviour> behaviour);
	void setName(std::string name);

	void setScript(std::string script);

	E_ActorType getType();
	E_ActorRace getRace();
	std::string getName();

	std::string getScript();

	virtual bool isDead();
	void setX(int x);
	void setY(int y);
	S_Coordinates getLocation();

	bool update(Map &map);

	bool isNextTo(std::shared_ptr<Actor> actor);
	bool seesActor(Map &map, std::shared_ptr<Actor> actor);
};

#endif
