/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:45:09 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/22 19:28:12 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parse a command line
 * 
 * command_line -> simple_command
 * 
 * @param self 
 * @return t_node* 
 */
t_node	*parser_command_line(t_parser *self)
{
	t_node	*command;
	t_token	*t;

	command = parser_simple_command(self);
	if (!command)
		return (NULL);
	t = parser_match(self, T_LESS | T_GREAT | T_DOUBLE_LESS | T_DOUBLE_GREAT);
	if (t)
	{
		while (parser_check(self, T_WHITESPACE))
			parser_advance(self);
		command->redirect_kind = token_kind_to_redirect_kind(t->kind);
		command->target = parser_word(self);
	}
	if (parser_match(self, T_VERTICAL_BAR))
	{
		command->pipe = parser_command_line(self);
		if (!command->pipe)
		{
			node_destroy(command);
			return (NULL);
		}
	}
	if (parser_match(self, T_SEMICOLON))
		command->next = parser_command_line(self);
	return (command);
}

/**
 * @brief Parse a simple command
 * 
 * simple_command -> word+
 * 
 * @param self 
 * @return t_node* 
 */
t_node	*parser_simple_command(t_parser *self)
{
	t_node	*arguments;
	t_node	*result;
	t_node	*temp;

	arguments = NULL;
	while (parser_check(self, T_WHITESPACE))
		parser_advance(self);
	temp = parser_word(self);
	while (temp)
	{
		arguments = node_push(arguments, temp);
		while (parser_check(self, T_WHITESPACE))
			parser_advance(self);
		temp = parser_word(self);
	}
	if (arguments == NULL)
		return (NULL);
	result = node_create(NODE_COMMAND);
	result->arguments = arguments;
	return (result);
}

/**
 * @brief Parse a quoted string
 * 
 * quoted -> T_DOUBLE_QUOTE simple_word+ T_DOUBLE_QUOTE
 * 
 * @param self 
 * @return t_node* 
 */
t_node	*parser_quoted(t_parser *self)
{
	t_node	*in_quote;
	t_node	*result;

	in_quote = NULL;
	while (!parser_match(self, T_DOUBLE_QUOTE | T_EOF))
		in_quote = node_push(in_quote, parser_simple_word(self));
	result = node_create(NODE_QUOTED);
	if (!result)
	{
		node_destroy(in_quote);
		return (NULL);
	}
	result->in_quote = in_quote;
	return (result);
}

/**
 * @brief Parse a simple word
 * 
 * simple_word -> T_DOLLAR_SIGN? T_WORD | T_WHITESPACE
 * 
 * @param self 
 * @return t_node* 
 */
t_node	*parser_simple_word(t_parser *self)
{
	bool	is_env;
	t_token	*word;
	t_node	*result;

	is_env = (parser_match(self, T_DOLLAR_SIGN) != NULL);
	word = parser_match(self, T_EOF | T_WORD | T_WHITESPACE);
	if (!word || word->kind == T_EOF)
		return (NULL);
	if (is_env)
		result = node_create(NODE_VARIABLE);
	else
		result = node_create(NODE_WORD);
	result->value = ft_strdup(word->slice);
	return (result);
}

/**
 * @brief Parse a word
 * 
 * word -> simple_word | quoted
 * 
 * @param self 
 * @return t_node* 
 */
t_node	*parser_word(t_parser *self)
{
	if (parser_match(self, T_DOUBLE_QUOTE))
		return (parser_quoted(self));
	return (parser_simple_word(self));
}
