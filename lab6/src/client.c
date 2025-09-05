#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <inttypes.h>
#include <stdbool.h>

struct Server {
    char ip[255];
    int port;
};

struct ThreadArgs {
    struct Server server;
    uint64_t begin;
    uint64_t end;
    uint64_t mod;
    uint64_t result;
};

bool ConvertStringToUI64(const char *str, uint64_t *val) {
    char *end = NULL;
    unsigned long long i = strtoull(str, &end, 10);
    if (errno == ERANGE || end == str || *end != '\0') {
        fprintf(stderr, "Invalid uint64_t: %s\n", str);
        return false;
    }
    *val = i;
    return true;
}

void *ThreadSend(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    struct hostent *host = gethostbyname(args->server.ip);
    if (!host) {
        fprintf(stderr, "gethostbyname failed: %s\n", args->server.ip);
        args->result = 1;
        return NULL;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        fprintf(stderr, "Socket failed\n");
        args->result = 1;
        return NULL;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(args->server.port);
    addr.sin_addr.s_addr = *(uint32_t *)host->h_addr;

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "Connect failed\n");
        close(sock);
        args->result = 1;
        return NULL;
    }

    printf("%s:%d connect\n", args->server.ip, args->server.port);

    char task[3 * sizeof(uint64_t)];
    memcpy(task, &args->begin, sizeof(uint64_t));
    memcpy(task + sizeof(uint64_t), &args->end, sizeof(uint64_t));
    memcpy(task + 2 * sizeof(uint64_t), &args->mod, sizeof(uint64_t));

    if (send(sock, task, sizeof(task), 0) < 0) {
        fprintf(stderr, "Send failed\n");
        close(sock);
        args->result = 1;
        return NULL;
    }

    printf("%s:%d send: %" PRIu64 " %" PRIu64 " %" PRIu64 "\n",
           args->server.ip, args->server.port, args->begin, args->end, args->mod);

    uint64_t answer;
    if (recv(sock, &answer, sizeof(answer), 0) <= 0) {
        fprintf(stderr, "Recv failed\n");
        close(sock);
        args->result = 1;
        return NULL;
    }

    printf("%s:%d answer: %" PRIu64 "\n", args->server.ip, args->server.port, answer);
    args->result = answer;
    close(sock);
    return NULL;
}

int main(int argc, char **argv) {
    uint64_t k = -1;
    uint64_t mod = -1;
    char servers_file[256] = {0};

    while (true) {
        static struct option options[] = {
            {"k", required_argument, 0, 0},
            {"mod", required_argument, 0, 0},
            {"servers", required_argument, 0, 0},
            {0, 0, 0, 0}
        };
        int option_index = 0;
        int c = getopt_long(argc, argv, "", options, &option_index);
        if (c == -1) break;

        switch (c) {
            case 0:
                switch (option_index) {
                    case 0:
                        if (!ConvertStringToUI64(optarg, &k)) return 1;
                        break;
                    case 1:
                        if (!ConvertStringToUI64(optarg, &mod)) return 1;
                        break;
                    case 2:
                        strncpy(servers_file, optarg, sizeof(servers_file) - 1);
                        break;
                    default:
                        printf("Unknown option index: %d\n", option_index);
                }
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }

    if (k == -1 || mod == -1 || !strlen(servers_file)) {
        fprintf(stderr, "Usage: %s --k 10 --mod 13 --servers servers.txt\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(servers_file, "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    int servers_num = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) servers_num++;
    rewind(file);

    struct Server *servers = malloc(sizeof(struct Server) * servers_num);
    for (int i = 0; i < servers_num; i++) {
        if (fgets(line, sizeof(line), file)) {
            sscanf(line, "%254[^:]:%d", servers[i].ip, &servers[i].port);
        }
    }
    fclose(file);

    pthread_t threads[servers_num];
    struct ThreadArgs targs[servers_num];

    uint64_t base = k / servers_num;
    uint64_t rem = k % servers_num;

    for (int i = 0; i < servers_num; i++) {
        targs[i].server = servers[i];
        targs[i].mod = mod;
        targs[i].begin = i * base + (i < rem ? i : rem) + 1;
        targs[i].end = targs[i].begin + base + (i < rem ? 1 : 0);
    }

    for (int i = 0; i < servers_num; i++) {
        pthread_create(&threads[i], NULL, ThreadSend, &targs[i]);
    }

    uint64_t total = 1;
    for (int i = 0; i < servers_num; i++) {
        pthread_join(threads[i], NULL);
        total = (total * targs[i].result) % mod;
    }

    printf("\nResult: %" PRIu64 "\n", total);
    free(servers);
    return 0;
}