/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_kind_to_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:57:15 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/19 19:58:23 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*token_kind_to_string(t_token_kind kind)
{
	if (kind == T_BEGIN)
		return ("T_BEGIN");
	if (kind == T_EOF)
		return ("T_EOF");
	return ("T_UNKNOWN");
}
