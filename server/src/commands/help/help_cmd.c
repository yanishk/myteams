/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** help_cmd
*/

#include "my.h"

static void print_all_help(const int client_fd)
{
    dprintf(client_fd, "%s", CODE_214);
    for (size_t i = 0; i < NB_CMD; i++) {
        dprintf(client_fd, "%s", help_msg[i]);
    }
    dprintf(client_fd, "%s", CODE_214);
}

static int cmd_help_msg(char *cmd, const int client_fd)
{
    for (size_t i = 0; i < NB_CMD; i++) {
        if (strcmp(cmd, cmd_lst[i]) == 0) {
            dprintf(client_fd, "%s", CODE_214);
            dprintf(client_fd, "%s", help_msg[i]);
            dprintf(client_fd, "%s", CODE_214);
            return WIN_CMD;
        }
    }
    dprintf(client_fd, "%s", ERR_BAD_ARG);
    return ERR_CMD;
}

int help_cmd(server_t *server, const int client_fd, my_teams_t *)
{
    if (server->cmd_arg.len == 1) {
        print_all_help(client_fd);
        return WIN_CMD;
    } else {
        return cmd_help_msg(server->cmd_arg.tab[1], client_fd);
    }
}
