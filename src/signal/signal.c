/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:19:12 by araramya          #+#    #+#             */
/*   Updated: 2022/03/07 13:16:46 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Default signals for shell
 * 
 */
void	signal_shell(void)
{
	signal(SIGINT, signal_reprompt);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Revert back to default handlers
 * 
 */
void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief Ignore signals
 * 
 */
void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Signals for heredoc
 * 
 */
void	signal_heredoc(void)
{
	signal(SIGINT, signal_interupt);
	signal(SIGQUIT, signal_do_nothing);
}
