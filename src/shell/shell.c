/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:14:01 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/27 01:17:09 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_builtin(t_shell *self, t_node *node)
{
	t_node	*name;

	if (node->kind != NODE_COMMAND || !node->arguments)
		return (1);
	name = node->arguments;
	if (ft_strcmp(name->value, "export") == 0)
		return (builtin_export(self, name->next));
	if (ft_strcmp(name->value, "unset") == 0)
		return (builtin_unset(self, name->next));
	if (ft_strcmp(name->value, "pwd") == 0)
		return (buildin_pwd(self, name->next));
	if (ft_strcmp(name->value, "cd") == 0)
		return (buildin_cd(self, name->next));
	if (ft_strcmp(name->value, "exit") == 0)
		return (buildin_exit(self, name->next));
	if (ft_strcmp(name->value, "echo") == 0)
		return (buildin_echo(self, name->next));
	return (0);
}

/**
 * @brief Executes a command line.
 * 
 * @param self 
 * @param input 
 */
int	shell_execute(t_shell *self, char *input)
{
	t_token	*tokens;
	t_node	*node;

	tokens = lexer_lex(&self->lexer, input);
	if (tokens && !self->lexer.error)
	{
		node = parser_parse(&self->parser, tokens);
		if (node && !self->parser.error)
		{
			shell_builtin(self, node);
			node_destroy(node);
		}
	}
	add_history(input);
	free(input);
	token_destroy(tokens);
	return (0);
}

/**
 * @brief Main shell loop.
 * 
 * @param self 
 * @return int 
 */
int	shell_start(t_shell *self)
{
	char	*input;

	self->code = 0;
	self->env = NULL;
	while (true)
	{
		input = readline("minishell $ ");
		if (!input)
			break ;
		shell_execute(self, input);
	}
	return (0);
}
