#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Player
{
	char name[4];
	int health;
};

int main()
{
	srand((unsigned)time(NULL));

	int playerCount;
	printf("How many players?\n");
	scanf("%d",&playerCount);
	struct Player list[] = (struct Player)malloc(playerCount * sizeof(struct Player));

	for(int i = 0; i < playerCount; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			list[i].name[j] = rand() % 26 + 65;
		}
		list[i].health = rand() % 50 + 50;
	}

	return 0;
}