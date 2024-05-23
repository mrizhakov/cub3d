#include "../cub3d.h"

void	ft_animation(void *param)
{
	t_game	*game_data;
	int		i;

	game_data = (t_game *)param;
	if (mlx_get_time() - game_data->animat_time > 0.5)
	{
		i = 0;
		while (game_data->sprites[i].texture)
		{
			if (game_data->sprites[i].texture == TEX_MUSHR)
				game_data->sprites[i].texture = TEX_MUSHR_2;
			else
				game_data->sprites[i].texture = TEX_MUSHR;
			i++;
		}
		i = 0;
		while (game_data->doors[i].texture)
		{
			if (game_data->doors[i].isopen && game_data->doors[i]. texture < TEX_DOOR_OP)
				game_data->doors[i].texture++;
			else if (!game_data->doors[i].isopen && game_data->doors[i]. texture > TEX_DOOR_CL)
				game_data->doors[i].texture--;
			i++;
		}
		game_data->animat_time = mlx_get_time();
		update_pos(game_data);
	}
}

void ft_keyboad_hook(void* param)
{
    t_game *game_data = param;

    if (mlx_is_key_down(game_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game_data->mlx);
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_W))
        game_data->player_walk_dir = 1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_S))
        game_data->player_walk_dir = -1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_A))
        game_data->player_strafe_dir = -1;
    if (mlx_is_key_down(game_data->mlx, MLX_KEY_D))
        game_data->player_strafe_dir = 1;
    if (mlx_is_key_down(game_data->mlx, MLX_KEY_LEFT))
		game_data->player_turn_dir = -1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_RIGHT))
		game_data->player_turn_dir = 1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_E))
		open_door(game_data);
		// printf("Action key triggered\n");
    if (game_data->player_walk_dir != 0 || game_data->player_turn_dir != 0 || game_data->player_strafe_dir != 0)
        update_pos(game_data);
}

void ft_cursor_hook(float xpos, float ypos, void* param)
{
	t_point	cursor;
	t_game	*game_data;

	cursor = ((t_game *)param)->cursor;
	game_data = (t_game *)param;
	if (cursor.x == 0)
	{
		game_data->cursor.x = xpos;
		return ;
	}
	if (cursor.x > xpos)
		game_data->player_turn_dir = -1;
	else if (cursor.x < xpos)
		game_data->player_turn_dir = 1;
	game_data->cursor.x = xpos;
	update_pos(game_data);
	(void)ypos;
}
