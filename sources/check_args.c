/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:07:57 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/20 19:58:25 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// all args should be > 0 EXCEPT number of meals each philo should eat (edge case)
// in eval form it says to not test with more than 200 philos so limit of 200 can be set

#include "philosophers.h"

bool	is_number(char **args)
{
	int	i;
	int	j;

	j = 1;
	while (args[j])
	{
		i = 0;
		while (args[j][i])
		{
			if (args[j][i] == '-' || args[j][i] == '+')
				i++;
			if (!ft_isdigit(args[j][i]))
				return (false);
			i++;
		}
		j++;
	}
	return (true);
}

bool	is_positive(char **args, bool meals_number)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (ft_atoi(args[i]) <= 0)
			return (false);
		i++;
	}
	if (meals_number)
	{
		if (ft_atoi(args[i]) < 0)
			return (false);
	}
	return (true);
}

bool	check_args(char **args, bool meals_number)
{
	if (!is_number(args))
		return (false);
	if (!is_positive(args, meals_number))
		return (false);
	return (true);
}
