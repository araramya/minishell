/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:58:30 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/02 16:59:20 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_itoa(int n)
{
	char			buffer[sizeof(int) * CHAR_BIT / 3 + 3];
	char			*str;
	unsigned int	i;

	str = buffer + sizeof(buffer);
	i = (unsigned)n;
	if (n < 0)
		i = -i;
	*--str = '\0';
	while (i > 9)
	{
		*--str = (i % 10) + '0';
		i /= 10;
	}
	*--str = i + '0';
	if (n < 0)
		*--str = '-';
	return (ft_strdup(str));
}
