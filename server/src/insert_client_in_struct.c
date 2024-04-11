/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** server
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "my.h"

int insert_client_in_struct(server_t *server, int client_fd)
{
    for (int i = 0; i != MAX_USER; i += 1) {
        if (server->clients[i]->client_fd == client_fd) {
            return i;
        }
    }
    for (int i = 0; i != MAX_USER; i += 1) {
        if (server->clients[i]->client_fd == 0) {
            server->clients[i]->client_fd = client_fd;
            return i;
        }
    }
    return 0;
}
