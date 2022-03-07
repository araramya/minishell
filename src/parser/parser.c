/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:15:18 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/07 15:58:51 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parses list of tokens into a Node Tree
 * 
 * @param self 
 * @param tokens 
 * @return t_node* 
 */
t_node	*parser_parse(t_parser *self, t_token *tokens)
{
	parser_init(self, tokens);
	if (!parser_consume(self, T_BEGIN))
		return (NULL);
	return (parser_command_line(self));
}

/**
 * @brief Advances to the next token if there's one
 * 
 * @param self 
 * @return t_token* 
 */
t_token	*parser_advance(t_parser *self)
{
	t_token	*temp;

	temp = self->current;
	if (self->current->kind != T_EOF)
	{
		self->current = self->current->next;
		self->index++;
	}
	return (temp);
}

/**
 * @brief Check if the current token is specific kind
 * 
 * @param self 
 * @param kind 
 * @return t_token* 
 */
t_token	*parser_check(t_parser *self, t_token_kind kind)
{
	if ((self->current->kind & kind) != 0)
		return (self->current);
	return (NULL);
}

/**
 * @brief Check if the current token is specific kind.
 * If so advance to the next token.
 * 
 * @param self 
 * @param kind 
 * @return t_token* 
 */
t_token	*parser_match(t_parser *self, t_token_kind kind)
{
	if (parser_check(self, kind))
		return (parser_advance(self));
	return (NULL);
}

/**
 * @brief Check if the current token is specific kind.
 * If so advance to the next token. Or else throw an error.
 * 
 * @param self 
 * @param kind 
 * @return t_token* 
 */
t_token	*parser_consume(t_parser *self, t_token_kind kind)
{
	if (self->error)
		return (NULL);
	if (parser_check(self, kind) != NULL)
		return (parser_advance(self));
	ft_putstr_fd("Parser error: Expected ", 2);
	ft_putstr_fd(token_kind_to_string(kind), 2);
	ft_putstr_fd(", but got ", 2);
	ft_putstr_fd(token_kind_to_string(self->current->kind), 2);
	ft_putstr_fd(".\n", 2);
	self->error = true;
	return (NULL);
}
