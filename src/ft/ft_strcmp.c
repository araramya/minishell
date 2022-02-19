/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:31:05 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/19 19:31:22 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	if (str1 == NULL)
		return (1);
	while (*str1)
		if (*str1++ != *str2++)
			break ;
	return (*(const unsigned char *)str1 - *(const unsigned char *)str2);
}
