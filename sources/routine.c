/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:44:18 by mganchev          #+#    #+#             */
/*   Updated: 2024/11/21 19:42:11 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_forks(t_philo *philos[], pthread_mutex_t **forks,
		int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		philos[i]->left_fork = forks[philos[i]->id - 1];
		if (i == num_of_philos - 1)
			philos[i]->right_fork = forks[0];
		else
			philos[i]->right_fork = forks[philos[i]->id];
		i++;
	}
}

int	thinking(t_philo *philo)
{
	print_message("is thinking.\n", philo);
	return (0);
}

int	sleeping(t_philo *philo)
{
	print_message("is sleeping.\n", philo);
	ft_usleep(philo->time_to_sleep);
	return (0);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message("has taken a fork.\n", philo);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (pthread_mutex_unlock(philo->right_fork), 0);
	print_message("has taken a fork.\n", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = true;
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_message("is eating.\n", philo);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = false;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_dead_loop(philo))
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (ptr);
}
