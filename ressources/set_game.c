/*
** EPITECH PROJECT, 2023
** set all
** File description:
** set game
*/

#include "../include/my_radar.h"

static void set_background(struct game *game)
{
    game->background.texture = sfTexture_createFromFile("./sprite/maptest.jpg",
    NULL);
    game->background.sprite = sfSprite_create();
    game->background.pos = (sfVector2f){0, 0};
    game->background.scale = (sfVector2f){0.8, 0.9};
    sfSprite_setScale(game->background.sprite, game->background.scale);
    sfSprite_setTexture(game->background.sprite, game->background.texture,
    sfTrue);
    sfSprite_setPosition(game->background.sprite, game->background.pos);
}

static void set_hitbox_tower(struct game *game, int j, int i, char **settings)
{
    sfVector2f ori = sfSprite_getOrigin(game->tower[i].sprite);
    sfVector2f posi = sfSprite_getPosition(game->tower[i].sprite);
    sfVector2f sca = sfSprite_getScale(game->tower[i].sprite);

    game->tower[i].hitbox.circle = sfCircleShape_create();
    game->tower[i].hitbox.radius = my_getnbr(settings[j + 3]) * (1920 / 100);
    sfCircleShape_setRadius(game->tower[i].hitbox.circle, game->tower[i].
    hitbox.radius);
    game->tower[i].hitbox.pos.x = posi.x - ori.x * sca.x + (ori.x * 2 * sca.x
    - game->tower[i].hitbox.radius * 2) / 2;
    game->tower[i].hitbox.pos.y = posi.y - ori.y * sca.y + (ori.y * 2 * sca.y
    - game->tower[i].hitbox.radius * 2) / 2;
    sfCircleShape_setPosition(game->tower[i].hitbox.circle, game->tower
    [i].hitbox.pos);
    sfCircleShape_setOutlineThickness(game->tower[i].hitbox.circle, 1.0f);
    sfCircleShape_setOutlineColor(game->tower[i].hitbox.circle, sfWhite);
    sfCircleShape_setFillColor(game->tower[i].hitbox.circle, (sfColor){0,
    0, 0, 0});
}

static int set_alltower(struct game *game, char **settings, sfTexture
    *texture, int i)
{
    int j = i;
    sfVector2u textureSize = sfTexture_getSize(texture);
    sfVector2f origin = {(float)textureSize.x / 2, (float)textureSize.y / 2};

    for (i = 0; game->tower[i].sprite; i++);
    game->tower[i].sprite = sfSprite_create();
    game->tower[i].pos = (sfVector2f){my_getnbr(settings[j + 1]),
    my_getnbr(settings[j + 2])};
    game->tower[i].scale = (sfVector2f){0.1, 0.1};
    sfSprite_setOrigin(game->tower[i].sprite, origin);
    sfSprite_setScale(game->tower[i].sprite, game->tower[i].scale);
    sfSprite_setTexture(game->tower[i].sprite, texture, sfTrue);
    sfSprite_setPosition(game->tower[i].sprite, game->tower[i].pos);
    set_hitbox_tower(game, j, i, settings);
    return 4;
}

static int set_hitbox_plane(struct game *game, int i)
{
    game->plane[i].angle = atan2(game->plane[i].posfin.y -
    game->plane[i].pos.y, game->plane[i].posfin.x -
    game->plane[i].pos.x) * 180 / PI;
    sfSprite_setRotation(game->plane[i].sprite, game->plane[i].angle);
    sfSprite_setPosition(game->plane[i].sprite, game->plane[i].pos);
    game->plane[i].hitbox.rect = sfRectangleShape_create();
    game->plane[i].hitbox.size = (sfVector2f){20.0f, 20.0f};
    sfRectangleShape_setSize(game->plane[i].hitbox.rect, game->plane[i].
    hitbox.size);
    sfRectangleShape_setPosition(game->plane[i].hitbox.rect, game->plane
    [i].pos);
    sfRectangleShape_setOutlineThickness(game->plane[i].hitbox.rect, 1.0f);
    sfRectangleShape_setOutlineColor(game->plane[i].hitbox.rect, sfWhite);
    sfRectangleShape_setFillColor(game->plane[i].hitbox.rect, (sfColor)
    {0, 0, 0, 0});
    sfRectangleShape_rotate(game->plane[i].hitbox.rect, game->plane[i].angle);
}

