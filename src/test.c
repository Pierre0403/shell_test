/*
** EPITECH PROJECT, 2022
** 
** File description:
** 
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void free_array(char **array)
{
    for (int i = 0; array[i]; i++) {
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
    array = NULL;
}

char **split(char *raw_cmd, char *limit)
{
    char *ptr = NULL;
    char **cmd = NULL;
    size_t idx = 0;
    int nb_word = 1;

    for (int i = 0; raw_cmd[i] != '\0'; i++) {
        if (raw_cmd[i] == ':') {
            nb_word++;
        }
    }
    cmd = malloc(sizeof(char *) * (nb_word + 1)); 
    for (int i = 0; i < nb_word; i++, raw_cmd = NULL) {
        cmd[i] = strtok(raw_cmd, limit);
    }
    cmd[nb_word] = NULL;
    return (cmd);
}

int main ()
{
    char *buffer = NULL;
    size_t buf_size = 2048;
    char *buf = malloc(sizeof(char) * 200);
    char **cmd = split(buf, "\n\t");
    
    buffer = malloc(sizeof(char) * buf_size);
    if (buffer == NULL) {
        perror("Malloc failure");
        return (EXIT_FAILURE);
    }
    write(1, "$> ", 3);
    while (getline(&buffer, &buf_size, stdin) > 0) {
        printf("%s\n", cmd);
        //  printf("cmd = %s\n", buffer);
        write(1, "$> ", 3);
    }   
    printf("Bye \n");
    free(buffer);
}
