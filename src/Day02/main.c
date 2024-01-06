#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *colors[] = {"red", "green", "blue"};
const int possible[] = {12, 13, 14};

int get_possible(const char *line)
{
    for (int i = 0; i < 3; i++)
    {
        char *pos = strstr(line, colors[i]);
        while (pos != NULL)
        {
            pos[0] = ' '; // replace first character to remove word
            int size = 0;
            while (pos[-2 - size] != ' ')
            {
                size++;
            }

            // check if number is possible
            if (atoi(pos - size - 1) > possible[i])
            {
                return 0;
            }

            pos = strstr(line, colors[i]);
        }
    }
    return 1;
}

int get_largest(const char *line, const char *color)
{
    char *pos = strstr(line, color);
    int largest = 0;
    while (pos != NULL)
    {
        int size = 0;
        while (pos[-2 - size] != ' ')
        {
            size++;
        }
        char *number = malloc(size + 1);
        strncpy(number, pos - size - 1, size);
        number[size] = '\0';

        int num = atoi(number);
        if (num > largest)
        {
            largest = num;
        }
        pos[0] = ' ';
        pos = strstr(line, color);
    }
    return largest;
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
        int product = 1;
        for (int i = 0; i < 3; i++)
        {
            int largest = get_largest(line, colors[i]);
            product *= largest;
        }
        sum += product;
    }
    printf("Sum: %d\n", sum);
}