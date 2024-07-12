#include "../includes/cub3D.h"

void handle_animation_state(t_data *game, struct s_animation *animation)
{
    render_image(game, (t_image *)(*animation).frames->content);
    if (game->time - game->crowbar.time > FPS)
    {
        animation->frames = (*animation).frames->next;
        game->crowbar.time = game->time;
    }
    if (animation->frames == animation->head)
    {
        game->crowbar.state = IDLE;
        game->key.one = 0;
        game->left_click = 0;
    }
}

void handle_idle_state(t_data *game)
{
    render_image(game, (t_image *)game->crowbar.attack.head->content);
    collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS);
    if (game->left_click && !game->coll_h && !game->coll_v)
        game->crowbar.state = ATTACK;
    else if (game->left_click && (game->coll_h || game->coll_v))
        game->crowbar.state = ATTACK_HIT;
    else if (game->key.one)
        game->crowbar.state = DRAW;
}

void update_crowbar_state(t_data *game)
{
    if (game->crowbar.state == IDLE)
        handle_idle_state(game);
    else if (game->crowbar.state == DRAW)
        handle_animation_state(game, &game->crowbar.draw);
    else if (game->crowbar.state == ATTACK)
        handle_animation_state(game, &game->crowbar.attack);
    else if (game->crowbar.state == ATTACK_HIT)
        handle_animation_state(game, &game->crowbar.attack_hit);
}
