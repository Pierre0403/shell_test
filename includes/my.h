/*
** EPITECH PROJECT, 2022
** 
** File description:
** 
*/

#ifndef _MY_H_
   #define _MY_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

typedef struct		s_env
{
	char			*var;		// var name exemple : PATH
	struct s_env	*next;
}					t_env;

static t_env *first = NULL;
static char     *get_env_var(char *var);
static void  add_env_var(char *var);
static void  dup_env(char **envp);
static char     *built_in_pwd(void);
static void	add_tail(char *var);

#endif /*_MY_H_*/
