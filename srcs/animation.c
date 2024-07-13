#include "../includes/cub3d.h"

void handle_animation_state(t_data *game, struct s_animation *animation, t_animation_type type)
{
    render_image(game, (t_image *)(*animation).frames->content);
    if (game->time - game->animation_time > FPS)
    {
        animation->frames = (*animation).frames->next;
        game->animation_time = game->time;
    }
    if (animation->frames == animation->head)
    {
        if (type == CROWBAR)
            game->crowbar.state = IDLE;
        game->key.one = 0;
        game->left_click = 0;
    }
}

void handle_idle_state(t_data *game)
{
    if (game->crowbar.equiped)
    {
        render_image(game, (t_image *)game->crowbar.attack.head->content);
        collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS);
        if (game->left_click && !game->coll_h && !game->coll_v)
            game->crowbar.state = ATTACK;
        else if (game->left_click && (game->coll_h || game->coll_v))
            game->crowbar.state = ATTACK_HIT;
        else if (game->key.one)
            game->crowbar.state = HOLSTER;
    }
    else if (game->key.one)
        game->crowbar.state = DRAW;
}

void update_crowbar_state(t_data *game)
{
    if (game->crowbar.state == IDLE)
        handle_idle_state(game);
    else if (game->crowbar.state == DRAW)
    {
        handle_animation_state(game, &game->crowbar.draw, CROWBAR);
        game->crowbar.equiped = 1;
    }
    else if (game->crowbar.state == ATTACK)
        handle_animation_state(game, &game->crowbar.attack, CROWBAR);
    else if (game->crowbar.state == ATTACK_HIT)
        handle_animation_state(game, &game->crowbar.attack_hit, CROWBAR);
    else if (game->crowbar.state == HOLSTER)
    {
        handle_animation_state(game, &game->crowbar.holster, CROWBAR);
        game->crowbar.equiped = 0;
    }
}
