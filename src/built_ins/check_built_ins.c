/*
** EPITECH PROJECT, 2018
** minishell1_2017
** File description:
** minishell1_2017 made by Sanchez Lucas
*/

#include "42sh.h"

void reset_fd(int *fd, int *save)
{
	close(fd[0]);
	close(fd[1]);
	dup2(save[0], 0);
	dup2(save[1], 1);
}

int check_built_ins(char **str, env_t *env, int *ret_value, int *fd)
{
	char *built_ins[] = {"cd", "exit", "env", "setenv", "unsetenv",
	"echo", NULL};
	void (*fptr[])(char **, env_t *, int *) = {&cd_func, &exit_func,
	&env_func, &setenv_func, &unsetenv_func, &echo_func};
	int save[2];

	save[0] = dup(0);
	save[1] = dup(1);
	for (int i = 0; built_ins[i]; i++) {
		if (str && my_strcmp(str[0], built_ins[i]) == 0) {
			dup2(fd[0], 0);
			dup2(fd[1], 1);
			fptr[i](str, env, ret_value);
			reset_fd(fd, save);
			return (0);
		}
	}
	return (1);
}
