#include "philosophers.h"

void make_name(char *buf, char *s1, int i)
{
    char *s2;

    ft_strlcpy(buf, s1, ft_strlen(s1) + 1);
    s2 = ft_itoa(i);
    ft_strlcat(buf, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
}

int pthread_sem_init(sem_t *buf, char *s1, int i, int num)
{
    char name[SIZE];

    make_name(name, s1, i);
    sem_unlink(name);
    buf = sem_open(name, O_CREAT | O_EXCL, 0644, num);
    if (buf == SEM_FAILED)
        return (FAIL);
    return (SUCCESS);
}

int pthread_sem_lock(sem_t *sem)
{
    if (sem_wait(sem) != SUCCESS)
        return (FAIL);
    return (SUCCESS);
}

int pthread_sem_unlock(sem_t *sem)
{
    if (sem_post(sem) != SUCCESS)
        return (FAIL);
    return (SUCCESS);
}

int pthread_sem_destroy(sem_t *sem, char *name)
{
    if (sem_close(sem) != SUCCESS)
        return (FAIL);
    if (sem_unlink(name) != SUCCESS)
        return (FAIL);
    return (SUCCESS);
}