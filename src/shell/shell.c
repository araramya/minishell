/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:14:01 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/01 01:13:40 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_builtin(t_shell *self, int argc, char **argv)
{
	if (argc == 0)
		return (1);
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(&self->env, argc, argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(&self->env, argc, argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (buildin_pwd());
	if (ft_strcmp(argv[0], "cd") == 0)
		return (buildin_cd(argc, argv));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (buildin_exit(argc, argv));
	if (ft_strcmp(argv[0], "echo") == 0)
		return (buildin_echo(argc, argv));
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
	char	**argv;
	int		argc;

	tokens = lexer_lex(&self->lexer, input);
	if (tokens && !self->lexer.error)
	{
		node = parser_parse(&self->parser, tokens);
		if (node && (node->kind & NODE_COMMAND) != 0)
		{
			argv = expander_eval(node->arguments);
			argc = argument_size(argv);
			shell_builtin(self, argc, argv);
			argument_destroy(argv);
		}
		node_destroy(node);
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
		{
			printf("\n");
			break ;
		}
		shell_execute(self, input);
	}
	return (0);
}