static int set_allplane(struct game *game, char **settings, sfTexture
    *texture, int i)
{
    int j = i;

    for (i = 0; game->plane[i].sprite; i++);
    game->plane[i].posfin = (sfVector2f){my_getnbr(settings[j + 3]),
    my_getnbr(settings[j + 4])};
    game->plane[i].speed = my_getnbr(settings[j + 5]);
    game->plane[i].delay = my_getnbr(settings[j + 6]);
    game->plane[i].sprite = sfSprite_create();
    game->plane[i].pos = (sfVector2f){my_getnbr(settings[j + 1]),
    my_getnbr(settings[j + 2])};
    game->plane[i].scale = (sfVector2f){0.08, 0.08};
    game->plane[i].clock = sfClock_create();
    game->plane[i].actif = game->plane[i].delay == 0 ? 1 : 0;
    sfSprite_setScale(game->plane[i].sprite, game->plane[i].scale);
    sfSprite_setTexture(game->plane[i].sprite, texture, sfTrue);
    set_hitbox_plane(game, i);
    return 7;
}

static void set_text_fps(struct game *game)
{
    game->frame = sfText_create();
    game->clock_fps = sfClock_create();
    sfText_setFont(game->frame, game->font);
    sfText_setCharacterSize(game->frame, 30);
    sfText_setPosition(game->frame, (sfVector2f){1700, 130});
    sfText_setFillColor(game->frame, sfWhite);
}

static void set_text(struct game *game)
{
    game->font = sfFont_createFromFile("font/arial.ttf");
    game->time = sfText_create();
    sfText_setFont(game->time, game->font);
    sfText_setCharacterSize(game->time, 30);
    sfText_setPosition(game->time, (sfVector2f){1700, 10});
    sfText_setFillColor(game->time, sfWhite);
    game->onspr = sfText_create();
    sfText_setFont(game->onspr, game->font);
    sfText_setCharacterSize(game->onspr, 30);
    sfText_setPosition(game->onspr, (sfVector2f){1700, 50});
    sfText_setFillColor(game->onspr, sfWhite);
    sfText_setString(game->onspr, "Sprite: ON");
    game->onhit = sfText_create();
    sfText_setFont(game->onhit, game->font);
    sfText_setCharacterSize(game->onhit, 30);
    sfText_setPosition(game->onhit, (sfVector2f){1700, 90});
    sfText_setFillColor(game->onhit, sfWhite);
    sfText_setString(game->onhit, "Hitbox: ON");
    set_text_fps(game);
}

void set_plane_tower(struct game *game, char **settings)
{
    sfTexture *texture = sfTexture_createFromFile
    ("./sprite/plane.png", NULL);
    sfTexture *texture2 = sfTexture_createFromFile
    ("./sprite/tower.png", NULL);

    for (int i = 0; i < game->nbr_plane; i++)
        game->plane[i].sprite = NULL;
    for (int i = 0; i < game->nbr_tower; i++)
        game->tower[i].sprite = NULL;
    for (int i = 0; settings[i];) {
        if (settings[i][0] == 'A')
            i += set_allplane(game, settings, texture, i);
        else
            i += set_alltower(game, settings, texture2, i);
    }
}

struct game set_game(char **settings)
{
    struct game game;

    game.mode = (sfVideoMode){1920, 1080, 32};
    game.window = sfRenderWindow_create(game.mode, "My_Radar",
    sfResize | sfClose, NULL);
    game.hit = 1;
    game.spr = 1;
    set_text(&game);
    game.nbr_plane = compt_plane(settings);
    game.nbr_tower = compt_tower(settings);
    game.plane = malloc(sizeof(sprite) * (game.nbr_plane + 1));
    game.tower = malloc(sizeof(sprite) * (game.nbr_tower + 1));
    set_background(&game);
    set_plane_tower(&game, settings);
    free_array(settings);
    game.clock = sfClock_create();
    return game;
}
