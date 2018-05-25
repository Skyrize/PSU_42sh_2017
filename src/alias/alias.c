/*
** EPITECH PROJECT, 2017
** alias42sh
** File description:
** alias.c
*/

#include "42sh.h"
#include "my.h"

int		check_name_exist(ll_alias_t *lla, char *name, char *alias)
{
	for (ll_alias_t *tmp = lla->next; tmp; tmp = tmp->next) {
		if (strcmp(tmp->name, name) == 0) {
			free(tmp->alias);
			tmp->alias = malloc(sizeof(char) * strlen(alias) + 1);
			strcpy(tmp->alias, alias);
			write_alias(lla);
			return (1);
		}
	}
	return (0);
}

void 		alias_func(char **str, shell_t shell, int *ret_value)
{
	char *str_alias = NULL;

	(void)shell;
	(void)ret_value;
	if (my_tablen(str) > 3) {
		str_alias = get_str_alias(str);
		add_alias(str[1], str_alias, shell.aliases, 1);
	} else if (my_tablen(str) == 3) {
		add_alias(str[1], str[2], shell.aliases, 0);
	} else if (my_tablen(str) == 1) {
		sort_lla(shell.aliases);
		print_alias(shell.aliases);
	}

}

// char **alias_core(char **cmd, ll_alias_t *tmp, char **str, int *loop)
// {
// 	if (alias_loop(tmp, lla) == 1) {
// 		printf("Alias loop.\n");
// 		*loop = 1;
// 		return (str);
// 	} else if (alias_loop(tmp, lla) == 2)
// 		return (str);
// 	while (alias_is_another(tmp->alias, lla))
// 		tmp = step_up_alias(tmp->alias, lla);
// 	cmd = my_str_to_word_array(tmp->alias, ' ');
// 	cmd = my_strtab_cat(cmd, str);
// 	return (cmd);
// }

char **replace_alias(char **str, ll_alias_t *lla, int *loop)
{
	ll_alias_t *tmp = lla->next;
	char **cmd = NULL;

	for (; tmp; tmp = tmp->next) {
		if (strcmp(str[0], tmp->name) != 0 || !tmp->name)
			continue;
		if (alias_loop(tmp, lla) == 1) {
			printf("Alias loop.\n");
			*loop = 1;
			return (str);
		} else if (alias_loop(tmp, lla) == 2)
			return (str);
		while (alias_is_another(tmp->alias, lla))
			tmp = step_up_alias(tmp->alias, lla);
		cmd = my_str_to_word_array(tmp->alias, ' ');
		cmd = my_strtab_cat(cmd, str);
		return (cmd);
	}
	return (str);
}