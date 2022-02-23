/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:14:01 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/23 18:53:55 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("\nTokens:\n");
		token_print(tokens);
		node = parser_parse(&self->parser, tokens);
		if (node && !self->parser.error)
		{
			printf("\nNodes:\n");
			node_print(node, 0);
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
	while (true)
	{
		input = readline("minishell $ ");
		if (!input)
			break ;
		shell_execute(self, input);
	}
	return (0);
}
