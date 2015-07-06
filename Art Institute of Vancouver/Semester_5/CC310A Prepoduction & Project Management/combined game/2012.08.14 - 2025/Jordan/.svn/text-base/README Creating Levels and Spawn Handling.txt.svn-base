The following information is everything a level designer would need to know:

---------------------
Making Level Pathways
---------------------
To make a path, simply place down same-coloured waypoints for the units to follow
	Examples:
		S, 1, 2, 3, E
Note: Every path must start with an S node object and end with an E node object

This way every path is determined by it's colour (the path number is represented by a specific colour)
	Example:
		Black path: rS, r1, r2, r3, rE
		Red path: bS, bE
		Blue path: gS, g1, g2, g3, g4, g5, g6, g7, gE

The order of paths determined by colour is:
1st path: Black
2nd path: Red
	Example: If I want only 1 path I'd use just black waypoints, but if I wanted two paths, the first path would be black and the second would be red.


--------------
Spawning Units
--------------
You can set ALL the settings for spawning units in a room specific script
Here's how it's done:
	1. In the room editor, in the settings tab, in creation code, type the name of the room script
		Example: scr_roomTest_create();
	2. Then in the script (scr_roomTest_create in our example), put all your settings inside the following curly-brackets:
	with(pPathingManager)
	{
    		PUT ALL YOUR SETTINGS HERE!!!
	}
That's it! Here's the list of settings you can set so far, and if you need more, just let me (Daniel Schenker) know!
enemyTotal
	The total amount of enemies that spawn in a level
enemyPathRandomize
	Setting this to false causes the spawn of enemies to be distributed equally between paths
	Setting this to true causes the spawn of enemies to be distributed randomly  between paths
enemySpawnRate
	How long inbetween enemy spawns
	The time between spawns is equal to enemySpawnRate / framerate of game (in our case 60 frames per second)
	1 = Spawn 1 enemy per 0.0166666... seconds
	15 = Spawn 1 enemy per 0.25 seconds
	60 = Spawn 1 enemy per 1 second
	180 = Spawn 1 enemy per 3 seconds