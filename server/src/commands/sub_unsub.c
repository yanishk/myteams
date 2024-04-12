/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** sub_unsub
*/

#include "my.h"

static int already_subbed(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    team_belong_t *own_team;

    TAILQ_FOREACH(own_team,
        &teams->new_user->team_belong_head, belong_entries) {
        if (strcmp(server->cmd_arg.tab[1], own_team->uuid) == 0) {
            dprintf(client_fd, "%s\n",
                "sub_unsub.c/error_sub_team : already subbed");
            return ERR_CMD;
        }
    }
    return WIN_CMD;
}

static int global_error(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (server->cmd_arg.tab[1] == NULL) {
        dprintf(client_fd, "%s\n",
            "sub_unsub.c/error_sub_team : not enough argument");
        return ERR_CMD;
    }
    if (already_subbed(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    return WIN_CMD;
}

static int error_sub_team(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    team_t *team_exist;

    if (global_error(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    TAILQ_FOREACH(team_exist, &teams->team_head, team_entries) {
        if (strcmp(team_exist->uuid, server->cmd_arg.tab[1]) == 0)
            return WIN_CMD;
    }
    dprintf(client_fd, "%s",
        "sub_unsub.c/error_sub_team : specified team does not exist\n");
    return ERR_CMD;
}

static void fill_user_subbed(server_t *server, user_t *new_user)
{
    team_belong_t *my_team;

    if (strcmp(new_user->uuid,
        server->clients[server->user_index]->my_uuid) == 0) {
        my_team = malloc(sizeof(team_belong_t));
        if (TAILQ_EMPTY(&new_user->team_belong_head))
            TAILQ_INIT(&new_user->team_belong_head);
        TAILQ_INSERT_TAIL(&new_user->team_belong_head,
            my_team, belong_entries);
        my_team->uuid = server->cmd_arg.tab[1];
    }
}

int sub_team(server_t *server, const int client_fd, my_teams_t *teams)
{
    user_t *new_user;

    if (error_sub_team(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    for ((new_user) = ((&teams->user_head)->tqh_first);
        (new_user); (new_user) = ((new_user)->user_entries.tqe_next)) {
        fill_user_subbed(server, new_user);
    }
    dprintf(client_fd, "%s",
        "sub_unsub.c/sub_team : Succesfully joined the team\n");
    return WIN_CMD;
}

static int disp_my_teams(const int client_fd, my_teams_t *teams)
{
    team_belong_t *my_teams;
    team_t *all_teams;

    TAILQ_FOREACH(my_teams, &teams->new_user->team_belong_head,
        belong_entries) {
        TAILQ_FOREACH(all_teams, &teams->team_head, team_entries) {
            if (strcmp(my_teams->uuid, all_teams->uuid) == 0) {
                dprintf(client_fd, "%s\n", all_teams->name);
                dprintf(client_fd, "%s\n", all_teams->description);
                dprintf(client_fd, "%s\n", all_teams->uuid);
            }
        }
    }
    return WIN_CMD;
}

static int is_in_team(server_t *server, const int client_fd, my_teams_t *teams)
{
    team_belong_t *my_teams;

    TAILQ_FOREACH(my_teams, &teams->new_user->team_belong_head,
        belong_entries) {
        if (strcmp(my_teams->uuid, server->cmd_arg.tab[1]) == 0)
            return WIN_CMD;
    }
    dprintf(client_fd,
        "sub_unsub.c/sub_team : You are not allowed to see this team\n");
    return ERR_CMD;
}

static int disp_all_team_user(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    user_t *all_user;
    team_belong_t *their_teams;

    if (is_in_team(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    TAILQ_FOREACH(all_user, &teams->user_head, user_entries) {
        TAILQ_FOREACH(their_teams, &all_user->team_belong_head,
            belong_entries) {
            if (strcmp(their_teams->uuid, server->cmd_arg.tab[1]) == 0) {
                dprintf(client_fd, "%s\n", all_user->name);
                dprintf(client_fd, "%s\n", all_user->uuid);
            }
        }
    }
    return WIN_CMD;
}

int disp_subscribed(server_t *server, const int client_fd, my_teams_t *teams)
{
    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (server->cmd_arg.tab[1] == NULL)
        return disp_my_teams(client_fd, teams);
    return disp_all_team_user(server, client_fd, teams);
}
