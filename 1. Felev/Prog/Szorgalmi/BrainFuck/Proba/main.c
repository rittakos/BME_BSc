#include <stdio.h>
#include <stdlib.h>

int Left(int position)
{
	if (position != 0)
		return --position;
	else
		exit;
	return -1;
}
int Right(int position)
{
	if (position != 32767)
		return ++position;
	else
		exit;
	return -1;
}
void Write(char c)
{
	printf("%c",c);
}

char Read()
{
	char c;
	scanf("%c", &c);
	if (c == EOF)
		return -1;
	return ' ';
}

int findNextLoopEnd(int currentId, char programkod[])
{
	for (int idx = currentId; currentId < sizeof(programkod) / sizeof(programkod[0]); ++idx)
	{
		if (programkod[idx] == ']')
			return idx;
	}
}

void Log(int idx, char programkod[], int tape[], int position, FILE* file)
{
	
	fprintf(file, "idx: %d", idx);
	//fprintf(file, "fsfs");
	for (int id = idx - 5; id < idx + 5; ++id)
	{
		if (id > 0 && id < strlen(programkod))
		{
			if (id != idx)
				fprintf(file, " %c ", programkod[id]);
			else
				fprintf(file, " -%c- ", programkod[id]);
		}
	}

		fprintf(file,"   %d   ", position);

	for (int id = position - 10; id < position + 10; ++id)
	{
		if (id >= 0 && id < 32768)
		{
			if (id != position)
				fprintf(file, " %d ", tape[id]);
			else
				fprintf(file, " -%d- ", tape[id]);
		}
	}
	fprintf(file, "\n");
	
}

int main()
{
	//char programkod[] = "++++>++[<[-.]>-]";
	//char programkod[] = "-[]";
	char programkod[] = "[.]>++++[<++++++++>-]>++++++++[>++++<-]>>++>>>+>>>+<<<<<<<<<<[-[->+<]>[-<+>>>.<<]>>>[[->++++++++[>++++<-]>.<<[->+<]+>[->++++++++++<<+>]>.[-]>]]+<<<[-[->+<]+>[-<+>>>-[->+<]++>[-<->]<<<]<<<<]++++++++++.+++.[-]<]+++++";
	//char programkod[] = "+";
	int tape[32768] = {0};
	int position = 0;

	FILE *file;
	file = fopen("log2.txt", "w+");


	int idx = 0;
	char currentCommand = programkod[idx];
	int numOfOpen = 0;
	//int numOfClose = 0;
	int loopId[32768] = {0};

	while (currentCommand != 0)
	{
		if (idx == 108)
		{
			printf("");
		}
		//printf("%d\n", position);
		if (currentCommand == '+')
			++tape[position];
		else if (currentCommand == '-')
			--tape[position];
		else if(currentCommand == '.')
			printf("%c", tape[position]);
		else if(currentCommand == ',')
		{
			//EOF kell meg
			
			tape[position] = getchar();
		}
		else if(currentCommand == '<')
		{
			if (position != 0)
				--position;
			else
			{
				printf("LeftError\n");
				exit(EXIT_SUCCESS);
			}
		}
		else if(currentCommand == '>')
		{
			if (position != 32767)
				++position;
			else
			{
				printf("RightError\n");
				exit(EXIT_SUCCESS);
			}
		}
		else if(currentCommand == '[')
		{
			if (tape[position] != 0)
			{
				loopId[numOfOpen] = idx;
				++numOfOpen;
			}
			else
			{
				idx = findNextLoopEnd(idx, programkod);
			}
			
		}
		else if(currentCommand == ']')
		{
			if (numOfOpen == 0)
			{
				printf("LoopError");
				exit(EXIT_SUCCESS);
			}
			else
			{
				--numOfOpen;
				if (tape[position] != 0)
				{
					idx = loopId[numOfOpen];
					++numOfOpen;
				}
			}
		}
		else
		{
			
		}
		Log(idx, programkod, tape, position, file);
		++idx;
		currentCommand = programkod[idx];
	}
	fclose(file);
	//printf("%d", tape[0]);
	printf("\n");
}
