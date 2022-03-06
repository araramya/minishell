/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:42:58 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/06 18:19:32 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parser_obtain_heredoc(char *identifer)
{
	t_string	heredoc;
	char		*input;

	string_init(&heredoc);
	signal_heredoc();
	while (true)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, identifer) == 0)
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

static void	parser_handle_heredoc(t_parser *self, char *tmpfile)
{
	char	*heredoc;
	char	*identifer;

	identifer = parser_get_identifer(self);
	if (!identifer)
		return ;
	if (fork() == 0)
	{
		heredoc = parser_obtain_heredoc(identifer);
		if (!heredoc)
			exit(1);
		parser_write_to_tmp(parser_heredoc_node(heredoc), tmpfile);
		free(identifer);
		exit(0);
	}
	wait(&self->heredoc_exit);
	free(identifer);
}

t_node	*parser_heredoc(t_parser *self)
{
	char	*tmpfile;
	t_node	*result;

	tmpfile = utils_get_tmp_path();
	parser_handle_heredoc(self, tmpfile);
	if (!tmpfile)
		return (NULL);
	result = node_create(NODE_REDIRECTION);
	result->redirect_kind = R_LEFT;
	result->rhs = node_create_value(NODE_WORD, tmpfile);
	free(tmpfile);
	return (result);
}
