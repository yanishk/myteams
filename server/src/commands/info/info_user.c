/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** info_user
*/

#include "my.h"

int info_user(const int client_fd, my_teams_t *teams)
{
    dprintf(client_fd, "%s%s\n%s\n%d\n%s", CODE_203, teams->new_user->uuid,
    teams->new_user->name, teams->new_user->is_logged, CODE_101);
    return WIN_CMD;
}
