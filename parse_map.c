#include "cub3D.h"

void	parse_map(t_data *game, char *filename)
{
    int     fd;
    char    *line;
    int     i;
    int     j;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        write(1, "Error2\n", 7);
        exit(0);
    }
    /*parse NO ./path_to_the_north_texture
    SO ./path_to_the_south_texture
    WE ./path_to_the_west_texture
    EA ./path_to_the_east_texture
    F 220,100,0
    C 225,30,0*/
    for (int k = 0; k<6; k++){line = get_next_line(fd); game->gc = gc_insert(game->gc, line);}
    i = 0;
	line = get_next_line(fd);
	game->gc = gc_insert(game->gc, line);
    while (line)
    {
        j = 0;
        while (line[j])
        {
            if (line[j] == '1')
                game->map[i][j] = 1;
            else if (line[j] == '0')
                game->map[i][j] = 0;
            else if (line[j] == 'N')
            {
                game->map[i][j] = 0;
                game->start_pos[0] = j;
                game->start_pos[1] = i;
                game->start_dir[1] = -1;
            }
            else if (line[j] == 'E')
            {
                game->map[i][j] = 0;
                game->start_pos[0] = j;
                game->start_pos[1] = i;
                game->start_dir[0] = 1;
            }
            else if (line[j] == 'S')
            {
                game->map[i][j] = 0;
                game->start_pos[0] = j;
                game->start_pos[1] = i;
                game->start_dir[1] = 1;
            }
            else if (line[j] == 'W')
            {
                game->map[i][j] = 0;
                game->start_pos[0] = j;
                game->start_pos[1] = i;
                game->start_dir[0] = -1;
            }
            j++;
        }
        i++;
		line = get_next_line(fd);
		game->gc = gc_insert(game->gc, line);
    }
}