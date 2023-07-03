/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:53:37 by bmaudet           #+#    #+#             */
/*   Updated: 2021/10/19 00:55:55 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == ' ') && str[i])
		i++;
	if ((str[i] == '+' || str[i] == '-') && str[i])
		if (str[i++] == '-')
			sign *= -1;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		nb = nb * 10;
		nb += ((int)str[i] - 48);
		i++;
	}
	return (nb * sign);
}
