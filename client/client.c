/*
** EPITECH PROJECT, 2024
** bs_myFTP
** File description:
** client
*/

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int check_socket_creation(int port, int sock_fd)
{
    if (port == 0) {
        fprintf(stderr, "argument isn't a port");
        return 84;
    }
    if (sock_fd == -1) {
        fprintf(stderr, "socket creation failed");
        return 84;
    }
    return 0;
}

int connect_to_server(const char **av, struct sockaddr_in *sock_addr,
    struct in_addr *in_addr, int port)
{
    if (inet_aton(av[1], in_addr) == 0) {
        fprintf(stderr, "invalid ip adress");
        return 84;
    }
    sock_addr->sin_family = AF_INET;
    sock_addr->sin_addr.s_addr = atoi(inet_ntoa(*in_addr));
    sock_addr->sin_port = htons(port);
    return 0;
}

void read_server(int sock_fd)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (getline(&line, &len, stdin) > 0) {
        line[strlen(line) - 1] = '\0';
        send(sock_fd, line, strlen(line), 0);
        line[0] = '\0';
        read(sock_fd, line, 1024 - 1);
        printf("%s\n", line);
        line = NULL;
        printf("Enter the string : ");
    }
}

int client(const char **av)
{
    int port = atoi(av[2]);
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock_addr;
    struct in_addr in_addr;

    if (check_socket_creation(port, sock_fd) == 84)
        return 84;
    if (connect_to_server(av, &sock_addr, &in_addr, port) == 84)
        return 84;
    if ((connect(sock_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)))) {
        fprintf(stderr, "connection to server failed");
        return 84;
    }
    read_server(sock_fd);
    close(sock_fd);
    return 0;
}

int main(int ac, const char **av)
{
    if (ac != 3) {
        fprintf(stderr, "bad number of arguments");
        return 84;
    }
    return client(av);
}
