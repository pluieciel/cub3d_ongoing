/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:07:36 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 17:22:28 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	destroy_animation(t_data *game, t_animation *animation)
{
	t_list	*current;
	t_image	*img;

	if (animation->frames)
	{
		current = animation->frames;
		while (current)
		{
			img = (t_image *)current->content;
			if (img->ptr)
				mlx_destroy_image(game->mlx_ptr, img->ptr);
			current = current->next;
			if (current == animation->frames)
				break ;
		}
	}
}

void	destroy_animations(t_data *game)
{
	destroy_animation(game, &game->crowbar.draw);
	destroy_animation(game, &game->crowbar.holster);
	destroy_animation(game, &game->crowbar.attack);
	destroy_animation(game, &game->crowbar.attack_hit);
	destroy_animation(game, &game->handgun.draw);
	destroy_animation(game, &game->handgun.holster);
	destroy_animation(game, &game->handgun.shoot);
	destroy_animation(game, &game->shotgun.draw);
	destroy_animation(game, &game->shotgun.holster);
	destroy_animation(game, &game->shotgun.shoot);
}

int	handle_animation_state(t_data *game, t_animation *animation,
		__uint64_t delay)
{
	render_image(game, (t_image *)(*animation).frames->content, 0, 0);
	if (game->time - game->animation_time > delay)
	{
		animation->frames = (*animation).frames->next;
		game->animation_time = game->time;
		if (animation->frames == animation->head)
		{
			game->left_click = 0;
			return (1);
		}
	}
	return (0);
}

void	update_animation(t_data *game)
{
	if (game->crowbar.state != NONE)
		update_crowbar_state(game);
	else if (game->handgun.state != NONE)
		update_handgun_state(game);
	else if (game->shotgun.state != NONE)
		update_shotgun_state(game);
}
