/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:44:18 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/17 21:11:36 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	thinking(t_philo *philo)
{
	int	time;

	time = get_current_time();
	pthread_mutex_lock(&philo->write_lock);
	printf("%d %d is thinking.", time, philo->id);
	pthread_mutex_unlock(&philo->write_lock);
	return (0);
}

int sleeping(t_philo *philo)
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

	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
    time = get_current_time();
	pthread_mutex_lock(philo->write_lock);
	printf("%d %d is eating.", time, philo->id);
	pthread_mutex_unlock(&philo->write_lock);
	ft_usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void    routine(t_philo *philo)
{
    while (1)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
}
