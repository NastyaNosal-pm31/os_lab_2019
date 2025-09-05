# Лабораторная работа №5

## Задание 1

Скомпилировать mutex.c без использования и с использованием мьютекса. Объяснить разницу в поведении программы.

без:
```bash
gcc -pthread -o mutex mutex.c
./mutex
```
```bash
doing one thing
counter = 0
doing another thing
counter = 0
doing another thing
counter = 1
doing one thing
counter = 1
doing another thing
counter = 2
doing another thing
counter = 3
doing one thing
counter = 2
doing another thing
counter = 4
doing one thing
counter = 3
doing another thing
counter = 5
doing one thing
counter = 4
doing another thing
counter = 6
doing another thing
counter = 7
doing one thing
counter = 5
doing another thing
counter = 8
doing another thing
counter = 9
doing one thing
counter = 6
doing another thing
counter = 10
doing another thing
counter = 11
doing one thing
counter = 7
doing another thing
counter = 12
doing another thing
counter = 13
doing one thing
counter = 8
doing another thing
counter = 14
doing one thing
counter = 9
doing another thing
counter = 15
doing another thing
counter = 16
doing another thing
counter = 17
doing one thing
counter = 10
doing another thing
counter = 18
doing one thing
counter = 11
doing another thing
counter = 19
doing one thing
counter = 12
doing another thing
counter = 20
doing another thing
counter = 21
doing another thing
counter = 22
doing one thing
counter = 13
doing another thing
counter = 23
doing one thing
counter = 14
doing another thing
counter = 24
doing another thing
counter = 25
doing another thing
counter = 26
doing one thing
counter = 15
doing another thing
counter = 27
doing one thing
counter = 16
doing another thing
counter = 28
doing one thing
counter = 17
doing another thing
counter = 29
doing another thing
counter = 30
doing one thing
counter = 18
doing another thing
counter = 31
doing one thing
counter = 19
doing another thing
counter = 32
doing one thing
counter = 20
doing one thing
counter = 21
doing one thing
counter = 22
doing one thing
counter = 23
doing another thing
counter = 33
doing one thing
counter = 24
doing one thing
counter = 25
doing one thing
counter = 26
doing one thing
counter = 27
doing another thing
counter = 34
doing one thing
counter = 28
doing one thing
counter = 35
doing one thing
counter = 36
doing another thing
counter = 36
doing another thing
counter = 37
doing one thing
counter = 37
doing another thing
counter = 38
doing one thing
counter = 38
doing another thing
counter = 39
doing another thing
counter = 40
doing one thing
counter = 39
doing another thing
counter = 41
doing one thing
counter = 40
doing another thing
counter = 42
doing one thing
counter = 41
doing another thing
counter = 43
doing another thing
counter = 44
doing another thing
counter = 45
doing another thing
counter = 46
doing another thing
counter = 47
doing another thing
counter = 48
doing one thing
counter = 42
doing another thing
counter = 49
doing one thing
counter = 43
doing another thing
counter = 50
doing one thing
counter = 44
doing one thing
counter = 45
doing one thing
counter = 46
doing one thing
counter = 47
doing one thing
counter = 48
doing one thing
counter = 49
doing one thing
counter = 50
doing one thing
counter = 51
doing one thing
counter = 52
doing one thing
counter = 53
doing one thing
counter = 54
doing one thing
counter = 55
All done, counter = 56
```

