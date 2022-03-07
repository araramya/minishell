/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:45:09 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/07 21:00:58 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parse a command pipe
 * 
 * pipe -> redirection | command_line
 * 
 * @param self 
 * @return t_node* 
 */
t_node	*parser_pipe(t_parser *self)
{
	t_node	*command;
	t_node	*temp;

	command = parser_simple_command(self);
	if (!command)
		return (NULL);
	while (parser_match2(self, T_VERTICAL_BAR))
	{
		temp = command;
		command = node_create(NODE_PIPE);
		command->lhs = temp;
		command->rhs = parser_command_line(self);
	}
	if ((command->kind & NODE_PIPE) != 0 && !command->rhs)
		return (parser_error(self, "command expected", command));
	return (command);
}

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

	command = parser_pipe(self);
	if (!command)
		return (NULL);
	if (parser_match2(self, T_SEMICOLON) != NULL)
		command->next = parser_command_line(self);
	return (command);
}

/**
 * @brief Parse a redirection
 * 
 * redirection -> simple_command [< | > | << | >>] word command_line?
 * 
 * @param self 
 * @return t_node* 
 */
t_node	*parser_redirection(t_parser *self, t_token_kind kind)
{
	t_node	*result;
	int		check;

	check = T_EOF | T_LESS | T_DOUBLE_LESS | T_GREAT | T_DOUBLE_GREAT;
	if (parser_check2(self, check))
		return (parser_error(self, "Unexpected token", NULL));
	result = node_create(NODE_REDIRECTION);
	result->redirect_kind = token_kind_to_redirect_kind(kind);
	result->rhs = parser_word(self);
	return (result);
}

static t_node	*node_push_to_lhs(t_node *self, t_node *src)
{
	t_node	*target;

	if (!self)
		return (src);
	target = self;
	while (target && target->lhs)
		target = target->lhs;
	target->lhs = src;
	return (self);
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
	t_node	*heredoc;

	arguments = NULL;
	heredoc = NULL;
	temp = parser_word(self);
	while (temp)
	{
		if ((temp->kind & NODE_REDIRECTION) != 0)
			heredoc = node_push_to_lhs(heredoc, temp);
		else
			arguments = node_push(arguments, temp);
		temp = parser_word(self);
	}
	if (arguments == NULL)
		return (NULL);
	result = node_create(NODE_COMMAND);
	result->arguments = arguments;
	if (heredoc)
		return (node_push_to_lhs(heredoc, result));
	return (result);
}
