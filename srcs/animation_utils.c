#include "../includes/cub3d.h"

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

void update_animation(t_data *game)
{
	if (game->crowbar.state != NONE)
		update_crowbar_state(game);
	else if (game->handgun.state != NONE)
		update_handgun_state(game);
}
