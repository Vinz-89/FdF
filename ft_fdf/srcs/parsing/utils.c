#include "../fdf.h"

long	ft_atoi(const char *nptr)
{
	int		i;
	long	value;
	int		sign;

	i = 0;
	value = 0;
	sign = 1;
	while (nptr[i] == ' ' || ('\t' <= nptr[i] && nptr[i] <= '\r'))
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		value = value * 10 + (nptr[i] - '0');
		if (INT_MAX < value * sign || value * sign < INT_MIN)
			return (value * sign);
		i++;
	}
	return (value * sign);
}

long	ft_abs(long value)
{
	if (value < 0)
		return (-value);
	return (value);
}
