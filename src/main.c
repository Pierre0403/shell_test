/*
** EPITECH PROJECT, 2022
** 
** File description:
** 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <linux/limits.h>
#include <pwd.h>
#include <sys/types.h>

int my_strlen(char const *str)
{
    int i = 0;

    for (i = 0; str[i] != '\0'; i++) {
    }
    return i;
}

char *concat_strings(char *dest , char const *src)
{
    int len = my_strlen(dest) + my_strlen(src);
    char *final_src = malloc(sizeof(char) * len + 2);
    int i = 0;
    int j = 0;
    
    for ( ; i < my_strlen(dest); i++) {
        final_src[i] = dest[i];
    }
    final_src[i] = '/';
    i++;
    for ( ; j < my_strlen(src); i++, j++) {
        final_src[i] = src[j];
    }
    final_src[i] = '\0';
    return final_src;    
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

char *find_path(char **env)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (env[i][0] == 'P' && env[i][1] == 'A' && \
        env[i][2] == 'T' && env[i][3] == 'H') {
            return env[i];
        }
    }
    return NULL;
}

char *find_cmd(char **all_path, char *buffer, char **cmd) 
{
    char *tmp_str;
    int reset_i = 0;
    
    for (int i = 0; all_path[i] != NULL; i++) {
        if(i - 1 != reset_i) 
            i = reset_i + 1;
        reset_i = i;
        tmp_str = concat_strings(all_path[i], "/");
        tmp_str = concat_strings(all_path[i], cmd[0]);
        if (access(all_path[i], F_OK) == 0) {
            return all_path[i];
        }
    }    
    return NULL;
}

int  main(int argc, char **argv, char **envp)
{
	char *buffer = NULL;
	size_t buf_size = 2048;
	char **cmd = NULL;
        char *good_path;
	char **env = NULL;
        char *path = find_path(envp);
        pid_t pid;
        char **all_path = split(path, ":");
        
	buffer = malloc(sizeof(char) * 200);
	if (buffer == NULL) {
            perror("Malloc failure");
		return (84);
	}
	write(1, "$> ", 3);
	while (getline(&buffer, &buf_size, stdin) > 0) {
		cmd = split(buffer, "\n\t");
                good_path = concat_strings(find_cmd(all_path, buffer, cmd), "/");
                good_path = concat_strings(find_cmd(all_path, buffer, cmd), cmd[0]);
                execve(good_path,cmd, envp);              
	}
	return (0);
}
