/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:42:58 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/05 10:34:46 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parser_obtain_heredoc(t_parser *self)
{
	t_string	heredoc;
	char		*input;
	char		*string;

	string = parser_get_identifer(self);
	if (!string)
		return (NULL);
	string_init(&heredoc);
	while (true)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, string) == 0)
		{
			if (input)
				free(input);
			else
				printf("\n");
			break ;
		}
		string_move(&heredoc, input);
		string_push(&heredoc, "\n");
	}
	free(string);
	return (string_freeze(&heredoc));
}

static bool	parser_write_to_tmp(t_node *result)
{
	int		fd;
	char	*expanded;

	fd = open(SHELL_TMP, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (false);
	expanded = expander_word(result);
	if (!expanded)
	{
		close(fd);
		return (false);
	}
	write(fd, expanded, ft_strlen(expanded));
	close(fd);
	free(expanded);
	node_destroy(result);
	return (true);
}

static void	parser_create_tmp(t_node *command)
{
	command->redirect_kind = R_LEFT;
	command->target = node_create(NODE_WORD);
	if (!command->target)
		return ;
	command->target->value = ft_strdup(SHELL_TMP);
}

t_node	*parser_heredoc(t_parser *self)
{
	t_node		*command;
	t_token		*tokens;
	t_lexer		lexer;
	t_parser	parser;
	char		*heredoc;

	command = parser_redirection(self);
	if (command && parser_match(self, T_DOUBLE_LESS))
	{
		heredoc = parser_obtain_heredoc(self);
		if (!heredoc)
		{
			node_destroy(command);
			return (NULL);
		}
		lexer.heredoc = true;
		tokens = lexer_lex(&lexer, heredoc);
		parser_init(&parser, tokens->next);
		parser.heredoc = true;
		parser_write_to_tmp(parser_simple_word(&parser));
		parser_create_tmp(command);
		token_destroy(tokens);
		free(heredoc);
	}
	return (command);
}

void	parser_init(t_parser *self, t_token *tokens)
{
	self->tokens = tokens;
	self->current = tokens;
	self->error = false;
	self->in_quote = false;
	self->heredoc = false;
	self->index = 0;
}
