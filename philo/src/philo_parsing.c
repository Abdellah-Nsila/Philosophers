/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:44:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 11:39:51 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		if (num <= 0 || num > INT_MAX)
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
