/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:53:46 by frahenin          #+#    #+#             */
/*   Updated: 2024/12/23 18:18:28 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
}
void	take_forks(t_philo *philo)
{
	if (philo->ph_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->l_fork->fork_mutex);
		print_status(TAKE_FORK, philo, philo->ph_id);
		pthread_mutex_lock(&philo->r_fork->fork_mutex);
		print_status(TAKE_FORK, philo, philo->ph_id);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork->fork_mutex);
		print_status(TAKE_FORK, philo, philo->ph_id);
		pthread_mutex_lock(&philo->l_fork->fork_mutex);
		print_status(TAKE_FORK, philo, philo->ph_id);
	}
	// pthread_mutex_lock(&philo->r_fork->fork_mutex);
	// print_status(TAKE_FORK, philo, philo->ph_id);
	// pthread_mutex_lock(&philo->l_fork->fork_mutex);
	// print_status(TAKE_FORK, philo, philo->ph_id);
}

int	eat(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	if (philo->data->philo_nbr == 1)
	{
		pthread_mutex_lock(&philo->l_fork->fork_mutex);
		print_status(TAKE_FORK, philo, philo->ph_id);
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->l_fork->fork_mutex);
		return (1);
	}
	take_forks(philo);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->eating = TRUE;
	print_status(EATING, philo, philo->ph_id);
	philo->last_meal = (time_t)get_current_time();
	philo->eaten_count++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	philo->eating = FALSE;
	release_forks(philo);
	return (0);
}

int	think(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	print_status(THINKING, philo, philo->ph_id);
	return (0);
}

int	snooze(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	print_status(SLEEPING, philo, philo->ph_id);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

void	*dinner_simulation(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	// if (philo->ph_id % 2 == 0)
	// 	ft_usleep(1);
	while (!is_dead(philo))
	{
		if (eat(philo))
			break ;
		if (snooze(philo))
			break ;
		if (think(philo))
			break ;
		ft_usleep(1);
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
