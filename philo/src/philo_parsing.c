/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:44:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/26 11:50:02 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//*Usage:    ./philo philo_num time_die time_eat time_sleep <eat_repeat>
//*Example:  ./philo 5         800      200      200        <20>    (Last arg optional)

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

	if (size < 4)
	{
		printf("%sphilo: Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]%s\n", YEL, RESET);
		return (false);
	}
	i = 0;
	while (i < size)
	{
		if (!ft_is_valid_number(arr[i]))
			return (false);
		num = ft_atol(arr[i]);
		if (num < 0 || num > INT_MAX)
		{
			printf("%sphilo: Invalid input: %s: Value must be between 0 and 2147483647.\n%s",RED, arr[i], RESET);
			return (false);
		}
		if (i == 0 && (num == 0 || num > 200))
		{
			printf("%sphilo: invalid input: %s: there must be between 1 and %d philosophers.\n%s",RED, arr[i], PHILO_MAX, RESET);
			return (false);
		}
		i++;
	}
	return (true);
}

t_bool	ft_check_parse(int ac, char **av)
{
	if (ft_validate_arg((av + 1), ac - 1))
	{	
		printf("%sValide args\n%s", GRN, RESET);
		return (true);
	}
	printf("%sError\n%s", RED, RESET);
	return (false);
}
