/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:26:55 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/02 16:22:10 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
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
long				ft_atoi(const char *str);

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
char				*string_freeze(t_string *self);

// TOKEN
typedef enum e_token_kind
{
	T_BEGIN = 1 << 0,
	T_DOUBLE_QUOTE = 1 << 1,
	T_WHITESPACE = 1 << 2,
	T_WORD = 1 << 3,
	T_DOLLAR_SIGN = 1 << 4,
	T_LESS = 1 << 5,
	T_GREAT = 1 << 6,
	T_DOUBLE_LESS = 1 << 7,
	T_DOUBLE_GREAT = 1 << 8,
	T_VERTICAL_BAR = 1 << 9,
	T_SEMICOLON = 1 << 10,
	T_EOF = 1 << 12
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
	bool			dollar_sign;
	bool			error;
	size_t			cursor;
	size_t			length;
}					t_lexer;

typedef int			(*t_check)(int);

t_token				*lexer_lex(t_lexer *self, const char *input);
t_token				*lexer_next(t_lexer *self);
char				lexer_peek(t_lexer *self, int index);
t_token				*lexer_single_quote(t_lexer *self);
t_token				*lexer_symbols(t_lexer *self, char peek);
t_token				*lexer_until(t_lexer *self, t_token_kind kind, t_check c);
int					lexer_is_space(int c);
int					lexer_is_word(int c);
int					lexer_is_alnum(int c);

// NODE
typedef enum e_node_kind
{
	NODE_COMMAND = 1 << 0,
	NODE_WORD = 1 << 1,
	NODE_VARIABLE = 1 << 2,
	NODE_QUOTED = 1 << 3,
}					t_node_kind;

const char			*node_kind_to_string(t_node_kind kind);

typedef enum e_redirect_kind
{
	R_NONE = 1 << 0,
	R_LEFT = 1 << 1,
	R_RIGHT = 1 << 2,
	R_DOUBLE_LEFT = 1 << 3,
	R_DOUBLE_RIGHT = 1 << 4
}					t_redirect_kind;

t_redirect_kind		token_kind_to_redirect_kind(t_token_kind kind);
const char			*redirect_kind_to_string(t_redirect_kind kind);

typedef struct s_node
{
	t_node_kind		kind;
	t_redirect_kind	redirect_kind;
	struct s_node	*lhs;
	struct s_node	*rhs;
	struct s_node	*next;
	struct s_node	*arguments;
	struct s_node	*target;
	struct s_node	*pipe;
	struct s_node	*in_quote;
	struct s_node	*merged;
	char			*value;
}					t_node;

t_node				*node_create(t_node_kind kind);
t_node				*node_last(t_node *self);
t_node				*node_push(t_node *self, t_node *src);
void				node_print(t_node *self, int indent);
void				node_destroy(t_node *self);
size_t				node_size(t_node *self);

void				node_print_indent(int indent);
void				node_print_children(t_node *node, char *name, int indent);
void				node_print_value(char *name, char *value, int indent);
// PASER
typedef struct s_parser
{
	bool			error;
	t_token			*tokens;
	t_token			*current;
	int				index;
}					t_parser;

t_node				*parser_parse(t_parser *self, t_token *tokens);
t_token				*parser_advance(t_parser *self);
t_token				*parser_check(t_parser *self, t_token_kind kind);
t_token				*parser_match(t_parser *self, t_token_kind kind);
t_token				*parser_match2(t_parser *self, t_token_kind kind);
t_token				*parser_consume(t_parser *self, t_token_kind kind);
t_node				*parser_command_line(t_parser *self);
t_node				*parser_redirection(t_parser *self);
t_node				*parser_pipe(t_parser *self);
t_node				*parser_quoted(t_parser *self);
t_node				*parser_simple_command(t_parser *self);
t_node				*parser_word(t_parser *self);
t_node				*parser_simple_word(t_parser *self);

// ENV
# define TABLE_SIZE 1000

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

void				env_init(void);
void				env_set(char *key, char *value);
void				env_unset(t_env ***env, char *key);
char				*env_get(char *key);
void				env_deinit(void);
void				env_destroy(t_env *env);
t_env				*env_pair(char *key, char *value);
size_t				env_hash(char *key);
void				env_print(const char *prefix);

// SHELL
typedef struct s_shell
{
	int				code;
	t_lexer			lexer;
	t_parser		parser;
}					t_shell;

int					shell_execute(t_shell *self, char *input);
int					shell_start(t_shell *self);

// INTEPRETER
char				**expander_eval(t_node *node);
char				*expander_quoted(t_node *node);
char				*expander_node(t_node *node);

// ARGUMENTS
void				argument_print(char **arguments);
void				argument_destroy(char **arguments);
int					argument_size(char **arguments);

// BUILTIN
int					builtin_unset(int argc, char **argv);
int					builtin_export(int argc, char **argv);
int					buildin_echo(int argc, char **argv);
int					buildin_cd(int argc, char **argv);
int					buildin_exit(int argc, char **argv);
int					builtin_env(void);
int					buildin_pwd(void);

#endif // MINISHELL_H77