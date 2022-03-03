/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:14:01 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/03 17:26:26 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_builtin(int argc, char **argv)
{
	if (argc == 0)
		return (0);
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env());
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argc, argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argc, argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argc, argv));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argc, argv));
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argc, argv));
	return (shell_bin(argv));
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
	char	*temp;

	tokens = lexer_lex(&self->lexer, input);
	if (tokens && !self->lexer.error)
	{
		node = parser_parse(&self->parser, tokens);
		if (node && (node->kind & NODE_COMMAND) != 0)
		{
			argv = expander_eval(node->arguments);
			argc = argument_size(argv);
			temp = ft_itoa(shell_builtin(argc, argv));
			env_set("?", temp);
			free(temp);
			argument_destroy(argv);
		}
		node_destroy(node);
	}
	add_history(input);
	free(input);
	token_destroy(tokens);
	return (0);
}

void	shell_init(t_shell *self, char **envp)
{
	size_t	i;

	self->code = 0;
	env_init();
	env_set("?", "0");
	i = 0;
	while (envp[i] != NULL)
		env_from_string(envp[i++]);
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
	env_deinit();
	return (0);
}
