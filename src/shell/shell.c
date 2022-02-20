/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:14:01 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/20 18:38:24 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_start(t_shell *self)
{
	char	*input;
	t_token	*tokens;

	self->code = 0;
	while (true)
	{
		input = readline("minishell $ ");
		if (!input)
			break ;
		tokens = lexer_lex(&self->lexer, input);
		if (!self->lexer.error)
			token_print(tokens);
		add_history(input);
		free(input);
		token_destroy(tokens);
	}
	return (0);
}
