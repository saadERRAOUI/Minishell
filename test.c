/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:54:50 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/24 03:38:17 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	@AUTHOR	: Saad ERRAOUI
	@PROTO	: int	getToken(char **ps, char *es, char **q, char **eq);
	@DESC	: utility function that returns the next token (INT) in the parsed
		string.
	@DATE	: 24-03-2024
*/
int	getToken(char **ps, char *es, char **q, char **eq)
{
	char	*whitespaces;
	char	*symbols;
	char	*s;
	int		ret;

	whitespaces = " \t\r\v\n";
	symbols = "<|>;&()";
	s = (*ps);
	while (s < es && ft_strchr(whitespaces, (*s)))
		s++;
	if (q)
		(*q) = s;
	ret = (*s);
	/* //TODO : MAKE THIS CODE IN A SEPERATE FUNC - START */
	switch(*s)
	{
		case 0:
			break;
		case '|':
		case '(':
		case ')':
		case '&':
		case ':':
		case '<':
			s++;
			break;
		case '>':
			s++;
			if (*s == '>')
			{
				ret = '+';
				s++;
			}
			break;
		default:
			ret = 'a';
			while (s < es && !ft_strchr(whitespaces, (*s)) && !ft_strchr(symbols, (*s)))
				s++;
			break;
	}
	/* //TODO : MAKE THIS CODE IN A SEPERATE FUNC - END */
	if (eq)
		(*eq) = s;
	while (s < es && ft_strchr(whitespaces, (*s)))
		s++;
	(*ps) = s;
	return (ret);
}

int main()
{
	char *ps = "  >>sad|test";
	char *es = (char *)ps + 12;
	char *eq;
	char *q;
	int token = getToken(&ps, es, &q, &eq);
	printf("next token %i %c\n", token, token);

	token = getToken(&ps, es, &q, &eq);
	printf("next token %i %c\n", token, token);
	
	token = getToken(&ps, es, &q, &eq);
	printf("next token %i %c\n", token, token);
	return (0);
}