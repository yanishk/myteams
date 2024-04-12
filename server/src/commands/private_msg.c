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
        dprintf(client_fd, "%s\n",
            "private_msg.c/error_send_msg : not enough argument");
        return ERR_CMD;
    }
    TAILQ_FOREACH(new_user, &teams->user_head, user_entries) {
        if (strcmp(server->cmd_arg.tab[1], new_user->uuid) == 0)
            return WIN_CMD;
    }
    dprintf(client_fd, "%s%s\n", CODE_401,
    server->clients[server->user_index]->my_uuid);
    return ERR_CMD;
}

static void fill_my_message(server_t *server, user_t *new_user)
{
    private_msg_t *prv_msg_me;

    if (strcmp(server->clients[server->user_index]->my_uuid,
        new_user->uuid) == 0) {
        prv_msg_me = malloc(sizeof(private_msg_t));
        if (TAILQ_EMPTY(&new_user->private_msg_head))
            TAILQ_INIT(&new_user->private_msg_head);
        TAILQ_INSERT_TAIL(&new_user->private_msg_head,
            prv_msg_me, private_msg_entries);
        prv_msg_me->body = server->cmd_arg.tab[2];
        prv_msg_me->uuid_other = server->cmd_arg.tab[1];
    }
}

static void fill_struct_privmsg(server_t *server, user_t *new_user)
{
    private_msg_t *prv_msg_other;

    fill_my_message(server, new_user);
    if (strcmp(server->clients[server->user_index]->my_uuid,
        new_user->uuid) == 0)
        return;
    if (strcmp(server->cmd_arg.tab[1], new_user->uuid) == 0) {
        prv_msg_other = malloc(sizeof(private_msg_t));
        if (TAILQ_EMPTY(&new_user->private_msg_head))
            TAILQ_INIT(&new_user->private_msg_head);
        TAILQ_INSERT_TAIL(&new_user->private_msg_head,
            prv_msg_other, private_msg_entries);
        prv_msg_other->body = server->cmd_arg.tab[2];
        prv_msg_other->uuid_other =
            server->clients[server->user_index]->my_uuid;
    }
}

int send_msg(server_t *server, const int client_fd, my_teams_t *teams)
{
    user_t *new_user;

    if (error_send_msg(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    TAILQ_FOREACH(new_user, &teams->user_head, user_entries) {
        fill_struct_privmsg(server, new_user);
    }
    dprintf(client_fd, "%s", CODE_200);
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
    dprintf(client_fd, "%s%s\n", CODE_401,
    server->clients[server->user_index]->my_uuid);
    return ERR_CMD;
}

int display_priv_msg(server_t *server, const int client_fd, my_teams_t *teams)
{
    private_msg_t *prv_msg;

    if (error_disp_msg(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    TAILQ_FOREACH(prv_msg, &teams->new_user->private_msg_head,
        private_msg_entries) {
        if (strcmp(prv_msg->uuid_other, server->cmd_arg.tab[1]) == 0)
            dprintf(client_fd, "%s\n", prv_msg->body);
    }
    dprintf(client_fd, "%s", CODE_200);
    return WIN_CMD;
}
