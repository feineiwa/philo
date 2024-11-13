/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:53:35 by frahenin          #+#    #+#             */
/*   Updated: 2024/11/13 10:26:16 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i].fork_mutex, NULL))
			return (ERROR_FAILURE);
		data->forks[i].fork_id = i;
		i++;
	}
	return (0);
}

static void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = (int)philo->data->philo_nbr;
	philo->l_fork = &forks[i];
	philo->r_fork = &forks[(i + 1) % philo_nbr];
	if (philo->ph_id % 2)
	{
		philo->r_fork = &forks[i];
		philo->l_fork = &forks[(i + 1) % philo_nbr];
	}
}

static int	init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->ph_id = i + 1;
		philo->eaten_count = 0;
		if (pthread_mutex_init(&philo->ph_mutex, NULL))
			return (ERROR_FAILURE);
		philo->data = data;
		assign_forks(philo, data->forks, i);
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->forks)
		return (ERROR_FAILURE);
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return (ERROR_FAILURE);
	if (pthread_mutex_init(&data->data_mutex, NULL))
		return (ERROR_FAILURE);
	if (init_forks(data))
		return (ERROR_FAILURE);
	if (init_philos(data))
		return (ERROR_FAILURE);
	return (0);
}
