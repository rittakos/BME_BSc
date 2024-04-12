#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
# include <ctype.h>


int LastLetter(char* word)
{
	int idx = strlen(word) - 1;
	while (idx >= 0 && isalpha(word[idx]) == 0)
		--idx;
	return idx;
}

void MixWord(char* word, int seed)
{
	srand(time(0) + seed);
	int lastLetterId = LastLetter(word);

	int i, j, tmp;

	for (i = lastLetterId - 1; i > 0; --i)
	{
		j = rand() % (i + 1);
		while (!(j > 0 && j < lastLetterId))
			j = rand() % (i + 1);
		printf("%d", j);
		tmp = word[j];
		word[j] = word[i];
		word[i] = tmp;
	}

}


int main()
{
	char word[51];
	char currentLetter;

	scanf("%c", &currentLetter);
	int seed = 0;
	while (currentLetter != '\n')
	{
		++seed;
		int idx = 0;

		while (currentLetter != '\n' && currentLetter != ' ')
		{
			word[idx++] = currentLetter;
			scanf("%c", &currentLetter);
		}
		word[idx] = '\0';
		if (strlen(word) > 3)
			MixWord(word, seed);

		printf("%s ", word);
		scanf("%c", &currentLetter);
	}

	return 0;
}