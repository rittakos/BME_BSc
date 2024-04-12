#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void ReallocknWords(char **text, int n)
{
    int length = sizeof(text) / (16 * sizeof(char));
    **text = (char **)realloc(text, n * sizeof(char *));
    for (int idx = length; idx < n; ++idx)
        text[idx] = (char *)malloc(16 * sizeof(char));
}

void Read()
{
    FILE* input = fopen("egri.txt", "r");
    char word[16];
    char word2[16];
    //fscanf(input, "\"%s\", ", word);



    char **text = (char **)malloc(10 * sizeof(char *));
    for (int idx=0; idx < 10; ++idx)
        text[idx] = (char *)malloc(16 * sizeof(char));


    //fscanf(input, "%[a-z]", word);
    //text[0] = word;
    //printf("%s\n", word);
    //scanf("\"%s\", ", word);
    //fscanf(input, "\"%s", word);
    /*int wordId = 0;
    while(wordId < 500)
    {
        fscanf(input, "%[a-z]", word);
        text[wordId] = word;
        printf("%s\n", text[wordId]);
        ++wordId;

        **text = (char **)realloc(text, 1 * sizeof(char *));
        for (int idx=0; idx < 1; ++idx)
            text[idx] = (char *)malloc(15 * sizeof(char));

        //fscanf(input, "\"%s\", ", word);
    }*/
    int wordId = 0;
    int letterId = 0;
    bool end = false;
    bool firstMark = true;
    //while(!end)
    while(!end)
    {
        char letter= (char)fgetc(input);
        if(letter == '\"')
        {
            if(firstMark)
                firstMark = false;
            else
            {
                firstMark = true;
                if(text[wordId][letterId - 1] == '\"')
                    end = true;
                text[wordId][letterId + 1] = 0;
                letterId = 0;
                ++wordId;
                printf("%s", text[wordId]);
            }
        } else if(letter == ',' || letter == ' '){}
        else
        {
            text[wordId][letterId] = letter;
            ++letterId;
        }
    }
    //printf("%s", word);
    //printf("%s", "sdfsd");
    printf("%s", text[0]);
    fclose(input);
    //return text;
}

int main()
{
    Read();
    int idx = 0;
    /*while(true)
    {
        printf("%s ", text[idx]);
        ++idx;
    }*/
    return 0;
}
