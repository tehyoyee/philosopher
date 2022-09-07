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
	pthread_mutex_lock(&rule->eat_cnt_mutex);
	pthread_mutex_lock(&rule->death_mutex);
	if (!rule->death && !rule->eat_full)
		printf("%lld %d %s\n", get_time() - rule->start_time, id + 1, str);
	pthread_mutex_unlock(&rule->death_mutex);
	pthread_mutex_unlock(&rule->eat_cnt_mutex);
}

void	ft_free_mutex(t_rule *rule)
{
	free(rule->fork);
	free(rule->person_mutex);
}
