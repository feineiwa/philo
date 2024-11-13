/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:34:59 by frahenin          #+#    #+#             */
/*   Updated: 2024/11/13 11:15:02 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR_FAILURE 1
# define PHILO_MAX 200

typedef enum e_bool
{
	FALSE,
	TRUE,
}						t_bool;

typedef pthread_mutex_t	t_mutex;
typedef struct s_data	t_data;

typedef struct s_fork
{
	long				fork_id;
	t_mutex				fork_mutex;
}						t_fork;

typedef struct s_philo
{
	long				ph_id;
	long				eaten_count;
	pthread_t			thread_id;
	t_fork				*l_fork;
	t_fork				*r_fork;
	t_mutex				ph_mutex;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				total_meals;
	t_mutex				data_mutex;
	t_philo				*philos;
	t_fork				*forks;
}						t_data;

int						error_exit(char *str);
int						print_error(t_data *data);
int						parse_input(t_data *data, char **av);
int						init_data(t_data *data);

#endif