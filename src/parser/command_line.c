/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:45:09 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/06 14:13:21 by aabajyan         ###   ########.fr       */
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

	command = parser_redirection(self);
	if (!command)
		return (NULL);
	while (parser_match2(self, T_VERTICAL_BAR))
	{
		temp = command;
		command = node_create(NODE_PIPE);
		command->lhs = temp;
		command->rhs = parser_command_line(self);
	}
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
t_node	*parser_redirection(t_parser *self)
{
	t_node	*command;
	t_token	*check;
	t_node	*temp;

	command = parser_simple_command(self);
	check = parser_match2(self, T_LESS | T_GREAT | T_DOUBLE_GREAT);
	while (check)
	{
		temp = command;
		if ((command->kind & NODE_REDIRECTION) != 0)
		{
			if (command->rhs)
				node_destroy(command->rhs);
		}
		else
		{
			command = node_create(NODE_REDIRECTION);
			command->lhs = temp;
		}
		command->rhs = parser_word(self);
		command->redirect_kind = token_kind_to_redirect_kind(check->kind);
		check = parser_match2(self, T_LESS | T_GREAT | T_DOUBLE_GREAT);
	}
	return (command);
}

static t_node	*parser_simple_command_return(t_node *heredoc, t_node *result)
{
	if (heredoc)
	{
		heredoc->lhs = result;
		return (heredoc);
	}
	return (result);
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
		{
			if (heredoc)
				node_destroy(heredoc);
			heredoc = temp;
		}
		else
			arguments = node_push(arguments, temp);
		temp = parser_word(self);
	}
	if (arguments == NULL)
		return (NULL);
	result = node_create(NODE_COMMAND);
	result->arguments = arguments;
	return (parser_simple_command_return(heredoc, result));
}
