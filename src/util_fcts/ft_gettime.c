/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:09:47 by kadigh            #+#    #+#             */
/*   Updated: 2023/05/13 00:41:34 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

u_int64_t   ft_mstime(void)
{
    struct timeval tv;
    
    if (gettimeofday(&tv, NULL) == -1)
        exit(1);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
