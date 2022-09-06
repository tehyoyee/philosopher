/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:23 by taehykim          #+#    #+#             */
/*   Updated: 2022/09/06 16:30:26 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_error(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	return (-1);
}

void	show_status(t_rule *rule, char *str, int id)
{
	pthread_mutex_lock(&rule->show_status);
	if (!rule->death && !rule->eat_full)
		printf("%lld %d %s\n", get_time() - rule->start_time, id + 1, str);
	pthread_mutex_unlock(&rule->show_status);
}
