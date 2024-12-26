/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:51:57 by frahenin          #+#    #+#             */
/*   Updated: 2024/12/26 14:02:54 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_exit(char *str)
{
	printf("%s\n", str);
	return (ERROR_FAILURE);
}

int	print_error(t_data *data)
{
	if (data->philo_nbr == -2 || data->time_to_die == -2 || data->time_to_eat
		== -2 || data->time_to_sleep == -2 || data->total_meals == -2)
		return (error_exit("Error\nMissing argument(s).\
 Please provide all required inputs."));
	if (data->philo_nbr == -3 || data->time_to_die == -3 || data->time_to_eat
		== -3 || data->time_to_sleep == -3 || data->total_meals == -3)
		return (error_exit("Error\nArguments must be positive numbers."));
	if (data->philo_nbr == -4 || data->time_to_die == -4 || data->time_to_eat
		== -4 || data->time_to_sleep == -4 || data->total_meals == -4)
		return (error_exit("Error\nInvalid argument.\
 Ensure all inputs are valid integers."));
	if (data->philo_nbr == -5 || data->time_to_die == -5 || data->time_to_eat
		== -5 || data->time_to_sleep == -5 || data->total_meals == -5)
		return (error_exit("Error\nArgument exceeds\
 the maximum integer limit."));
	if (!data->philo_nbr || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_sleep || !data->total_meals)
		return (error_exit("Error\nArguments cannot be zero."));
	return (0);
}
