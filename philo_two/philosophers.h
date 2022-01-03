#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#define SUCCESS 0
#define FAIL 1
#define TRUE 1
#define FALSE 0
#define EAT 0
#define SLEEP 1
#define FORK 2
#define THINK 3
#define END 4
#define DEAD 5
#define MESSAGE_STOP 0
#define MESSAGE_GO 1
#define SIZE 255

typedef struct s_philo
{
    int position;
    size_t time_limit;
    struct s_status *all;
    sem_t *dining_sem;
    sem_t *must_eat_sem;
} t_philo;

typedef struct s_status
{
    int number_of_philosophers;
    int must_eat_count;

    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t time_to_start;

    t_philo *philos;
    sem_t *forks_sem;
    sem_t *write_sem;
    sem_t *end_sem;
} t_status;

//utils
int long_value(int sign);
int ft_atoi(const char *str);
size_t get_time();
void ft_putnbr_fd(int nb, int fd);
size_t ft_strlen(const char *str);
void ft_putchar_fd(char c, int fd);
int error_message();
int clean_all(t_status *all);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
char *ft_itoa(int n);

//init
int init_semaphores(t_status *all);
int init_philos(t_status *all);
int init_all(t_status *all, int ac, char **av);
int parse_argv(char **av);

//dining
void exceptional(t_philo *philo);
void get_forks(t_philo *philo);
void put_down_forks(t_philo *philo);
void eating(t_philo *philo);

//message
char *get_message(int type);
void display_message(t_philo *philo, int type);

//translate
int pthread_sem_init(sem_t *buf, char *s1, int i, int num);
int pthread_sem_lock(sem_t *sem);
int pthread_sem_unlock(sem_t *sem);
void make_name(char *buf, char *s1, int i);
int pthread_sem_destroy(sem_t *sem, char *name);