/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:22:40 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/03 21:20:56 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTHOR: hicham bouzid
	@DESC: join a char to an string
	@PROTOTYPE: char *ft_charjoin(char *str,
		char c)
	@DATE: 03-04-2024
*/

char	*ft_charjoin(char *str, char c)
{
	int		len;
	char	*ptr;

	if (!str || !*str)
		{
			ptr = malloc(sizeof(char) * (2));
			ptr[0] = c;
			ptr[1] = 0;
			// printf("+_=+\n");
			return (ptr);
		}
	len = (int)ft_strlen(str);
	ptr = malloc(sizeof(char) * (len + 2));
	if (!ptr)
		return (NULL);
	ptr[len + 1] = 0;
	len = 0;
	while (str[len])
	{
		ptr[len] = str[len];
		len++;
	}
	ptr[len] = c;
	free(str);
	return (ptr);
}

/*
	@AUTHOR: hicham bouzid
	@DESC: check if chars in sym are syparde by space
	if not add space
	@PROTOTYPE: char *add_32(char *str, char *sym)
	@DATE: 03-04-2023
*/

char	*add_32(char *str, char *sym)
{
	int		i;
	char	*ptr;

	ptr = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (i == 0 && ft_strchr(sym, str[i]))
		{
			ptr = ft_charjoin(ptr, str[i]);
			if (!ft_strchr(sym, str[i + 1]))
				ptr = ft_charjoin(ptr, 32);
		}
		else if ((!ft_strchr(sym, str[i]) && i < (int)ft_strlen(str)
				&& ft_strchr(sym, str[i + 1])) || (ft_strchr(sym, str[i])
				&& i < (int)ft_strlen(str) && !ft_strchr(sym, str[i + 1])))
		{
			ptr = ft_charjoin(ptr, str[i]);
			ptr = ft_charjoin(ptr, 32);
		}
		else
			ptr = ft_charjoin(ptr, str[i]);
		i++;
	}
	return (ptr);
}

/*
	@AUTHOR: hicham bouzid
	@DESC: remove " and ' by shif the string
	@PROTOTYPE: char *ft_shift(char *ptr)
	@DATE: 04-04-2024
*/

char	*ft_shift(char *ptr)
{
	int		i;
	int		j;
	char	c;
	char	*str;

	i = 0;
	j = 0;
	str = ft_strdup(ptr);
	while (ptr[i])
	{
		if (ptr[i] == '\'' || ptr[i] == '\"')
		{
			c = ptr[i];
			i++;
			while (ptr[i])
			{
				if (ptr[i] == c)
				{
					i++;
					break ;
				}
				else
					str[j++] = ptr[i++];
			}
		}
		else
			str[j++] = ptr[i++];
	}
	str[j] = 0;
	free(ptr);
	return (str);
}

/*
	@AUTHOR: hicham bouzid
	@PROTOTYPE: char	**add_dollar(char **ptr, t_env_v *env)
	@DESC: this function uset to replace env variable by
			by his value check if containe and call other func
	@DATE: 18-05-20240
*/

char	**add_dollar(char **ptr, t_env_v *env)
{
	int		i;
	int		token;
	char	*tmp;

	i = 0;
	while (ptr[i])
	{
		token = 0;
		if (ptr[i] && ft_strchr(ptr[i], '$'))
		{
			token = 1;
		}
		if (token && i && !ft_strcmp(ptr[i -1], "<<"))
			token = 0;
		if (token)
		{
			tmp = ft_replace_dollar(ptr[i], env);
			free(ptr[i]);
			ptr[i] = tmp;
			i = 0;
		}
		i++;
	}
	return (ptr);
}

/*
	@AUTHOR: Hicham BOUZID
	@DESC: function util used just in this file
	@DATE: 22-04-2024
*/

static int ft_checkk(char **ptr, int index)
{

	while (ptr[index])
	{
		if (ft_strchr("<>|", ptr[index][0]) && ft_strlen(ptr[index]) >= 2)
		{
			if (ft_strlen(ptr[index]) > 2)
				return (0);
			if (ptr[index][0] != ptr[index][1])
				return (0);
			if (!ptr[index + 1])
			return (0);
		}
		else if (index && ft_strchr("|<>", ptr[index][0]) &&
			ft_strchr("|<>", ptr[index - 1][0]))
		return (0);
		else if (ft_strchr("|><", ptr[index][0]) && (!ptr[index + 1] || ft_strchr("|><", ptr[index + 1][0])))
		{
			if (ptr[index][0] == '|' && ptr[index + 1][0] != '|')
				return (1);
			return (0);
		}
		index++;
	}
	return (1);
}

/*
	@AUTHOR: Hicham BOUZID
	@DESC: Check if the syntax true or false
	@PROTOTYPE: char **syntax(char **ptr)
	DATE: 22-04-2024
*/

char **syntax(char **ptr)
{

		 if (!ft_checkk(ptr, 0))
		 {
			ft_free(ft_strleen(ptr), ptr);
			ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
			return (NULL);
		 }
		 return (ptr);
}

// !todo add function to check if the syntax true or not

char	**ft_check_syntax(char *str)
{
	char	**ptr;
	int		i;

	i = 0;
	str = ft_convert_0(str);
	str = add_32(str, "|<>");
	ptr = ft_split(str, " \t");
	ptr = undo(ptr);
	i = 0;
	while (ptr[i])
	{
		ptr[i] = expand_or_not(ptr[i]);
		i++;
	}
	ptr = syntax(ptr);
	// printf("here\n");
	return (ptr);
}
