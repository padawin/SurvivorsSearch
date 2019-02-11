#include "ActorFactory.hpp"

ActorFactory::ActorFactory()
{
}

bool ActorFactory::parseTaxonomy(const char* taxonomyFile) {
	ResourceManager<S_ActorRaceData> resourceManager;
	if (!resourceManager.setResourceFile(taxonomyFile)) {
		return false;
	}

	resourceManager.parseBinaryFile();
	for (auto raceData : resourceManager.getParsedResources()) {
		E_ActorRace raceID = (E_ActorRace) raceData.first;
		ActorRace race(raceData.second);
		m_mTaxonomy.insert(std::make_pair(raceID, race));
	}

	return true;
}

std::shared_ptr<Actor> ActorFactory::createActor(E_ActorRace race, E_ActorType type) {
	auto raceData = m_mTaxonomy.find(race);
	if (raceData == m_mTaxonomy.end()) {
		return NULL;
	}

	return raceData->second.createActor(type);
}
