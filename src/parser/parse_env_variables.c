/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** parse_env_variables
*/

#include "42sh.h"

char *get_var_name(char *str)
{
	char *name = NULL;
	int i = 0;

	while (str[i] && str[i] != '"' && str[i] != '\'')
		i++;
	name = strndup(str, i);
	return (name);
}

int is_a_env_value(env_t *env, char *str)
{
	char *var_name = get_var_name(str + 1);

	if (get_env(env, var_name) == NULL) {
		free(var_name);
		return (0);
	}
	free(var_name);
	return (1);
}

char *get_str_with_env(env_t *env, char *var_name,
						char *beg_str, char **str)
{
	char *end_str = *str + strlen(beg_str) + 1 + strlen(var_name);
	char *end_with_env = my_strcat(get_env(env, var_name), end_str);
	char *ret = my_strcat(beg_str, end_with_env);

	free(*str);
	free(beg_str);
	free(var_name);
	free(end_with_env);
	return (ret);
}

void update_iterator(char *str, int *i, bool *d_quote)
{
	if (str[*i] == '"')
		*d_quote = (*d_quote == 1 ? 0 : 1);
	if (*d_quote || str[*i] != '\'')
		return;
	for (*i += 1; str[*i] && str[*i] != '\''; *i += 1);
}

int parse_env_variables(char **str, env_t *env)
{
	char *new_str = NULL;
	char *var_name = NULL;
	bool d_quote = 0;

	if (!str)
		return (0);
	for (int i = 0; *str && (*str)[i]; i++) {
		update_iterator(*str, &i, &d_quote);
		if ((*str)[i] == '$' && (*str)[i + 1]
		&& !is_a_env_value(env, (*str) + i)) {
			my_printf("%s: Undefined variable.\n", (*str) + i + 1);
			return (1);
		} else if ((*str)[i] == '$' && (*str)[i + 1]) {
			var_name = get_var_name(*str + i + 1);
			new_str = strndup(*str, i);
			*str = get_str_with_env(env, var_name, new_str, str);
			return (0);
		}
	}
	return (0);
}