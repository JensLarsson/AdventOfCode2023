#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *colors[] = {"red", "green", "blue"};
const int possible[] = {12, 13, 14};

int get_possible(const char *line)
{
    // copy line to new string
    char *line_copy = malloc(strlen(line) + 1);
    strcpy(line_copy, line);

    for (int i = 0; i < 3; i++)
    {
        char *pos = strstr(line_copy, colors[i]);
        while (pos != NULL)
        {
            pos[0] = ' '; // replace first character to remove word
            int size = 0;
            while (pos[-2 - size] != ' ')
            {
                size++;
            }
            // copy number as new string
            char *number = malloc(size + 1);
            strncpy(number, pos - size - 1, size);
            number[size] = '\0';

            if (atoi(number) > possible[i])
            {
                return 0;
            }

            pos = strstr(line_copy, colors[i]);
        }
    }
    return 1;
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
        int possible = get_possible(line);

        if (possible)
        {
            int size = 0;
            while (line[5 + size] != ' ')
            {
                size++;
            }
            char *number = malloc(size + 1);
            strncpy(number, line + 5, size);
            number[size] = '\0';

            printf("%s \n", number);
            sum += atoi(number);
        }
    }
    printf("Sum: %d\n", sum);
}