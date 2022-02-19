/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:26:55 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/19 19:29:14 by aabajyan         ###   ########.fr       */
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
void	*ft_memcpy(void *dest, const void *src, size_t num);
void	*ft_calloc(size_t el_num, size_t el_size);
void	*ft_realloc(void *ptr, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
int		ft_strcmp(const char *str1, const char *str2);
void	*ft_calloc(size_t el_num, size_t el_size);
void	*ft_memset(void *buffer, int c, size_t size);

#endif // MINISHELL_H