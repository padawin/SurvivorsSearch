-- needs a run function for the engine to execute
-- can have access to the following functions:
-- - notify
-- - map_removeActor(x, y)
function run(observer, map, x, y)
	SURVIVOR_SAVED = 3
	notify(observer, SURVIVOR_SAVED)
	map_removeActor(map, x, y)
end
