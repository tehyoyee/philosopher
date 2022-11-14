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

#include "philo_bonus.h"

int	exit_error(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	return (-1);
}

void	show_status(t_rule *rule, char *str, int id)
{
	printf("%lld %d %s\n", get_time() - rule->start_time, id + 1, str);
}

void	destroy_sem()
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_eat_cnt");
	sem_unlink("/sem_time");
	sem_unlink("/sem_person");
	sem_unlink("/sem_done");
}

void	destroy_process(t_rule *rule)
{
	int	i;

	i = 0;
	printf("destroy process\n");
	while (i < rule->num_philo)
	{
		kill(rule->pids[i], SIGKILL);
		i++;
	}
}