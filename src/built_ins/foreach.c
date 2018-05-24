/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

int check_error_handling_foreach(char **str)
{
	if (my_tablen(str) < 3) {
		printf("foreach: Too few arguments.\n");
		return (1);
	}
	if (is_alpha_string(str[1]) != 1) {
		printf("foreach: Variable name must begin with a letter.\n");
		return (1);
	}
	return (0);
}

char *add_last_char(char *res, int last_semicolon)
{
	int y = 0;

	if (!res)
		return (NULL);
	for (int i = 0 ; res[i] ; i++) {
		res[i] == ';' ? y++ : 0;
		if (y == last_semicolon) {
			res[i] = 0;
			break;
		}
	}
	return (res);
}

char *process_foreach(void)
{
	char *res = NULL;
	char *input = NULL;
	int last_semicolon = 0;

	isatty(0) ? write (1, "foreach? ", 9) : 0;
	input = get_next_line(stdin);
	while (input != NULL && my_strcmp(input, "end") != 0) {
		last_semicolon++;
		isatty(0) ? write (1, "foreach? ", 9) : 0;
		input = my_clean_str(input);
		res = my_strcat(res, input);
		res = my_strcat(res, " ; ");
		if ((input = get_next_line(stdin)) == NULL)
			break;
	}
	if (add_last_char(res, last_semicolon) == NULL)
		return (NULL);
	return (res);
}

int process_loop_foreach(char *ret, char **str, env_t *env, int *ret_value)
{
	char **tmp_tab= NULL;
	char *tmp= NULL;
	int loop_foreach = 0;

	if (!ret || !str || !env)
		return (84);
	tmp_tab = my_str_to_word_array(ret, ';');
	tmp_tab[my_tablen(tmp_tab)] = NULL;
	tmp = convert_tab_to_string(tmp_tab);
	loop_foreach = my_tablen(str) - 2;
	(void) ret_value;
	for (int i = 0 ; i < loop_foreach ; i++) {
		parse_cmd(env, tmp, ret_value);
		tmp = convert_tab_to_string(tmp_tab);
	}
	ret ? free (ret) : 0;
	my_free_tab(tmp_tab);
	return (0);
}

void foreach_func(char **str, env_t *env, int *ret_value)
{
	char *ret = NULL;

	if (!str || !env) {
		*ret_value = 1;
		return;
	}
	if (check_error_handling_foreach(str) != 0
	|| (ret = process_foreach()) == NULL
	|| process_loop_foreach(ret, str, env, ret_value) != 0) {
		*ret_value = 1;
		return;
	}
}
