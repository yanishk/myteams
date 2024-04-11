/*
** EPITECH PROJECT, 2024
** bs_myFTP
** File description:
** client
*/

#include "client.h"

static int check_socket_creation(const int port, const int sock_fd)
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

static int connect_to_server(const char **av, struct sockaddr_in *sock_addr,
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

static int read_server(const int sock_fd, fd_set readfds)
{
    size_t len = 0;
    char *line = NULL;
    char *reponse = malloc(sizeof(char) * 1024);

    if (select(sock_fd + 1, &readfds, NULL, NULL, NULL) == -1) {
        fprintf(stderr, "select failed\n");
        return 1;
    }
    if (FD_ISSET(0, &readfds)) {
        if (getline(&line, &len, stdin) > 0) {
            line[strlen(line) - 1] = '\0';
            write(sock_fd, line, strlen(line));
        }
    }
    if (FD_ISSET(sock_fd, &readfds)) {
        if (read(sock_fd, reponse, 1024) <= 0)
            return 18;
        select_display_methode(reponse);
    }
    return 0;
}

static void send_initial_command(const int sock_fd)
{
    const char *initial_cmd = "";
    char buffer[1024];

    write(sock_fd, initial_cmd, strlen(initial_cmd));
    read(sock_fd, buffer, 1024 - 1);
}

static void client_loop(int sock_fd)
{
    fd_set readfds;

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(sock_fd, &readfds);
        FD_SET(0, &readfds);
        if (read_server(sock_fd, readfds) == 18)
            break;
    }
}

int client(const char **av)
{
    int port = atoi(av[2]);
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock_addr;
    struct in_addr in_addr;

    write(1, "Enter the command : ", strlen("Enter the command : "));
    if (check_socket_creation(port, sock_fd) == 84)
        return 84;
    if (connect_to_server(av, &sock_addr, &in_addr, port) == 84)
        return 84;
    if ((connect(sock_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)))) {
        fprintf(stderr, "connection to server failed");
        return 84;
    }
    send_initial_command(sock_fd);
    client_loop(sock_fd);
    close(sock_fd);
    return 0;
}

int check_args(int ac, const char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myteams_cli ip port\n");
        printf("\tip\tis the server ip address ");
        printf("on which the server socket listens\n");
        printf("\tport\tis the port number on which ");
        printf("the server socket listens\n");
        return 1;
    }
    return 0;
}

int main(int ac, const char **av)
{
    if (check_args(ac, av) != 0) {
        return 0;
    }
    if (ac != 3) {
        fprintf(stderr, "Bad number of arguments\n");
        return 84;
    }
    return client(av);
}
