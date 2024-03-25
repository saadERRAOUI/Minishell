/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:43:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/03/25 02:47:07 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int      count_words(char const *s, char c)
{
        int     i;
        int     chuncks_number;

        i = 0;
        chuncks_number = 0;
        if (*s == '\0')
                return (chuncks_number);
        while (s[i] && s[i] == c)
                i++;
        while (s[i])
        {
                if (s[i] == c && s[i - 1] != c)
                        chuncks_number += 1;
                i++;
        }
        if (s[i - 1] != c)
                chuncks_number += 1;
        return (chuncks_number);
}

static int      count_word_len(char const *s, char c)
{
        int     i;
        int     len;

        i = 0;
        len = 0;
        while (s[i] && s[i] == c)
                i++;
        while (s[i] && s[i] != c)
        {
                len++;
                i++;
        }
        return (len);
}

static void     *free_allocation(char **s, int count)
{
        while (count >= 0)
        {
                free(s[count]);
                count--;
        }
        free(s);
        s = NULL;
        return (NULL);
}

char    **ft_split(char const *s, char c)
{
        char    **str;
        int             offset;
        int             j;
        int             i;

        offset = 0;
        i = 0;
        str = malloc((count_words(s, c) + 1) * sizeof(char *));
        if (!s || !str)
                return (NULL);
        while (i < count_words(s, c))
        {
                str[i] = malloc((count_word_len(&s[offset], c) + 1) * sizeof(char));
                if (!str[i])
                        return (free_allocation(str, i));
                j = 0;
                while (s[offset] == c)
                        offset++;
                while (s[offset] && s[offset] != c)
                        str[i][j++] = s[offset++];
                str[i][j] = '\0';
                i++;
        }
        str[i] = NULL;
        return (str);
}

t_env_v	*ft_lstlast(t_env_v *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_env_v **lst, t_env_v *new)
{
	t_env_v	*tmp;

	if (!lst)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}