С:
```bash
gcc -pthread -o mutex mutex.c
./mutex
```
```bash
doing one thing
counter = 0
doing one thing
counter = 1
doing one thing
counter = 2
doing one thing
counter = 3
doing one thing
counter = 4
doing one thing
counter = 5
doing one thing
counter = 6
doing one thing
counter = 7
doing one thing
counter = 8
doing one thing
counter = 9
doing one thing
counter = 10
doing one thing
counter = 11
doing another thing
counter = 12
doing another thing
counter = 13
doing another thing
counter = 14
doing one thing
counter = 15
doing one thing
counter = 16
doing one thing
counter = 17
doing one thing
counter = 18
doing one thing
counter = 19
doing one thing
counter = 20
doing one thing
counter = 21
doing one thing
counter = 22
doing one thing
counter = 23
doing one thing
counter = 24
doing one thing
counter = 25
doing one thing
counter = 26
doing one thing
counter = 27
doing one thing
counter = 28
doing one thing
counter = 29
doing one thing
counter = 30
doing one thing
counter = 31
doing one thing
counter = 32
doing one thing
counter = 33
doing one thing
counter = 34
doing one thing
counter = 35
doing one thing
counter = 36
doing one thing
counter = 37
doing one thing
counter = 38
doing one thing
counter = 39
doing one thing
counter = 40
doing one thing
counter = 41
doing one thing
counter = 42
doing one thing
counter = 43
doing one thing
counter = 44
doing one thing
counter = 45
doing one thing
counter = 46
doing one thing
counter = 47
doing one thing
counter = 48
doing one thing
counter = 49
doing one thing
counter = 50
doing one thing
counter = 51
doing one thing
counter = 52
doing another thing
counter = 53
doing another thing
counter = 54
doing another thing
counter = 55
doing another thing
counter = 56
doing another thing
counter = 57
doing another thing
counter = 58
doing another thing
counter = 59
doing another thing
counter = 60
doing another thing
counter = 61
doing another thing
counter = 62
doing another thing
counter = 63
doing another thing
counter = 64
doing another thing
counter = 65
doing another thing
counter = 66
doing another thing
counter = 67
doing another thing
counter = 68
doing another thing
counter = 69
doing another thing
counter = 70
doing another thing
counter = 71
doing another thing
counter = 72
doing another thing
counter = 73
doing another thing
counter = 74
doing another thing
counter = 75
doing another thing
counter = 76
doing another thing
counter = 77
doing another thing
counter = 78
doing another thing
counter = 79
doing another thing
counter = 80
doing another thing
counter = 81
doing another thing
counter = 82
doing another thing
counter = 83
doing another thing
counter = 84
doing another thing
counter = 85
doing another thing
counter = 86
doing another thing
counter = 87
doing another thing
counter = 88
doing another thing
counter = 89
doing another thing
counter = 90
doing another thing
counter = 91
doing another thing
counter = 92
doing another thing
counter = 93
doing another thing
counter = 94
doing another thing
counter = 95
doing another thing
counter = 96
doing another thing
counter = 97
doing another thing
counter = 98
doing another thing
counter = 99
All done, counter = 100
@NastyaNosal-pm31 ➜ /workspaces/os_lab_2019/lab5/src (master) $ 
```

Видно, что без мутекса потоки образуют в критической области так называемое состояние гонки, а во втором мутех блокирует поток и выполняется поочерёдно. Мьютекс необходим для защиты общих данных в многопоточных программах. Без него возникает состояние гонки, приводящее к потере данных и непредсказуемому поведению. С мьютексом программа работает корректно, но может быть менее производительной из-за блокировок.

## Задание 2

Написать программу для паралелльного вычисления факториала по модулю `mod` (`k!`), которая будет принимать на вход следующие параметры (пример: `-k 10 --pnum=4 --mod=10`):

1. `k` - число, факториал которого необходимо вычислить.
2. `pnum` - количество потоков.
3. `mod` - модуль факториала

Для синхронизации результатов необходимо использовать мьютексы.

