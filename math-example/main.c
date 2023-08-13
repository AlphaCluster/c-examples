#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const size_t BUFFER_SIZE = 512;

enum OpCode {Add, Sub, Mult, Div, None};

enum OpCode parse_operator(char operation)
{
    enum OpCode result;
    switch (operation)
    {
        case '+':
            result = Add;
            break;
        case '-':
            result = Sub;
            break;
        case '*':
            result = Mult;
            break;
        case '/':
            result = Div;
            break;
        default:
            result = None;
            break;
    }

    return result;
}

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

            // Since we found an operator we can jump to the next spot
            // this makes sure the load that will take place later doesn't
            // end up with an operator.
            index++;
            if ((index < BUFFER_SIZE) && (index < strlen(buffer)))
                memset(localBuffer, 0, BUFFER_SIZE);
            else
                return false;
        }

        if (buffer[index] == '\n')
        {
            *second = strtol(localBuffer, NULL, 10);
            return true;
        }

        localBuffer[strlen(localBuffer)] = buffer[index];
    }

    return false;
}

long calculate_result(long first, long second, enum OpCode operation)
{
    long result = 0;
    switch (operation)
    {
        case Add:
            result = first + second;
            break;
        case Sub:
            result = first - second;
            break;
        case Mult:
            result = first * second;
            break;
        case Div:
            result = first / second;
            break;
    }

    return result;
}

int main() {
    char *line = NULL;
    size_t length = 0;
    ssize_t rStatus = 0;

    printf("Enter a equation:\n");

    rStatus = getline(&line, &length, stdin);
    // Move to local buffer so we can make sure the dynamic memory is freed.
    char buffer[BUFFER_SIZE];
    strcpy(buffer, line);
    // Free dynamic memory.
    free(line);

    long first;
    long second;
    char operand;
    bool status = parse_line(&first, &second, &operand, buffer);

    long result = calculate_result(first, second, parse_operator(operand));

    printf("Read: %ld %c %ld = %ld", first, operand, second, result);
    return 0;
}
