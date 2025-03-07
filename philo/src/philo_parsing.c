/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:44:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/03 13:22:33 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

#define USAGE_MSG "%sphilo: Usage: \
./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n%s"
#define INPUT_ERROR "%sphilo: Invalid input: %s: \
Value must be a positive integer.\n%s"
#define ARG_ERROR "%sphilo: Invalid input: %s: \
Value must be between 0 and 2147483647.\n%s"
#define PHILO_ERROR "%sphilo: Invalid input: %s: \
there must be between 1 and %d philosophers.\n%s"

t_bool	ft_is_valid_number(char *str)
{
	if (!ft_isnumber(str))
		return (false);
	return (true);
}

t_bool	ft_validate_arg(char **arr, int size)
{
	int		i;
	long	num;

	if (size < 4 || size > 5)
		return (printf(USAGE_MSG, YEL, RESET), false);
	i = 0;
	while (i < size)
	{
		if (!ft_is_valid_number(arr[i]))
			return (printf(INPUT_ERROR, RED, arr[i], RESET), false);
		num = ft_atol(arr[i]);
		if (num < 0 || num > INT_MAX)
			return (printf(ARG_ERROR, RED, arr[i], RESET), false);
		if (i == 0 && (num == 0 || num > 200))
			return (printf(PHILO_ERROR, RED, arr[i], PHILO_MAX, RESET), false);
		i++;
	}
	return (true);
}

t_bool	ft_check_parse(int ac, char **av)
{
	if (ft_validate_arg((av + 1), ac - 1))
		return (true);
	return (false);
}
