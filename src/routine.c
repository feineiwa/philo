/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:53:46 by frahenin          #+#    #+#             */
/*   Updated: 2024/12/27 17:48:35 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	take_forks(t_philo *philo)
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
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
}

void	eat(t_philo *philo)
{
	if (philo->data->philo_nbr == 1)
	{
		pthread_mutex_lock(&philo->l_fork->fork_mutex);
		print_status(TAKE_FORK, philo, philo->ph_id);
		ft_usleep(philo->data->time_to_die, philo);
		pthread_mutex_unlock(&philo->l_fork->fork_mutex);
		return ;
	}
	take_forks(philo);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = (time_t)get_current_time();
	philo->eating = TRUE;
	print_status(EATING, philo, philo->ph_id);
	philo->eaten_count++;
	philo->eating = FALSE;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat, philo);
	release_forks(philo);
}

void	think(t_philo *philo)
{
	print_status(THINKING, philo, philo->ph_id);
	usleep(500);
	if (philo->data->time_to_eat > philo->data->time_to_sleep)
		ft_usleep((philo->data->time_to_eat - philo->data->time_to_sleep),
			philo);
	else
		ft_usleep((philo->data->time_to_sleep - philo->data->time_to_eat),
			philo);
}

void	snooze(t_philo *philo)
{
	print_status(SLEEPING, philo, philo->ph_id);
	ft_usleep(philo->data->time_to_sleep, philo);
}
