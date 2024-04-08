/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** main
*/

#include "my.h"
#include <stdio.h>
#include <string.h>
#include "teams.h"

void print_usage(void)
{
    puts("USAGE: ./myteams_server port");
    puts("port is the port number on which the server socket listens");
}

int main(int ac, char *const *av)
{
    if (ac != 2) {
        fprintf(stderr, "run ./myteams_server -help\n");
        return 84;
    }
    if (strcmp(av[1], "-help") == 0)
        print_usage();
    return server(av[1]);
}
