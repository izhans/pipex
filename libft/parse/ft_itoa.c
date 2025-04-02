/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:37:15 by isastre-          #+#    #+#             */
/*   Updated: 2025/03/21 15:22:52 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_number_len(long n);

char	*ft_itoa(int n)
{
	long	num;
	int		len;
	char	*str;
	int		i;

	num = n;
	len = ft_number_len(num);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (num < 0)
	{
		str[i] = '-';
		num *= -1;
		i++;
	}
	str[len] = '\0';
	while (len > i)
	{
		len--;
		str[len] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
