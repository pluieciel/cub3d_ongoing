#include "../includes/cub3D.h"

int handle_animation_state(t_data *game, struct s_animation *animation, __uint64_t delay)
{
    render_image(game, (t_image *)(*animation).frames->content, 0, 0);
    if (game->time - game->animation_time > delay)
    {
        animation->frames = (*animation).frames->next;
        game->animation_time = game->time;
        if (animation->frames == animation->head)
        {
            game->left_click = 0;
            return 1;
        }
    }
    return 0; 
}

void handle_crowbar_idle_state(t_data *game)
{
    if (game->crowbar.equiped)
    {
        render_image(game, (t_image *)game->crowbar.attack.head->content, 0, 0);
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
        render_image(game, (t_image *)game->handgun.shoot.head->content, 0, 0);
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
    game->crowbar.completed  = 0;
    if (game->crowbar.state == CROWBAR_IDLE)
        handle_crowbar_idle_state(game);
    else if (game->crowbar.state == CROWBAR_DRAW)
    {
        game->crowbar.completed = handle_animation_state(game, &game->crowbar.draw, FPS);
        if (game->crowbar.completed)
            game->crowbar.equiped = 1;
    }
    else if (game->crowbar.state == CROWBAR_ATTACK)
        game->crowbar.completed = handle_animation_state(game, &game->crowbar.attack, FPS);
    else if (game->crowbar.state == CROWBAR_ATTACK_HIT)
        game->crowbar.completed = handle_animation_state(game, &game->crowbar.attack_hit, FPS);
    else if (game->crowbar.state == CROWBAR_HOLSTER)
    {
        game->crowbar.completed = handle_animation_state(game, &game->crowbar.holster, FPS);
        if (game->crowbar.completed)
        {
            game->crowbar.equiped = 0;
            if (game->key.two)
            {
                game->crowbar.state = CROWBAR_NONE;
                game->handgun.state = HANDGUN_DRAW;
            }
        }
    }
    if (game->crowbar.completed)
    {
        if (game->crowbar.state != CROWBAR_NONE)
        {
            game->crowbar.state = CROWBAR_IDLE;
            game->key.two = 0;
            game->key.one = 0;
        }
    }
}

void update_handgun_state(t_data *game)
{
    game->handgun.completed = 0;
    if (game->handgun.state == HANDGUN_IDLE)
        handle_handgun_idle_state(game);
    else if (game->handgun.state == HANDGUN_DRAW)
    {
        game->handgun.completed  = handle_animation_state(game, &game->handgun.draw, FPS);
        if (game->handgun.completed)
            game->handgun.equiped = 1;
    }
    else if (game->handgun.state == HANDGUN_SHOOT)
        game->handgun.completed = handle_animation_state(game, &game->handgun.shoot, FPS / 2);
    else if (game->handgun.state == HANDGUN_HOLSTER)
    {
        game->handgun.completed = handle_animation_state(game, &game->handgun.holster, FPS);
        if (game->handgun.completed)
        {
            game->handgun.equiped = 0;
            if (game->key.one)
            {
                game->handgun.state = HANDGUN_NONE;
                game->crowbar.state = CROWBAR_DRAW;
            }
        }
    }
    if (game->handgun.completed)
    {
        if (game->handgun.state != HANDGUN_NONE)
        {
            game->handgun.state = HANDGUN_IDLE;
            game->key.two = 0;
            game->key.one = 0;
        }
    }
}
