/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:29:45 by taehykim          #+#    #+#             */
/*   Updated: 2022/11/14 16:11:36 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	get_answer(const char *str, int sign)
{
	unsigned long long	result;
	int					arr_len;

	result = 0;
	arr_len = 0;
	while ('0' <= *str && *str <= '9')
	{
		arr_len++;
		result = result * 10 + *str - 48;
		if ((result > 2147483647) && sign == 1)
			return (-1);
		if ((result > 2147483648) && sign == -1)
			return (-1);
		str++;
	}
	return (sign * (int)result);
}

int	ft_atoi(const char *str)
{
	int	sign;

	sign = 1;
	if (*str == '\0')
		return (-1);
	while (*str == 32 || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str == '0')
		str++;
	if ('0' > *str || *str > '9')
		return (0);
	return (get_answer(str, sign));
}
