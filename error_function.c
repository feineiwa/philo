/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:51:57 by frahenin          #+#    #+#             */
/*   Updated: 2024/11/14 13:24:53 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(char *str)
{
	printf("%s\n", str);
	return (ERROR_FAILURE);
}

int	print_error(t_data *data)
{
	if (data->philo_nbr == -2 || data->time_to_die == -2000
		|| data->time_to_eat == -2000 || data->time_to_sleep == -2000
		|| data->total_meals == -2)
		return (error_exit("Error\nThere is no Argument"));
	if (data->philo_nbr == -3 || data->time_to_die == -3000
		|| data->time_to_eat == -3000 || data->time_to_sleep == -3000
		|| data->total_meals == -3)
		return (error_exit("Error\nArgument should be positive number"));
	if (data->philo_nbr == -4 || data->time_to_die == -4000
		|| data->time_to_eat == -4000 || data->time_to_sleep == -4000
		|| data->total_meals == -4)
		return (error_exit("Error\nInvalid Argument"));
	if (data->philo_nbr == -5 || data->time_to_die == -5000
		|| data->time_to_eat == -5000 || data->time_to_sleep == -5000
		|| data->total_meals == -5)
		return (error_exit("Error\nThe number is exceeded the int limit max"));
	if (data->time_to_die < 60000 || data->time_to_eat < 60000
		|| data->time_to_sleep < 60000)
		return (error_exit("the minumum of time is 60"));
	if (!data->philo_nbr || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_sleep)
		return (error_exit("Error\nThe number should not be 0"));
	return (0);
}
