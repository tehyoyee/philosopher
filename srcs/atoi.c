#include "philo.h"

static int	num_len(unsigned long result)
{
	int	num_len;

	num_len = 0;
	while (result > 0)
	{
		num_len++;
		result /= 10;
	}
	return (num_len);
}

static int	get_answer(const char *str, int sign)
{
	unsigned long	result;
	int				arr_len;

	result = 0;
	arr_len = 0;
	while ('0' <= *str && *str <= '9')
	{
		arr_len++;
		result = result * 10 + *str - 48;
		if ((result > 9223372036854775807) && sign == 1)
			return (-1);
		if (num_len(result) != arr_len && sign == 1)
			return (-1);
		if (num_len(result) != arr_len && sign == 1)
			return (0);
		if ((result > 9223372036854775807 + 1UL) && sign == -1)
			return (0);
		str++;
	}
	return (sign * (int)result);
}

int	ft_atoi(const char *str)
{
	int	sign;

	sign = 1;
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