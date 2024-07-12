#include "../includes/cub3D.h"

void idle_state(t_data *game, long long cur_time)
{
	t_image *img;
	
	(void)cur_time;
	img = (t_image *)game->crowbar_attack_head->content;
    for (int i = 0; i < WIN_W; i++)
    {
        for (int j = 0; j < WIN_H; j++)
        {
            if (i < img->w && j < img->h)
            {
                unsigned int t = ((unsigned int *)img->addr)[j * img->w + i];
                if (t != TRANSPARENT_COLOR)
                    ((unsigned int *)game->img.addr)[j * WIN_W + i] = t;
            }
        }
    }
	collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS);
    if (game->left_click && !game->coll_h && !game->coll_v)
        game->crowbar_state = ATTACK;
    else if (game->left_click && (game->coll_h || game->coll_v))
        game->crowbar_state = ATTACK_HIT;
    else if (game->key.one)
        game->crowbar_state = DRAW;
}

void attack_state(t_data *game, long long cur_time)
{
    for (int i = 0; i < WIN_W; i++)
    {
        for (int j = 0; j < WIN_H; j++)
        {
            t_image *img = (t_image *)game->crowbar_attack->content;
            if (i < img->w && j < img->h)
            {
                unsigned int t = ((unsigned int *)img->addr)[j * img->w + i];
                if (t != TRANSPARENT_COLOR)
                    ((unsigned int *)game->img.addr)[j * WIN_W + i] = t;
            }
        }
    }
    if (cur_time - game->crowbar_attack_time > FPS)
    {
        game->crowbar_attack = game->crowbar_attack->next;
        game->crowbar_attack_time = cur_time;
    }
    if (game->crowbar_attack == game->crowbar_attack_head)
    {
        game->left_click = 0;
        game->crowbar_state = IDLE;
    }
}

void hit_state(t_data *game, long long cur_time)
{
    for (int i = 0; i < WIN_W; i++)
    {
        for (int j = 0; j < WIN_H; j++)
        {
            t_image *img = (t_image *)game->crowbar_attack_hit->content;
            if (i < img->w && j < img->h)
            {
                unsigned int t = ((unsigned int *)img->addr)[j * img->w + i];
                if (t != TRANSPARENT_COLOR)
                    ((unsigned int *)game->img.addr)[j * WIN_W + i] = t;
            }
        }
    }
    if (cur_time - game->crowbar_attack_hit_time > FPS)
    {
        game->crowbar_attack_hit = game->crowbar_attack_hit->next;
        game->crowbar_attack_hit_time = cur_time;
    }
    if (game->crowbar_attack_hit == game->crowbar_attack_hit_head)
    {
        game->left_click = 0;
        game->crowbar_state = IDLE;
    }
}

void draw_state(t_data *game, long long cur_time)
{
    for (int i = 0; i < WIN_W; i++)
    {
        for (int j = 0; j < WIN_H; j++)
        {
            t_image *img = (t_image *)game->crowbar_draw->content;
            if (i < img->w && j < img->h)
            {
                unsigned int t = ((unsigned int *)img->addr)[j * img->w + i];
                if (t != TRANSPARENT_COLOR)
                    ((unsigned int *)game->img.addr)[j * WIN_W + i] = t;
            }
        }
    }
    if (cur_time - game->crowbar_draw_time > FPS)
    {
        game->crowbar_draw = game->crowbar_draw->next;
        game->crowbar_draw_time = cur_time;
    }
    if (game->crowbar_draw == game->crowbar_draw_head)
    {
        game->key.one = 0;
        game->crowbar_state = IDLE;
    }
}

void update_crowbar_state(t_data *game, long long cur_time)
{
	static void (*crowbar_animations[])(t_data *, long long) = {
        idle_state,
		draw_state,
		attack_state,
		hit_state
    };
    crowbar_animations[game->crowbar_state](game, cur_time);
}