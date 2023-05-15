/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:46:30 by kadigh            #+#    #+#             */
/*   Updated: 2023/05/15 22:23:13 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_vars_struct(t_data **data,int ac, char ** av)
{
	(*data)->vars->nbr_of_philos= ft_atoi(av[1]);
	(*data)->vars->time_to_die= ft_atoi(av[2]);
	(*data)->vars->time_to_eat= ft_atoi(av[3]);
	(*data)->vars->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*data)->vars->nbrof_meals = ft_atoi(av[5]);
	else
		(*data)->vars->nbrof_meals = -1;
}

void	init_args(int ac, char **av, t_data	**data)
{
	int i;

	(*data)->philos = malloc((*data)->vars->nbr_of_philos * sizeof(t_philo *) );
	(*data)->philos_thread = malloc((*data)->vars->nbr_of_philos * sizeof(pthread_t *));
	(*data)->forks = malloc((*data)->vars->nbr_of_philos * sizeof(pthread_mutex_t *));
	init_vars_struct(data, ac, av);
	i = 0;
	while (i < (*data)->vars->nbr_of_philos)
	{
		(*data)->philos[i] = (t_philo *)calloc(1,sizeof(t_philo));
		(*data)->philos_thread[i] = (pthread_t *)ft_calloc(1,sizeof(pthread_t));
		(*data)->forks[i] = (pthread_mutex_t *)ft_calloc(1,sizeof(pthread_mutex_t));
		i++;
	}
}

	// (*data)->nbr_of_philos = ft_atoi(av[1]);
	// (*data)->time_to_die = ft_atoi(av[2]);
	// (*data)->time_to_eat = ft_atoi(av[3]);
	// (*data)->time_to_sleep = ft_atoi(av[4]);
	// if (ac == 6)
	// 	(*data)->nbr_of_times_each_philo_must_eat = ft_atoi(av[5]);
	// else
	// 	(*data)->nbr_of_times_each_philo_must_eat = -1;


	// i = -1;
	// while (++i < (*data)->vars.nbr_of_philos)
	// {
	// 	(*data)->philos[i].vars.nbr_of_philos = ft_atoi(av[1]);
	// 	(*data)->philos[i].vars.time_to_die = ft_atoi(av[2]);	
	// 	(*data)->philos[i].vars.time_to_eat = ft_atoi(av[3]);
	// 	(*data)->philos[i].vars.time_to_sleep = ft_atoi(av[4]);
	// 	if (ac == 6)
	// 		(*data)->philos[i].vars.nbrof_meals = ft_atoi(av[5]);
	// 	else
	// 		(*data)->philos[i].vars.nbrof_meals = -1;
		// i++;
	// }



	// printf("nb\t%d\ndie\t%d\neat\t%d\nslp\t%d\nlas \t%d ",(*data)->nbr_of_philos ,(*data)->time_to_die ,(*data)->time_to_eat ,(*data)->time_to_sleep,(*data)->nbr_of_times_each_philo_must_eat);



	// (*data)->philos = (t_philo *)ft_calloc(1, sizeof(t_philo) * (*data)->nbr_of_philos);
	// (*data)->forks = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t) * (*data)->nbr_of_philos);