```C++
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <getopt.h>
#include <sys/time.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

typedef struct node
{
    uint64_t result;
    uint64_t multiplier;
    uint64_t mod;
} node;

void calculations(void *__arg)
{
    pthread_mutex_lock(&mtx);
    node *buff = (node *)__arg;
    uint64_t mod = buff->mod;
    buff->result = 
    ((buff->result % mod) * (buff->multiplier % mod))%mod;
    pthread_mutex_unlock(&mtx);
}

int main(int argc, char *argv[])
{
    uint32_t k = 0;
    uint32_t pnum = 0;
    uint32_t mod = 0;

    static struct option options[] = {{"k", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"mod", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    while (true)
    {
        int current_optind = optind ? optind : 1;

        int option_index = 0;
        int c = getopt_long(argc, argv, "", options, &option_index);

        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            switch (option_index)
            {
            case 0:
                k = atoi(optarg);

                break;
            case 1:
                pnum = atoi(optarg);

                if (pnum == 0)
                {
                    printf("Threads number is a positive number\n");
                }

                break;
            case 2:
                mod = atoi(optarg);

                if (mod == 0)
                {
                    printf("Module is a positive number.\n");
                }

                break;

            defalut:
                printf("Index %d is out of options\n", option_index);
            }
            break;

        default:
            printf("getopt returned character code 0%o?\n", c);
        }
    }

    if (optind < argc)
    {
        printf("Has at least one no option argument\n");
        return 1;
    }

    if (pnum == 0 || mod == 0)
    {
        printf("Usage: %s --k \"num\" --pnum \"num\" --mod \"num\" \n",
               argv[0]);
        return 1;
    }

    node *res = (node *)malloc(sizeof(node));
    res->mod = mod;
    res->result = 1;
    pthread_t threads[pnum];

    for (uint64_t i = 1; i <= k; ++i)
    {
        res->multiplier = i;
        size_t idx = (i-1) % pnum;
        if (pthread_create(&threads[idx], NULL, (void *)calculations, (void *)res) != 0)
        {
            perror("pthread_create"); exit(1);
        }

        if (pthread_join(threads[idx], NULL))
        {
            perror("pthread_join"); exit(1);
        }
    }

    printf("Factorial %i mod %i is equals %i.\n", k, mod, res->result);
    free(res);

    return 0;
}
```

```
gcc -pthread -o factorial factorial.c
./factorial --k "2" --pnum "2" --mod "2" 
./factorial --k "3" --pnum "2" --mod "4" 
```

![alt text](image-4.png)

## Задание 3

### Необходимые знания

1. Состояние deadlock

Напишите программу для демонстрации состояния deadlock.
```C++
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER,
                mtx2 = PTHREAD_MUTEX_INITIALIZER;

int global_var = 1;

void work1(void *arg)
{
    pthread_mutex_lock(&mtx1);
    sleep(1);
    pthread_mutex_lock(&mtx2);
    for (int i = 0; i < 100; ++i)
    {
        global_var *= 2;
        printf("%d_", global_var);
    }
    sleep(3);
    pthread_mutex_unlock(&mtx2);
    pthread_mutex_unlock(&mtx1);
}

void work2(void *arg)
{
    pthread_mutex_lock(&mtx2);
    sleep(1);
    pthread_mutex_lock(&mtx1);
    for (int i = 0; i < 100; ++i)
    {
        global_var *= 3;
        printf("%d_", global_var);
    }
    sleep(3);
    pthread_mutex_unlock(&mtx1);
    pthread_mutex_unlock(&mtx2);
}

int main()
{
    pthread_t thr1, thr2;
    void *some;

    if (pthread_create(&thr1, NULL, (void *)work1, some))
    {
        perror("pthread create");
        exit(1);
    }

    if (pthread_create(&thr2, NULL, (void *)work2, some))
    {
        perror("pthread create");
        exit(1);
    }

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    printf("\n");
    return 0;
}
```
```bash
@NastyaNosal-pm31 ➜ /workspaces/os_lab_2019/lab5/src (master) $ gcc -o deadlock deadlock.c -lpthread
@NastyaNosal-pm31 ➜ /workspaces/os_lab_2019/lab5/src (master) $ ./deadlock
```
![alt text](image-5.png)



