/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:49:37 by frahenin          #+#    #+#             */
/*   Updated: 2024/11/13 13:16:55 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("%ld is thinking\n", philo->ph_id);
	printf("%ld is eating\n", philo->ph_id);
	printf("%ld is sleeping\n", philo->ph_id);
	return (NULL);
}

int	dinner_start(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, dinner_simulation,
				&data->philos[i]))
			return (ERROR_FAILURE);
		i++;
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			return (ERROR_FAILURE);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (error_exit("Error:\nYour argument should be correct"));
	if (parse_input(&data, av) == ERROR_FAILURE)
		return (ERROR_FAILURE);
	if (init_data(&data) == ERROR_FAILURE)
		return (ERROR_FAILURE);
	if (dinner_start(&data))
		return (ERROR_FAILURE);
	return (0);
}