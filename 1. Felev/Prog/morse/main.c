#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Morse
{
    char letter;
    struct Morse *dot; //bal
    struct Morse *line; //jobb
}Morse;

typedef struct Queue
{
    Morse *morse;
    struct Queue *under;
}Queue;

Queue *Add(Queue *queue, Morse *morse)
{
    Queue *New = (Queue *)malloc(sizeof(Queue));
    New->morse = morse;
    New->under = queue;
    return New;
}


Morse *Get(Queue **queue)
{
    Morse *morse = (*queue)->morse;
    *queue = (*queue)->under;
    return morse;
}

Morse *BuildTree(Morse *morse, char *letters)
{
    char *leafs = "hvflpjbxcyzq ";
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue = Add(queue, morse);
    for(int idx = 0; idx < 30; idx += 2)
    {
        Morse *morseDot = (Morse *)malloc(sizeof(Morse));
        Morse *morseLine = (Morse *)malloc(sizeof(Morse));
        //printf("betuk: %c %c\n", letters[idx], letters[idx + 1]);
        morseDot->letter = letters[idx];
        morseLine->letter = letters[idx+1];
        Morse *current = Get(&queue);
        current->dot = morseDot;
        current->line = morseLine;

        if(strchr(leafs, letters[idx]) == NULL)
        {
            queue = Add(queue, morseLine);
            queue = Add(queue, morseDot);
        }else
        {
            morseDot->dot = NULL;
            morseDot->line = NULL;
            morseLine->dot = NULL;
            morseLine->line = NULL;
        }
    }
    return morse;
}

void Write(Morse *morse)
{
    if(morse == NULL)
        return;

    Write(morse->dot);
    printf("%c ", morse->letter);
    Write(morse->line);
}

int main()
{
    char letters[30] = {'e', 't', 'i', 'a', 's', 'u', 'h', 'v', 'f', ' ', 'r', 'w', 'l', ' ', 'p', 'j', 'n', 'm', 'd', 'k', 'b', 'x', 'c', 'y', 'g', 'o', 'z', 'q', ' ', ' '};
    Morse *morse = (Morse *)malloc(sizeof(Morse));
    morse->letter = ' ';

    BuildTree(morse, letters);
    /*
        printf("%c %c\n", morse->dot->letter, morse->line->letter);
        printf("%c\n", (morse->line)->line->letter);

        printf("%c %c %c %c\n", morse->dot->dot->letter, morse->dot->line->letter, morse->line->dot->letter, morse->line->line->letter);
    */
    //printf("-%c-\n", morse->line->dot->line->dot->letter);
    Write(morse);
    return 0;
}
