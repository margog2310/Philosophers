/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:44:18 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/17 22:37:44 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_forks(t_philo *philos[], pthread_mutex_t *forks[],
		int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		philos[i]->left_fork = forks[philos[i]->id - 1];
		philos[i]->right_fork = forks[philos[i]->id];
		if (i == num_of_philos - 1)
			philos[i]->right_fork = forks[num_of_philos - 1];
		i++;
	}
}

int	thinking(t_philo *philo)
{
	int	time;

	time = get_current_time();
	pthread_mutex_lock(&philo->write_lock);
	printf("%d %d is thinking.", time, philo->id);
	pthread_mutex_unlock(&philo->write_lock);
	return (0);
}

int	sleeping(t_philo *philo)
{
	int	time;

	time = get_current_time();
	pthread_mutex_lock(&philo->write_lock);
	printf("%d %d is sleeping.", time, philo->id);
	pthread_mutex_unlock(&philo->write_lock);
	ft_usleep(philo->time_to_sleep * 1000);
	return (0);
}

int	eating(t_philo *philo)
{
	int	time;

	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (-1);
	pthread_mutex_lock(&philo->write_lock);
	time = get_current_time();
	printf("%d %d has taken a fork.\n", time, philo->id);
	pthread_mutex_unlock(&philo->write_lock);
	if (pthread_mutex_lock(philo->left_fork) != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	pthread_mutex_lock(&philo->write_lock);
	time = get_current_time();
	printf("%d %d has taken a fork.\n", time, philo->id);
	pthread_mutex_unlock(&philo->write_lock);
	pthread_mutex_lock(&philo->write_lock);
	time = get_current_time();
	printf("%d %d is eating.\n", time, philo->id);
	pthread_mutex_unlock(&philo->write_lock);
	ft_usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	routine(t_philo *philo)
{
	while (!philo->dead)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
}
