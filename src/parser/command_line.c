/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:45:09 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/23 19:11:29 by aabajyan         ###   ########.fr       */
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

	command = parser_redirection(self);
	if (!command)
		return (NULL);
	if (parser_match(self, T_VERTICAL_BAR))
		command->pipe = parser_command_line(self);
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
	if (parser_match(self, T_SEMICOLON))
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
	int		check_enum;

	check_enum = T_LESS | T_GREAT | T_DOUBLE_LESS | T_DOUBLE_GREAT;
	command = parser_simple_command(self);
	check = parser_match(self, check_enum);
	if (check)
	{
		command->redirect_kind = token_kind_to_redirect_kind(check->kind);
		command->target = parser_word(self);
		if (!parser_match2(self, T_EOF))
			command->next = parser_command_line(self);
	}
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
	temp = parser_word(self);
	while (temp)
	{
		arguments = node_push(arguments, temp);
		temp = parser_word(self);
	}
	if (arguments == NULL)
		return (NULL);
	result = node_create(NODE_COMMAND);
	result->arguments = arguments;
	return (result);
}
