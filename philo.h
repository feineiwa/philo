/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:34:59 by frahenin          #+#    #+#             */
/*   Updated: 2024/11/24 15:05:18 by frahenin         ###   ########.fr       */
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
	int					fork_id;
	t_mutex				fork_mutex;
}						t_fork;

typedef struct s_philo
{
	int					ph_id;
	int					eaten_count;
	pthread_t			thread_id;
	t_fork				*l_fork;
	t_fork				*r_fork;
	t_data				*data;
	time_t				start_time;
	time_t				last_meal;
	t_bool				eating;
	t_bool				dead_flag;
}						t_philo;

typedef struct s_data
{
	int					philo_nbr;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					total_meals;
	t_philo				*philos;
	t_fork				*forks;
	t_mutex				dead_lock;
	t_mutex				meal_lock;
	t_mutex				write_lock;
}						t_data;

int						error_exit(char *str);
int						print_error(t_data *data);
int						parse_input(t_data *data, char **av);
int						init_data(t_data *data);
size_t					get_current_time(void);
void					*ft_monitor(void *param);
void					print_status(char *str, t_philo *philo, int id);

#endif