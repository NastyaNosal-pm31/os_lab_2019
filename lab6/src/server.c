#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>

#include <getopt.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include "multmodulo.h"

struct FactorialArgs {
    uint64_t begin;
    uint64_t end;
    uint64_t mod;
};

uint64_t Factorial(const struct FactorialArgs *args) {
    uint64_t ans = 1;
    // [begin, end) — полуоткрытый интервал
    for (uint64_t i = args->begin; i < args->end; i++) {
        ans = (ans * i) % args->mod;
    }
    return ans;
}

void *ThreadFactorial(void *arg) {
    struct FactorialArgs *args = (struct FactorialArgs *)arg;
    uint64_t *result = malloc(sizeof(uint64_t));
    if (!result) {
        fprintf(stderr, "malloc failed\n");
        pthread_exit(NULL);
    }
    *result = Factorial(args);
    return (void *)result;
}

int main(int argc, char **argv) {
    int tnum = -1;
    int port = -1;

    while (true) {
        int current_optind = optind ? optind : 1;
        static struct option options[] = {
            {"port", required_argument, 0, 0},
            {"tnum", required_argument, 0, 0},
            {0, 0, 0, 0}
        };
        int option_index = 0;
        int c = getopt_long(argc, argv, "", options, &option_index);
        if (c == -1) break;

        switch (c) {
            case 0:
                switch (option_index) {
                    case 0:
                        port = atoi(optarg);
                        if (port <= 0) {
                            printf("invalid port number.\n");
                            return 1;
                        }
                        break;
                    case 1:
                        tnum = atoi(optarg);
                        if (tnum <= 0) {
                            printf("invalid number of threads.\n");
                            return 1;
                        }
                        break;
                    default:
                        printf("Index %d is out of options\n", option_index);
                }
                break;
            case '?':
                printf("Unknown argument\n");
                break;
            default:
                fprintf(stderr, "getopt returned character code 0%o?\n", c);
        }
    }

    if (port == -1 || tnum == -1) {
        fprintf(stderr, "Using: %s --port 20001 --tnum 4\n", argv[0]);
        return 1;
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        fprintf(stderr, "Can not create server socket!\n");
        return 1;
    }

    int opt_val = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val));

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        fprintf(stderr, "Can not bind to socket!\n");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 128) < 0) {
        fprintf(stderr, "Could not listen on socket\n");
        close(server_fd);
        return 1;
    }

    printf("Server listening at %d\n", port);

    while (true) {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int client_fd = accept(server_fd, (struct sockaddr *)&client, &client_len);
        if (client_fd < 0) {
            fprintf(stderr, "Could not establish new connection\n");
            continue;
        }

        while (true) {
            const size_t buf_size = 3 * sizeof(uint64_t);
            char buffer[buf_size];
            int n = recv(client_fd, buffer, buf_size, 0);
            if (n == 0) break;
            if (n < 0) {
                fprintf(stderr, "Client read failed\n");
                break;
            }
            if (n != buf_size) {
                fprintf(stderr, "Client send wrong data format\n");
                break;
            }

            uint64_t begin, end, mod;
            memcpy(&begin, buffer, sizeof(uint64_t));
            memcpy(&end, buffer + sizeof(uint64_t), sizeof(uint64_t));
            memcpy(&mod, buffer + 2 * sizeof(uint64_t), sizeof(uint64_t));

            printf("Receive: %" PRIu64 " %" PRIu64 " %" PRIu64 "\n", begin, end, mod);

            pthread_t threads[tnum];
            struct FactorialArgs args[tnum];

            uint64_t len = end - begin;
            for (int i = 0; i < tnum; i++) {
                args[i].begin = begin + i * len / tnum;
                args[i].end = begin + (i + 1) * len / tnum;
                args[i].mod = mod;

                if (pthread_create(&threads[i], NULL, ThreadFactorial, &args[i])) {
                    fprintf(stderr, "pthread_create failed\n");
                    goto cleanup;
                }
            }

            uint64_t total = 1;
            for (int i = 0; i < tnum; i++) {
                void *thread_result;
                pthread_join(threads[i], &thread_result);
                uint64_t result = *(uint64_t *)thread_result;
                free(thread_result);
                total = MultModulo(total, result, mod);
            }

            printf("Total: %" PRIu64 "\n", total);

            if (send(client_fd, &total, sizeof(total), 0) < 0) {
                fprintf(stderr, "Send failed\n");
                break;
            }
        }

    cleanup:
        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}