#include "../includes/cub3D.h"

void handle_animation_state(t_data *game, struct s_animation *animation, t_animation_type type, __uint64_t delay)
{
    render_image(game, (t_image *)(*animation).frames->content);
    if (game->time - game->animation_time > delay)
    {
        animation->frames = (*animation).frames->next;
        game->animation_time = game->time;
    }
    if (animation->frames == animation->head)
    {
        if (type == CROWBAR)
            game->crowbar.state = CROWBAR_IDLE;
        else if (type == HANDGUN)
            game->handgun.state = HANDGUN_IDLE;
        game->key.one = 0;
        game->key.two = 0;
        game->left_click = 0;
    }
}

void handle_crowbar_idle_state(t_data *game)
{
    if (game->crowbar.equiped)
    {
        render_image(game, (t_image *)game->crowbar.attack.head->content);
        collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS);
        if (game->left_click && !game->coll_h && !game->coll_v)
            game->crowbar.state = CROWBAR_ATTACK;
        else if (game->left_click && (game->coll_h || game->coll_v))
            game->crowbar.state = CROWBAR_ATTACK_HIT;
        else if (game->key.one || game->key.two)
            game->crowbar.state = CROWBAR_HOLSTER;
    }
    else if (game->key.one)
        game->crowbar.state = CROWBAR_DRAW;
}

void handle_handgun_idle_state(t_data *game)
{
    if (game->handgun.equiped)
    {
        render_image(game, (t_image *)game->handgun.shoot.head->content);
        collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS);
        if (game->left_click)
            game->handgun.state = HANDGUN_SHOOT;
        else if (game->key.two || game->key.one)
            game->handgun.state = HANDGUN_HOLSTER;
    }
    else if (game->key.two)
        game->handgun.state = HANDGUN_DRAW;
}

void update_crowbar_state(t_data *game)
{
    if (game->crowbar.state == CROWBAR_IDLE)
        handle_crowbar_idle_state(game);
    else if (game->crowbar.state == CROWBAR_DRAW)
    {
        handle_animation_state(game, &game->crowbar.draw, CROWBAR, FPS);
        game->crowbar.equiped = 1;
    }
    else if (game->crowbar.state == CROWBAR_ATTACK)
        handle_animation_state(game, &game->crowbar.attack, CROWBAR, FPS);
    else if (game->crowbar.state == CROWBAR_ATTACK_HIT)
        handle_animation_state(game, &game->crowbar.attack_hit, CROWBAR, FPS);
    else if (game->crowbar.state == CROWBAR_HOLSTER)
    {
        handle_animation_state(game, &game->crowbar.holster, CROWBAR, FPS);
        game->crowbar.equiped = 0;
    }
}

void update_handgun_state(t_data *game)
{
    if (game->handgun.state == HANDGUN_IDLE)
        handle_handgun_idle_state(game);
    else if (game->handgun.state == HANDGUN_DRAW)
    {
        handle_animation_state(game, &game->handgun.draw, HANDGUN, FPS);
        game->handgun.equiped = 1;
    }
    else if (game->handgun.state == HANDGUN_SHOOT)
        handle_animation_state(game, &game->handgun.shoot, HANDGUN, FPS / 2);
    else if (game->handgun.state == HANDGUN_HOLSTER)
    {
        handle_animation_state(game, &game->handgun.holster, HANDGUN, FPS);
        game->handgun.equiped = 0;
    }
}
