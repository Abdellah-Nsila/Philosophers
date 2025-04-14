/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:44:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 15:41:28 by abnsila          ###   ########.fr       */
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
		return (printf(USAGE_MSG), false);
	i = 0;
	while (i < size)
	{
		if (!ft_is_valid_number(arr[i]))
			return (printf(INPUT_ERROR, arr[i]), false);
		num = ft_atol(arr[i]);
		if (i == 0 && num <= 0)
			return (printf(PHILO_ERROR, arr[i]), false);
		else if (i == 4 && num < 0)
			return (printf(APT_ERROR, arr[i]), false);
		else if (i != 0 && i != 4 && (num <= 0 || num > INT_MAX))
			return (printf(TIME_ERROR, arr[i]), false);
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
