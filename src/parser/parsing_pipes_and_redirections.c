/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** parsing_pipes_and_redirections
*/

#include "42sh.h"

void set_op_for_redirections_and_pipes(btree_t *node, char c)
{
	if (c == '<')
		node->op = my_strdup("<");
	else if (c == '>')
		node->op = my_strdup(">");
	else
		node->op = my_strdup("|");
}

int check_double_redirections_in_cmd(char *cmd, int i, btree_t *node)
{
	if ((cmd[i] == '<' && cmd[i - 1] == '<')
	|| (cmd[i] == '>' && cmd[i - 1] == '>')) {
		if (cmd[i] == '>')
			node->op = my_strdup(">>");
		else
			node->op = my_strdup("<<");
		cmd[i] = 0;
		cmd[i - 1] = 0;
		node->right = create_btree_node( \
					my_clean_str(node->cmd + i + 1), NULL);
		node->left = create_btree_node(my_clean_str(cmd), NULL);
		node->cmd = NULL;
		parse_cmd_for_pipes_and_redirections(node->left);
		parse_cmd_for_pipes_and_redirections(node->right);
		return (1);
	}
	return (0);
}

void recursivity_on_parsing(btree_t *node)
{
	if (!node->cmd) {
		parse_cmd_for_pipes_and_redirections(node->left);
		parse_cmd_for_pipes_and_redirections(node->right);
	}
}

void parse_cmd_for_pipes_and_redirections(btree_t *node)
{
	char *cmd = my_strdup(node->cmd);
	int len = my_strlen(node->cmd);

	recursivity_on_parsing(node);
	for (int i = len - 1; i >= 0; i--) {
		if (check_double_redirections_in_cmd(cmd, i, node))
			break;
		if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|') {
			set_op_for_redirections_and_pipes(node, cmd[i]);
			cmd[i] = 0;
			node->right = create_btree_node( \
					my_clean_str(node->cmd + i + 1), NULL);
			node->left = create_btree_node(my_clean_str(cmd), NULL);
			node->cmd = NULL;
			parse_cmd_for_pipes_and_redirections(node->left);
			parse_cmd_for_pipes_and_redirections(node->right);
			break;
		}
	}
	free(cmd);
}