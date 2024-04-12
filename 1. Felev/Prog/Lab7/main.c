#include <stdio.h>
#include <stdlib.h>

void E2()
{
    int count = 0;

    scanf("%d", &count);

    int *nums = (int*)malloc(count * sizeof(int));

    for(int idx = 0; idx < count; ++idx)
    {
        scanf("%d", &nums[idx]);
    }
    for(int idx = count - 1; idx >= 0; --idx)
    {
        printf("%d\n", nums[idx]);
    }
    free(nums);
}

void E3()
{
    int *nums = (int*)malloc(0);


    int num = 0;
    int count = 0;
    while(scanf("%d", &num) == 1)
    {
        ++count;
        realloc(nums, count * sizeof(int));
        nums[count-1] = num;
    }
    for(int idx = count - 1; idx >= 0; --idx)
    {
        printf("%d\n", nums[idx]);
    }
}

void E4()
{
    char *string = (char*)malloc(sizeof(char));
    string[0] = 0;

    char letter = 0;
    int count = 0;
    scanf("%c", &letter);
    while(letter != '\n')
    {
        ++count;
        realloc(string, (count + 1) * sizeof(int));
        string[count-1] = letter;
        string[count] = '\0';
        scanf("%c", &letter);
    }
    printf("%s\n", string);
    free(string);
}

char *E5()
{
    char *string = (char*)malloc(sizeof(char));
    string[0] = 0;

    char letter = 0;
    int count = 0;
    scanf("%c", &letter);
    while(letter != '\n')
    {
        ++count;
        realloc(string, (count + 1) * sizeof(int));
        string[count-1] = letter;
        string[count] = '\0';
        scanf("%c", &letter);
    }
    return string;
}

int main()
{
    //E2();
    //E3();
    //E4();
    printf("%s", E5());
    return 0;
}
