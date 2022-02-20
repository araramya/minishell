/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:26:55 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/20 18:33:56 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// LIBFT
void				*ft_memcpy(void *dest, const void *src, size_t num);
void				*ft_calloc(size_t el_num, size_t el_size);
void				*ft_realloc(void *ptr, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s);
int					ft_strcmp(const char *str1, const char *str2);
void				*ft_calloc(size_t el_num, size_t el_size);
void				*ft_memset(void *buffer, int c, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strchr(const char *str, int c);

// STRING
typedef struct s_string
{
	char			*buffer;
	size_t			size;
	size_t			capacity;
}					t_string;

void				string_init(t_string *self);
int					string_push(t_string *self, const char *src);
int					string_deinit(t_string *self);

// TOKEN
typedef enum e_token_kind
{
	T_BEGIN = 1 << 0,
	T_QUOTE = 1 << 1,
	T_DOUBLE_QUOTE = 1 << 2,
	T_WHITESPACE = 1 << 3,
	T_WORD = 1 << 4,
	T_DOLLAR_SIGN = 1 << 5,
	T_LESS = 1 << 6,
	T_GREAT = 1 << 7,
	T_DOUBLE_LESS = 1 << 8,
	T_DOUBLE_GREAT = 1 << 9,
	T_VERTICAL_BAR = 1 << 10,
	T_SEMICOLON = 1 << 11,
	T_QUESTION_MARK = 1 << 12,
	T_EQUALS = 1 << 13,
	T_EOF = 1 << 14
}					t_token_kind;

const char			*token_kind_to_string(t_token_kind kind);

typedef struct s_token
{
	t_token_kind	kind;
	char			*slice;
	struct s_token	*next;
}					t_token;

t_token				*token_create(t_token_kind kind, char *slice);
t_token				*token_last(t_token *self);
t_token				*token_push(t_token *self, t_token *src);
t_token				*token_size(t_token *self);
void				token_destroy(t_token *self);
void				token_print(t_token *self);

// LEXER
# define LEXER_ERROR_UNTERIMATED_STRING "Lexer Error: Unterminated string\n"

typedef struct s_lexer
{
	t_token			*tokens;
	const char		*input;
	bool			in_quotes;
	bool			error;
	size_t			cursor;
	size_t			length;
}					t_lexer;

typedef int			(*t_check)(int);

t_token				*lexer_lex(t_lexer *self, const char *input);
t_token				*lexer_next(t_lexer *self);
char				lexer_peek(t_lexer *self, int index);
t_token				*lexer_single_quote(t_lexer *self);
t_token				*lexer_until(t_lexer *self, t_token_kind kind, t_check c);
int					lexer_is_space(int c);
int					lexer_is_word(int c);

// SHELL
typedef struct s_shell
{
	int				code;
	t_lexer			lexer;
}					t_shell;

int					shell_start(t_shell *self);

#endif // MINISHELL_H