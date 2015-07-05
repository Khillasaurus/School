char* search(int playerCount, struct Player list, int &counter)
{
	if(counter >= playerCount)
	{
		return list[playerWithMostHP].name;
	}

	int playerWithMostHP = 1;
	int maxHP = 0;

	if(list[counter].health > maxHP)
	{
		playerWithMostHP = counter;
	}
	++counter;
	
	search();
	return playerWithMostHP;
}