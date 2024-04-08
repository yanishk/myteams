/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** save_database
*/

#include <unistd.h>
#include <fcntl.h>
#include "teams.h"

static void save_users(const my_teams_t teams)
{
    int fd = open("database", O_WRONLY | O_TRUNC | O_CREAT, 422);
    user_t *np_user;
    team_belong_t *np_team_belong;

    dprintf(fd, "struct user:\n");
    TAILQ_FOREACH(np_user, &teams.user_head, user_entries) {
        dprintf(fd, "user:\n");
        dprintf(fd, "\tuuid=%s\n", np_user->uuid);
        dprintf(fd, "\tname=%s\n", np_user->name);
        dprintf(fd, "\tteams_uuid=");
        TAILQ_FOREACH(np_team_belong, &np_user->team_belong_head,
            belong_entries) {
            dprintf(fd, "%s", np_team_belong->uuid);
            if (TAILQ_NEXT(np_team_belong, belong_entries) != NULL)
                dprintf(fd, ",");
            if (TAILQ_NEXT(np_team_belong, belong_entries) == NULL)
                dprintf(fd, "\n");
        }
    }
    close(fd);
}

void save_database(const my_teams_t teams)
{
    save_users(teams);
}
