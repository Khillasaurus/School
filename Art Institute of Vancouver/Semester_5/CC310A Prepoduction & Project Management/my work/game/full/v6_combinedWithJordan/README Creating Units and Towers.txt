This is a simple readme on how to create your own unit or tower:

---------------------------------
Creating the object in Game Maker
---------------------------------
The first thing that you will want to do is open up the latest 
version of the project file (.gmk / .gm81). Navigate over to the 
"Unit" / "Tower" filters under "Objects."

Create any filters you think are needed. You will now create 
the Unit / Tower object. Pick and enter a name (using a proper 
naming convention). If you have a sprite, load it into Game 
Maker as well, name it properly, and set the newly-created 
object's sprite to it.

With your object, add a new "Step" event. Drag & drop the 
"Execute Code" button from the window on the right. In it, you 
will enter the following (copy & pasting works perfectly):

For a unit:

if (mStatsLoaded == false)
{
    scr_file_getUnitStats(object_get_name(object_index));
    mStatsLoaded = true;
}

For a tower:

if (mStatsLoaded == false)
{
    scr_file_getTowerStats(object_get_name(object_index));
    mStatsLoaded = true;
}


------------------
Entering the stats
------------------
Save & close everything. Your object is now in the game. Of 
course, we still need to enter in the stats. Navigate to where 
the project file is stored and there should be two text files- 
unit_types.txt and tower_types.txt. Open up whichever you need 
and follow the instructions inside.