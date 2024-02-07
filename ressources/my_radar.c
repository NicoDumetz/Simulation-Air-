/*
** EPITECH PROJECT, 2023
** my radar project
** File description:
** my radar
*/

#include "../include/my_radar.h"

void pop_event(struct game *game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        if (event.type == sfEvtClosed || (event.type == sfEvtKeyPressed &&
        event.key.code == sfKeyEscape))
            sfRenderWindow_close(game->window);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyL)
            game->hit = game->hit == 1 ? 0 : 1;
    }
}

static void game_loop(struct game *game)
{
    while (sfRenderWindow_isOpen(game->window)) {
        pop_event(game);
        reset_tower_col(game);
        check_tower_col(game);
        check_colision_plane(game);
        sfRenderWindow_clear(game->window, sfBlack);
        display(game);
    }
}

int my_radar(char **settings)
{
    struct game game = set_game(settings);

    sfRenderWindow_setFramerateLimit(game.window, 60);
    game_loop(&game);
    sfRenderWindow_destroy(game.window);
    return 0;
}
