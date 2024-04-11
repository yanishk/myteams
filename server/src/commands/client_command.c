/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** client_command
*/

#include "my.h"

int quit_cmd(server_t *server, int client_fd, my_teams_t *)
{
    write(client_fd, QUIT_MSG, strlen(QUIT_MSG));
    printf("Client disconnected :\n");
    printf("IP : %s\n", inet_ntoa(server->sock_addr.sin_addr));
    printf("Port : %d\n", ntohs(server->sock_addr.sin_port));
    printf("User : %s\n\n", server->clients[server->user_index]->username);
    server->clients[server->user_index]->username = malloc(sizeof(char) * 1);
    server->clients[server->user_index]->is_connected = false;
    server->fd_array[server->user_index] = 0;
    close(client_fd);
    return WIN_CMD;
}

int noop_cmd(server_t *server, int client_fd, my_teams_t *)
{
    if (error_not_login(server, client_fd) != 0) {
        return ERR_CMD;
    }
    write(client_fd, CODE_200, strlen(CODE_200));
    return WIN_CMD;
}
