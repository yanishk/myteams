/*
** EPITECH PROJECT, 2024
** bs_myFTP_select
** File description:
** my
*/

    #include <stdbool.h>
    #include <netinet/ip.h>
    #include <sys/select.h>

#ifndef SERVER_H_
    #define SERVER_H_

static const int MAX_USER = 1024;

typedef struct clients_s {
    struct sockaddr_in sock_addr;
    int client_fd;
    bool username_entered;
    bool user_logged_in;
    bool has_been_closed;
    char *username;
} clients_t;

typedef struct server_s {
    struct sockaddr_in sock_addr;
    int port;
    int server_fd;
    int *fd_array;
    int size;
    int max_fd_set;
    fd_set readfds;
    clients_t **clients;
} server_t;

#endif /* !SERVER_H_ */
