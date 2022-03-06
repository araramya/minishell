/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:42:58 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/06 13:46:45 by aabajyan         ###   ########.fr       */
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

static bool	parser_write_to_tmp(t_node *result, char *tmpfile)
{
	int		fd;
	char	*expanded;

	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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

static t_node	*parser_heredoc_node(char *heredoc)
{
	t_lexer		lexer;
	t_parser	parser;
	t_token		*tokens;
	t_node		*nodes;

	lexer_init(&lexer, heredoc, true);
	tokens = lexer_lex(&lexer);
	parser_init(&parser, tokens->next);
	parser.heredoc = true;
	nodes = parser_simple_word(&parser);
	token_destroy(tokens);
	return (nodes);
}

t_node	*parser_heredoc(t_parser *self)
{
	char	*heredoc;
	char	*tmpfile;
	t_node	*result;

	heredoc = parser_obtain_heredoc(self);
	if (!heredoc)
		return (NULL);
	tmpfile = utils_get_tmp_path();
	if (!tmpfile)
	{
		free(heredoc);
		return (NULL);
	}
	result = node_create(NODE_REDIRECTION);
	result->redirect_kind = R_LEFT;
	result->rhs = node_create_value(NODE_WORD, tmpfile);
	parser_write_to_tmp(parser_heredoc_node(heredoc), tmpfile);
	free(tmpfile);
	free(heredoc);
	return (result);
}
