#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// array of number strings
const char *numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

// instead of replacing the entire , just replace the middle character of the word with the number
void replace(char *str, const char *sub, const char rep)
{
    char *pos = strstr(str, sub);
    do
    {
        if (pos != NULL)
        {
            int subLen = strlen(sub);
            pos[subLen / 2] = rep;
        }
        pos = strstr(str, sub);
    } while (pos != NULL);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // For each line in the file
    char line[1024];
    int sum = 0;
    while (fgets(line, sizeof(line), file))
    {
        printf("%s \n", line);
        for (int i = 0; i < 10; i++)
        {
            // insert number into the words which correspond to the number, effectively replacing the word
            replace(line, numbers[i], i + '0');
        }
        printf("%s \n", line);

        char number[3] = {'\0', '\0', '\0'};
        int lineLength = strlen(line);

        // find first number
        for (int i = 0; i < lineLength; i++)
        {
            if (line[i] >= '0' && line[i] <= '9')
            {
                number[0] = line[i];
                break;
            }
        }

        // find last number
        for (int i = lineLength - 1; i >= 0; i--)
        {
            if (line[i] >= '0' && line[i] <= '9')
            {
                number[1] = line[i];
                break;
            }
        }

        // convert to int and add to sum
        int endNumber = atoi(number);
        sum += endNumber;
        printf("end number: %d\n", endNumber);
    }

    printf("Sum: %d\n", sum);
    fclose(file);

    return 0;
}
