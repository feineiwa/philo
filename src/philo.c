/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:49:37 by frahenin          #+#    #+#             */
/*   Updated: 2024/12/26 14:04:40 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*dinner_simulation(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->data->philo_nbr % 2 == 0)
	{
		if (philo->ph_id % 2 == 0)
			ft_usleep(1, philo);
	}
	while (!is_dead(philo))
	{
		if (eat(philo))
			break ;
		if (snooze(philo))
			break ;
		if (think(philo))
			break ;
		ft_usleep(1, philo);
	}
	return (param);
}

static int	dinner_start(t_data *data)
{
	int			i;
	pthread_t	observer;

	if (pthread_create(&observer, NULL, &ft_monitor, data->philos))
		return (ERROR_FAILURE);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &dinner_simulation,
				&data->philos[i]))
			return (ERROR_FAILURE);
		i++;
	}
	if (pthread_join(observer, NULL))
		return (ERROR_FAILURE);
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
		return (error_exit("Error:\nError number of argument"));
	if (parse_input(&data, av) == ERROR_FAILURE)
		return (ERROR_FAILURE);
	if (init_data(&data) == ERROR_FAILURE)
		return (ERROR_FAILURE);
	if (dinner_start(&data))
		return (ERROR_FAILURE);
	destroy_all(&data);
	return (0);
}
