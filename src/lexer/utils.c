/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:13:21 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/20 18:34:32 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_is_space(int c)
{
	return (c == ' ' || c == '\t');
}

int	lexer_is_word(int c)
{
	return (!ft_strchr(" \t$=|><;$\"'", c));
}

char	lexer_peek(t_lexer *self, int index)
{
	if (self->cursor + index >= self->length)
		return ('\0');
	return (self->input[self->cursor + index]);
}

t_token	*lexer_until(t_lexer *self, t_token_kind kind, t_check check)
{
	int		length;
	char	peek;
	int		start;
	char	*result;

	length = 1;
	start = self->cursor;
	peek = lexer_peek(self, length);
	while (peek != '\0' && check(peek))
		peek = lexer_peek(self, ++length);
	result = ft_substr(self->input, start, length);
	return (token_create(kind, result));
}
