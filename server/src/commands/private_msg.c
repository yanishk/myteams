/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** private_msg
*/

#include "my.h"

static int error_send_msg(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    user_t *new_user;

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (server->cmd_arg.tab[1] == NULL || server->cmd_arg.tab[2] == NULL) {
        dprintf(client_fd, "%s\n%s",
            "private_msg.c/error_send_msg : not enough argument", CODE_101);
        return ERR_CMD;
    }
    TAILQ_FOREACH(new_user, &teams->user_head, user_entries) {
        if (strcmp(server->cmd_arg.tab[1], new_user->uuid) == 0)
            return WIN_CMD;
    }
    dprintf(client_fd, "%s%s\n%s", CODE_401,
        server->clients[server->user_index]->my_uuid, CODE_101);
    return ERR_CMD;
}

int send_msg(server_t *server, const int client_fd, my_teams_t *teams)
{
    private_msg_t *priv_msg;

    if (error_send_msg(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    priv_msg = malloc(sizeof(private_msg_t));
    TAILQ_INSERT_TAIL(&teams->priv_msg_head, priv_msg, private_msg_entries);
    priv_msg->uuid_sender = server->clients[server->user_index]->my_uuid;
    priv_msg->uuid_other = server->cmd_arg.tab[1];
    priv_msg->body = server->cmd_arg.tab[2];
    dprintf(client_fd, "%s%s", CODE_200, CODE_101);
    return WIN_CMD;
}

static int error_disp_msg(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    user_t *new_user;

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (server->cmd_arg.tab[1] == NULL) {
        dprintf(client_fd, "%s\n",
            "private_msg.c/error_disp_msg : not enough argument");
        return ERR_CMD;
    }
    TAILQ_FOREACH(new_user, &teams->user_head, user_entries) {
        if (strcmp(server->cmd_arg.tab[1], new_user->uuid) == 0)
            return WIN_CMD;
    }
    dprintf(client_fd, "%s%s\n%s", CODE_401,
    server->clients[server->user_index]->my_uuid, CODE_101);
    return ERR_CMD;
}

int display_priv_msg(server_t *server, const int client_fd, my_teams_t *teams)
{
    private_msg_t *prv_msg;

    if (error_disp_msg(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    TAILQ_FOREACH(prv_msg, &teams->priv_msg_head, private_msg_entries) {
        if (strcmp(prv_msg->uuid_other, server->cmd_arg.tab[1]) == 0)
            dprintf(client_fd, "%s\n", prv_msg->body);
    }
    dprintf(client_fd, "%s%s", CODE_200, CODE_101);
    return WIN_CMD;
}
