/*
** EPITECH PROJECT, 2024
** bs_myFTP
** File description:
** client
*/

#include "client.h"

static int check_socket_creation(int port, int sock_fd)
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

static void display_msg(char *msg, int nb)
{
    char **tab = word_array(msg, "\n");

    if (nb == 1) {
        client_event_logged_in("[uuid client]", "[nom client]");
    }
    if (nb == 2) {
        client_print_user(tab[2], tab[1], 1);
    }
    if (nb == 3 || nb == 4) {
        client_error_unauthorized();
    }
    if (nb == 0) {
        printf("200 tt est ok\n");
    }
    if (nb == 5) {
        client_error_already_exist();
    }
}

static void select_display_methode(char *msg)
{
    char *new_msg = strdup(msg);
    char *first_ligne = word_array(new_msg, "\n")[0];
    char *first_word = word_array(first_ligne, " ")[0];

    for (int i = 0; i < NB_CODE; i++) {
        if (strcmp(code_lst[i], first_word) == 0) {
            display_msg(strdup(msg), i);
        }
    }
}

static void read_server(int sock_fd)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) > 0) {
        line[strlen(line) - 1] = '\0';
        write(sock_fd, line, strlen(line));
        line = malloc(sizeof(char) * 1024);
        read(sock_fd, line, 1024 - 1);
        select_display_methode(line);
        line = NULL;
        printf("Enter the string : ");
    }
}

void send_initial_command(int sock_fd)
{
    const char *initial_cmd = "";
    char buffer[1024];

    write(sock_fd, initial_cmd, strlen(initial_cmd));
    read(sock_fd, buffer, 1024 - 1);
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
    printf("Enter the string : ");
    send_initial_command(sock_fd);
    read_server(sock_fd);
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
        fprintf(stderr, "bad number of arguments");
        return 84;
    }
    client_print_user("be41cd7e-37ea-4a54-a8fb-be87222903ab", "mathis", 1);
    return client(av);
}
