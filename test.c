#include <stdio.h>
#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned long long	i;
	unsigned long long	f;

	i = 0;
	if (dstsize <= 0)
		return (strlen(src));
	f = dstsize;
	while (i < f - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (strlen(src));
}

// #include<string.h>
// #include<stdio.h>
int main()
{
	char dst[5];
	char *src = "the-42  ";
	// printf("size returned is == %d\n", (int)strlcpy(dst, src, 6));
	ft_strlcpy(dst, src, 7);
	printf("the dest is  == %s\n", dst);
}