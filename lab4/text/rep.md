### Задание №1

...
#### Решение
```bash
gcc parallel_min_max.c utils.c find_min_max.c -o ex_1
./ex_1 --seed 100000 --array_size 2000000 --pnum 5000 --timeout 1
./ex_1 --seed 2 --array_size 50000 --pnum 100 --timeout 1 
```
```bash
Timeout reached! Sending SIGKILL to child processes.
583492
All child processes terminated due to timeout.
10085
Min: 61026
Max: 2147481746
Elapsed time: 10.085000ms
```

### Задание №2
```bash
 gcc zombie.c -o zombie
./zombie &
ps aux | grep Z
```

```bash
[1] 42289
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
codespa+   42291  0.0  0.0      0     0 pts/2    Z    05:55   0:00 [zombie] <defunct>
codespa+   42302  0.0  0.0   7080  2176 pts/2    S+   05:55   0:00 grep --color=auto Z
```
...
### Задание №3

...
#### Решение
```bash
gcc process_memory.c -o ex_3
./ex_3
```
```bash
Address etext: 922C8509 
Address edata: 922CB018 
Address end  : 922CB050 
ID main          is at virtual address: 922C8249
ID showit        is at virtual address: 922C840C
ID cptr          is at virtual address: 922CB010
ID buffer1       is at virtual address: 922CB030
ID i     is at virtual address:  C681EC4
A demonstration
ID buffer2       is at virtual address:  C681EA0
Alocated memory at B19D56B0
This message is output by the function showit()
```
### Задание №4-6

...
#### Решение
```
make clean
make parallel_sum
./parallel_sum --seed 1 --array_size 5 --threads_num 2
```
```
Generated array (5 elements): 1804289383 846930886 1681692777 1714636915 1957747793 
Total: 8005297754
Суммирование заняло 0.090000 миллисекунд
```
