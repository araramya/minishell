/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:26:55 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/19 20:29:16 by aabajyan         ###   ########.fr       */
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
	T_EOF = 1 << 1
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

#endif // MINISHELL_H