/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:14:01 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/07 18:41:19 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle builtins
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	shell_builtin(int argc, char **argv)
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
 * @brief Handle command node
 * 
 * @param command 
 * @return int 
 */
int	shell_command(t_node *command)
{
	char	**argv;
	int		argc;
	int		code;

	if ((command->kind & NODE_PIPE) != 0)
		code = shell_pipe(command);
	else if ((command->kind & NODE_REDIRECTION) != 0)
		code = shell_redirection(command);
	else
	{
		argv = expander_eval(command->arguments);
		argc = argument_size(argv);
		code = shell_builtin(argc, argv);
		argument_destroy(argv);
	}
	if (command->next)
		code = shell_command(command->next);
	return (code);
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
	char	*temp;
	int		code;

	if (ft_strlen(input) == 0)
		return (0);
	code = 2;
	lexer_init(&self->lexer, input, false);
	tokens = lexer_lex(&self->lexer);
	if (tokens && !self->lexer.error)
	{
		node = parser_parse(&self->parser, tokens);
		if (!self->parser.error && node && self->parser.heredoc_exit != 2)
			code = shell_command(node);
		node_destroy(node);
	}
	temp = ft_itoa(code);
	env_set("?", temp);
	free(temp);
	free(input);
	token_destroy(tokens);
	return (code);
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
		if (ft_strlen(input) > 0)
			add_history(input);
		signal_ignore();
		shell_execute(self, input);
		signal_shell();
	}
	env_deinit();
	return (0);
}
