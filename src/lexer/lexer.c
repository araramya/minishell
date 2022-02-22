/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:26:19 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/22 18:57:34 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Lex single quotes.
 * 
 * @param self 
 * @return t_token* 
 */
t_token	*lexer_single_quote(t_lexer *self)
{
	int		start;
	int		length;
	char	*result;
	char	peek;

	if (self->in_quotes)
		return (token_create(T_WORD, ft_strdup("'")));
	start = ++self->cursor;
	length = 0;
	peek = lexer_peek(self, length);
	while (peek != '\0' && peek != '\'')
		peek = lexer_peek(self, ++length);
	self->cursor++;
	if (peek != '\'')
	{
		printf(LEXER_ERROR_UNTERIMATED_STRING);
		self->error = true;
		return (NULL);
	}
	result = ft_substr(self->input, start, length);
	return (token_create(T_WORD, result));
}

/**
 * @brief Lex single charecters.
 * 
 * @param self 
 * @param peek 
 * @return t_token* 
 */
static t_token	*lexer_single(t_lexer *self, char peek)
{
	if (peek == '$')
		return (token_create(T_DOLLAR_SIGN, ft_strdup("$")));
	if (peek == '|')
		return (token_create(T_VERTICAL_BAR, ft_strdup("|")));
	if (peek == ';')
		return (token_create(T_SEMICOLON, ft_strdup(";")));
	if (peek == '=')
		return (token_create(T_EQUALS, ft_strdup("=")));
	if (peek == '>')
	{
		if (lexer_peek(self, 1) == '>')
			return (token_create(T_DOUBLE_GREAT, ft_strdup(">>")));
		return (token_create(T_GREAT, ft_strdup(">")));
	}
	if (peek == '<')
	{
		if (lexer_peek(self, 1) == '<')
			return (token_create(T_DOUBLE_LESS, ft_strdup("<<")));
		return (token_create(T_LESS, ft_strdup("<")));
	}
	return (NULL);
}

/**
 * @brief Lexes one token from input.
 * 
 * @param self 
 * @return t_token* 
 */
t_token	*lexer_next(t_lexer *self)
{
	char	peek;
	t_token	*temp;

	peek = lexer_peek(self, 0);
	if (peek == '\0')
		return (NULL);
	temp = lexer_single(self, peek);
	if (temp)
		return (temp);
	if (peek == '"')
	{
		self->in_quotes = !self->in_quotes;
		return (token_create(T_DOUBLE_QUOTE, ft_strdup("\"")));
	}
	if (peek == '\'')
		return (lexer_single_quote(self));
	if (lexer_is_space(peek))
		return (lexer_until(self, T_WHITESPACE, lexer_is_space));
	return (lexer_until(self, T_WORD, lexer_is_word));
}

/**
 * @brief Lexes input string into tokens.
 * 
 * @param self 
 * @param input 
 * @return t_token* 
 */
t_token	*lexer_lex(t_lexer *self, const char *input)
{
	t_token	*next;

	if (!input)
		return (NULL);
	self->cursor = 0;
	self->error = false;
	self->in_quotes = false;
	self->input = input;
	self->length = ft_strlen(input);
	self->tokens = token_create(T_BEGIN, NULL);
	next = lexer_next(self);
	while (next && self->error == false)
	{
		self->cursor += ft_strlen(next->slice);
		token_push(self->tokens, next);
		next = lexer_next(self);
	}
	if (self->in_quotes)
	{
		printf(LEXER_ERROR_UNTERIMATED_STRING);
		self->error = true;
	}
	token_push(self->tokens, token_create(T_EOF, NULL));
	return (self->tokens);
}
