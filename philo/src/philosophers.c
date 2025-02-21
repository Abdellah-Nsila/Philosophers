/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/21 15:27:32 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//*Usage:    ./philo philo_num time_die time_eat time_sleep <eat_repeat>
//*Example:  ./philo 5         800      200      200        <20>    (Last arg optional)
//TODO 1: Parsing 4 or 5 arg all is numbers 
//TODO 2: Create the main struct for shared data, and one for each philo 
//TODO 3: Init the struct and validate the args after fiiling all data we need
//TODO 4: 

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
		else if (i == 0 && ft_atoi(arr[i]) > 200)
			return (false);
		else if (i == 4 && ft_atoi(arr[i]) < 0)
			return (false);
		else if (i != 0 && i != 4 && ft_atoi(arr[i]) <= 0)
			return (false);
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	if (ft_validate_arg((av + 1), ac - 1))
		printf("%sValide args\n%s", GRN, RESET);
	else
		printf("%sError\n%s", RED, RESET);
}
