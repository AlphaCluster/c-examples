#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const size_t BUFFER_SIZE = 512;

bool parse_line(long *first, long *second, char *operation, const char *buffer)
{
    char localBuffer[BUFFER_SIZE];
    for (size_t index = 0; index < strlen(buffer) && index < BUFFER_SIZE; index++)
    {
        if ((buffer[index] == '+') ||
            (buffer[index] == '-') ||
            (buffer[index] == '*') ||
            (buffer[index] == '/'))
        {
            // Grab operation
            *operation = buffer[index];
            // Save first number as this is the middle
            *first = strtol(localBuffer, NULL, 10);
            localBuffer[0] = 0;
        }

        if (buffer[index] == '\0')
        {
            *second = strtol(localBuffer, NULL, 10);
            return true;
        }

        localBuffer[strlen(localBuffer)] = buffer[index];
    }

    return false;
}

int main() {
    char *line = NULL;
    size_t length = 0;
    ssize_t status = 0;

    printf("Enter a equation:\n");

    status = getline(&line, &length, stdin);
    // Move to local buffer so we can make sure the dynamic memory is freed.
    char buffer[BUFFER_SIZE];
    strcpy(buffer, line);
    // Free dynamic memory.
    free(line);

    long first;
    long second;
    char operand;
    bool result = parse_line(&first, &second, &operand, buffer);

    printf("Read: %ld %c %ld", first, operand, second);
    return 0;
}
