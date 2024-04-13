/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** info_user
*/

#include "my.h"

int info_user(const int client_fd, my_teams_t *teams)
{
    dprintf(client_fd, "%s\n", teams->new_user->uuid);
    dprintf(client_fd, "%s\n", teams->new_user->name);
    dprintf(client_fd, "%d\n", teams->new_user->is_logged);
    return WIN_CMD;
}
