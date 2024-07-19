/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:07:36 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/19 22:14:42 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_animation_state(t_data *game, struct s_animation *animation,
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
