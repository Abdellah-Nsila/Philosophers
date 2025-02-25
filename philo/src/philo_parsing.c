/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:44:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/25 17:17:29 by abnsila          ###   ########.fr       */
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
	int	i;

	if (size < 4)
		return (false);
	i = 0;
	while (i < size)
	{
		if (!ft_is_valid_number(arr[i]))
			return (false);
		else if (i == 0 && ft_atol(arr[i]) > 200)
			return (false);
		else if (i == 4 && ft_atol(arr[i]) < 0)
			return (false);
		else if (i != 0 && i != 4 && ft_atol(arr[i]) <= 0)
			return (false);
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
