/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:48:49 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 10:48:49 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include <stdio.h>

int main()
{
	printf("--------- Zone de test ---------\n");
		
	printf("== is stuff ==\n");
	printf("a is alpha %d\n", ft_isalpha('a'));
	printf("2 is digit %d\n", ft_isdigit('2'));
	printf("0 is alnum %d\n", ft_isalnum('0'));
	printf("\t is ascii %d\n", ft_isascii('\t'));
	printf("! is print %d\n", ft_isprint('!'));
	printf("<a nice string> len:%ld\n", ft_strlen("a nice string"));
	printf("== memset ==\n");
	char s[] = "abcde";
	char c = 'f';
	printf("s: %s with 3 %c\n", s, c);
	ft_memset(s, c, 3);
	printf("=) s: %s\n", s);
	printf("== bzero ==\n");

	printf("== memcpy ==\n");
	char dest[] = "abcde";
	char src[] = "ffffffffff";
	printf("!) des: %s\n", dest);
	printf("!) src: %s\n", src);
	ft_memcpy(dest, src, 3);
	printf("=) des: %s\n", dest);
	printf("=) src: %s\n", src);

	// Overlap example
	// Copy abcde dans cde
	// donne donc aba car [abcde] - [abade] - [ababe] - [ababa] Donc [aba]
	char src2[] = "abcde";
	char *dest2 = src2+2;
	//char dest2[] = "abcde";
	//char src2[] = "ffffffffff";
	printf("!) des: %s\n", dest2);
	printf("!) src: %s\n", src2);
	ft_memcpy(dest2, src2, 3);
	printf("=) des: %s\n", dest2);
	printf("=) src: %s\n", src2);

	printf("== memmove ==\n");
	char dest3[] = "abcde";
	char src3[] = "ffffffffff";
	printf("!) des: %s\n", dest3);
	printf("!) src: %s\n", src3);
	ft_memmove(dest3, src3, 3);
	//memmove(dest3, src3, 3);
	printf("=) des: %s\n", dest3);
	printf("=) src: %s\n", src3);

	// Overlap example
	// Move de abcde dans cde
	// donne donc abc car [abcde] - [abcdc] - [adcbc] - [ababc] Donc [abc]
	char src4[] = "abcde";
	char *dest4 = src4+2;
	printf("!) des: %s\n", dest4);
	printf("!) src: %s\n", src4);
	ft_memmove(dest4, src4, 3);
	//memmove(dest4, src4, 3);
	printf("=) des: %s\n", dest4);
	printf("=) src: %s\n", src4);

	printf("== strlcpy ==\n");
	// Alwayse NULL terminate!
	char dest5[] = "abcde";
		char src5[] = "fff";
		printf("dest[%s] , src[%s] \n", dest5, src5);
		unsigned int result5 = (unsigned int)ft_strlcpy(dest5, src5, 2);
		printf("dest[%s] , src[%s] \n", dest5, src5);
		printf("%u \n", result5);

	printf("== strlcat ==\n");

		char src6[] = "bla"; // 6
		char dest6[100] = "toto"; //10
	printf("dest[%s] , src[%s] \n", dest6, src6);
	unsigned int result6 = (unsigned int)ft_strlcat(dest6, src6, 3);
	printf("dest[%s] , src[%s] \n", dest6, src6);
	printf("%u \n", result6);

		char src7[] = "bla"; // 6
		char dest7[100] = "toto"; //10
	printf("dest[%s] , src[%s] \n", dest7, src7);
	unsigned int result7 = (unsigned int)ft_strlcat(dest7, src7, 100);
	printf("dest[%s] , src[%s] \n", dest7, src7);
	printf("%u \n", result7);

	printf("== ==== ==\n");
	printf("%c\n", ft_toupper('u'));
	printf("%c\n", ft_tolower('L'));
	printf("%s\n", ft_strchr("search x letter x first", 'x'));
	printf("%s\n", ft_strrchr("search x letter x last", 'x'));

	printf("== strcmp ==\n");
	printf("Comp result (n=4): %d\n", ft_strncmp("Hello", "Hellz", 4));
	printf("Comp result (n=5): %d\n", ft_strncmp("Hello", "Hellz", 5));
	printf("Comp result (n=5): %d\n", ft_strncmp("Hello", "Hello, World!", 5));

	printf("== memchr ==\n");
	char searchmemory[] = "search x letter x first";
	printf("%s\n", (char *)ft_memchr(searchmemory, (int)'x', (size_t)22));

	printf("== memcmp ==\n");
	printf("Comp result (n=4): %d\n", ft_memcmp("Hello", "Hellz", 4));
	printf("Comp result (n=5): %d\n", ft_memcmp("Hello", "Hellz", 5));
	printf("Comp result (n=5): %d\n", ft_memcmp("Hello", "Hello, World!", 5));

	printf("== strnstr ==\n");
	printf("%s\n", ft_strnstr("try to find the word in len 21", "find", 21));

	printf("== atoi ==\n");
	char str = '29';
	printf("%d\n", ft_atoi(" \n\v\f\r\t  -1234aa"));
	printf("%d\n", atoi(" \n\v\f\r\t  -1234aa"));
	printf("%d\n", ft_atoi(" \n\v\f\r\t  01234"));
	printf("%d\n", atoi(" \n\v\f\r\t  01234"));
	printf("%d\n", ft_atoi("-124121412414124214"));
	printf("%d\n", atoi("-124121412414124214"));

	printf("== strdup ==\n");
	printf("%s\n", ft_strdup("d"));

	printf("--------- PARTIE 2 ---------\n");

	printf("%s\n", ft_substr("Not cutted string and no more", 4, 13));
	printf("%s\n", ft_strjoin("string ", "joined"));
	printf("%s\n", ft_strtrim("x<x>>Tri<>med<>x>>>", "<>x"));
	//printf("%s\n", ft_split("My super message ", ' ')[0]);
	//printf("%s\n", ft_split("My super message ", ' ')[1]);
	//printf("%s\n", ft_split("My super message ", ' ')[2]);


	//printf("%s\n", ft_split("\t\t\t\thello!\t\t\t\t", '\t')[0]);
	printf("%s\n", ft_split("   split    this for   me  !   ", ' ')[4]);
	printf("%s\n", ft_split("hello!", ' ')[0]);
	printf("%s\n", ft_split("zzzz", 'z'));
	printf("%s\n", ft_split("zzzzzhello!", 'z')[0]);
	printf("%s\n", ft_split("hello!zzz", 'z')[0]);

	printf("%s\n", ft_itoa(-0));
	printf("%s\n", ft_itoa(512));
	printf("%s\n", ft_itoa(-512));
	printf("%s\n", ft_itoa(-2147483647));
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(2147483647));

	return 0;
}

