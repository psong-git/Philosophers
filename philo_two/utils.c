#include "philosophers.h"

int long_value(int sign)
{
    if (sign == -1)
        return (0);
    else
        return (-1);
}

int ft_atoi(const char *str)
{
    int i;
    int nb;
    int sign;

    i = 0;
    nb = 0;
    sign = 1;
    while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while ('0' <= str[i] && str[i] <= '9')
    {
        nb = nb * 10 + sign * (str[i] - '0');
        i++;
    }
    if (i >= 20)
        nb = long_value(sign);
    return (nb);
}

size_t get_time()
{
    struct timeval current;

    gettimeofday(&current, NULL);
    return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void ft_putnbr_fd(int nb, int fd)
{
    unsigned int nbr;

    if (nb < 0)
    {
        ft_putchar_fd('-', fd);
        nbr = (unsigned int)(nb * -1);
    }
    else
        nbr = (unsigned int)nb;
    if (nbr >= 10)
        ft_putnbr_fd(nbr / 10, fd);
    ft_putchar_fd((char)(nbr % 10 + '0'), fd);
}

size_t ft_strlen(const char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

int clean_all(t_status *all)
{
    int i;
    char name[SIZE];

    i = 0;
    if (all->philos)
    {

        while (i < all->number_of_philosophers)
        {
            make_name(name, "dining", i);
            pthread_sem_destroy(all->philos[i].dining_sem, name);
            make_name(name, "must", i);
            pthread_sem_destroy(all->philos[i].must_eat_sem, name);
            i++;
        }
        free(all->philos);
        all->philos = NULL;
    }
    make_name(name, "forks", 0);
    pthread_sem_destroy(all->forks_sem, name);
    make_name(name, "write", 0);
    pthread_sem_destroy(all->write_sem, name);
    make_name(name, "end", 0);
    pthread_sem_destroy(all->end_sem, name);
    return (FAIL);
}

int error_message()
{
    write(0, "ERROR\n", 6);
    return (FAIL);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    char *dst;
    int i;
    int j;
    size_t len;

    i = 0;
    j = 0;
    if (s1 == NULL)
        return (NULL);
    len = (ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!(dst = (char *)malloc(sizeof(char) * len)))
        return (NULL);
    ft_strlcpy(dst, s1, (ft_strlen(s1) + 1));
    ft_strlcat(dst, s2, len);
    return (dst);
}

size_t ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t dst_len;
    size_t src_len;
    size_t i;

    dst_len = ft_strlen(dst);
    src_len = ft_strlen(src);
    i = 0;
    if (dstsize < dst_len + 1)
        return (dstsize + src_len);
    if (dstsize > dst_len + 1)
    {
        while (src[i] != '\0' && dst_len + 1 + i < dstsize)
        {
            dst[dst_len + i] = src[i];
            i++;
        }
    }
    dst[dst_len + i] = '\0';
    return (dst_len + src_len);
}

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i;

    i = 0;
    if (src == NULL)
        return (0);
    if (dstsize == 0)
        return (ft_strlen(src));
    while (src[i] && i < dstsize - 1)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (ft_strlen(src));
}

char *ft_itoa(int n)
{
    int i;
    int tmp;
    char *s;

    i = 1;
    if (n < 0)
        i++;
    tmp = n;
    while (tmp /= 10)
        i++;
    if (!(s = malloc(sizeof(char) * (i + 1))))
        return (NULL);
    s[i] = '\0';
    if (n < 0)
        s[0] = '-';
    if (n == 0)
        s[0] = '0';
    while (--i >= 0 && n != 0)
    {
        s[i] = ((n > 0) ? 1 : -1) * (n % 10) + '0';
        n = n / 10;
    }
    return (s);
}