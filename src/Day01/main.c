#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    int sum = 0;
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
        char number[3] = {'\0', '\0', '\0'};
        int lineLength = strlen(line);

        for (int i = 0; i < lineLength; i++)
        {
            if (line[i] >= '0' && line[i] <= '9')
            {
                number[0] = line[i];
                printf("%c \n", line[i]);
                break;
            }
        }
        for (int i = lineLength - 1; i >= 0; i--)
        {
            if (line[i] >= '0' && line[i] <= '9')
            {
                number[1] = line[i];
                printf("%c \n", line[i]);
                break;
            }
        }
        sum += atoi(number);
        printf("%d\n", atoi(number));
    }
    printf("Sum: %d\n", sum);

    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    process_file(argv[1]);

    return 0;
}
