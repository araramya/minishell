/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:58:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/28 15:05:04 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_env **env, int argc, char **argv)
{
	t_lexer	lexer;
	t_token	*tokens;

	(void)env;
	if (argc < 2)
		return (0);
	tokens = lexer_lex(&lexer, argv[1]);
	if (!tokens || lexer.error)
		return (1);
	token_print(tokens);
	token_destroy(tokens);
	return (0);
}
