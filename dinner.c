/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:53:46 by frahenin          #+#    #+#             */
/*   Updated: 2024/11/26 17:21:55 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork->fork_mutex);
	print_status(TAKE_FORK, philo, philo->ph_id);
	if (philo->data->philo_nbr == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->r_fork->fork_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->l_fork->fork_mutex);
	print_status(TAKE_FORK, philo, philo->ph_id);
	philo->eating = TRUE;
	print_status(EATING, philo, philo->ph_id);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->eaten_count++;
	philo->last_meal = (time_t)get_current_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	philo->eating = FALSE;
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
}

void	think(t_philo *philo)
{
	print_status(THINKING, philo, philo->ph_id);
}

void	snooze(t_philo *philo)
{
	print_status(SLEEPING, philo, philo->ph_id);
	ft_usleep(philo->data->time_to_sleep);
}

void	*dinner_simulation(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->ph_id % 2 == 0)
		ft_usleep(1);
	while (!is_dead(philo))
	{
		eat(philo);
		snooze(philo);
		think(philo);
	}
	return (param);
}

int	dinner_start(t_data *data)
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
