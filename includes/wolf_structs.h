/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:57:11 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/04 19:06:29 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_STRUCTS_H
# define WOLF_STRUCTS_H
# include "wolf_lists.h"

typedef struct s_linked		t_linked;
typedef struct s_door_list	t_door_list;

typedef struct	s_ai
{
	double		dx;
	double		dy;
	double		length;
	double		dot_side;
	double		dot_front;
	double		speed;
	int			angle_side;
	int			angle_front;
	int			x_move;
	int			y_move;
}				t_ai;

typedef struct	s_convert
{
	Uint32		*pixels;
	Uint32		sa;
	Uint32		sb;
	Uint32		sc;
}				t_convert;

typedef struct	s_audio
{
	Mix_Music	*music;
	Mix_Chunk	**generics;
	Mix_Chunk	**g_screams;
	Mix_Chunk	**z_screams;
	Mix_Chunk	**g_alerts;
	Mix_Chunk	**z_alerts;
}				t_audio;

typedef struct	s_map
{
	int			width;
	int			height;
	int			**data;
}				t_map;

typedef struct	s_rgb
{
	Uint8		r;
	Uint8		g;
	Uint8		b;
}				t_rgb;

typedef	struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef	struct	s_pair
{
	int			x;
	int			y;
}				t_pair;

typedef struct	s_range
{
	int			low;
	int			high;
}				t_range;

typedef struct	s_decisions
{
	t_range		move;
	t_range		shoot;
	t_range		idle;
}				t_decisions;

typedef struct	s_draw_vars
{
	t_point		pos;
	t_point		transform;
	int			height;
	int			width;
	int			stripe;
	int			screen_x;
	int			d;
	int			screen_adj;
	double		inv_det;
	t_pair		start;
	t_pair		end;
	t_pair		tex;
	SDL_Color	rgb;
}				t_draw_vars;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		length;
	double		orig_x;
	double		orig_y;
	int			texture;
	int			drawn;
	int			enemy;
	int			move;
	int			shoot_ind;
	int			death_ind;
	int			moving;
	int			shooting;
	int			alive;
	int			dying;
	int			hp;
	int			pink;
	int			inventory;
	int			in_world;
	int			seen_player;
	int			zombie;
	int			blue;
	int			angle;
	int			init;
	int			can_alert;
	int			channel;
	t_decisions	decisions;
	t_draw_vars	*dv;
	t_point		dir;
	Uint32		time;
	Uint32		prev_time;
	Uint32		*pix;
}				t_sprite;

typedef	struct	s_enemy
{
	SDL_Surface	**forward;
	SDL_Surface	**forwardleft;
	SDL_Surface	**forwardright;
	SDL_Surface	**left;
	SDL_Surface	**right;
	SDL_Surface	**backright;
	SDL_Surface	**backleft;
	SDL_Surface	**back;
	SDL_Surface **shoot;
	SDL_Surface **death;
}				t_enemy;

typedef struct	s_textures
{
	SDL_Surface	**generics;
	SDL_Surface	**skybox;
	t_enemy		guard;
	t_enemy		zombie;
}				t_textures;

typedef	struct	s_player
{
	t_point		pos;
	t_point		dir;
	t_point		plane;
	Uint32		time;
	Uint32		prev_time;
	int			hp;
	int			firing;
	int			has_key;
	int			pos_count;
	double		prev_fire_time;
	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct	s_line
{
	int			height;
	int			start;
	int			end;
	double		hit_loc;
	double		wall_dist;
	int			tex_num;
	t_pair		tex;
}				t_line;

typedef struct	s_floor
{
	t_pair		tex;
	t_point		wall;
	t_point		current;
	t_pair		map;
	double		wall_dist;
	double		weight;
}				t_floor;

typedef struct	s_ray
{
	t_point		dir;
	t_pair		map;
	t_point		side_dist;
	t_point		delta_dist;
	t_pair		step;
	t_point		half;
	int			hit;
	int			side;
	t_line		line;
	t_floor		floor;
}				t_ray;

typedef struct	s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	SDL_Surface	*health;
	SDL_Surface	*gameover;
	SDL_Rect	health_rect;
	SDL_Rect	gameover_rect;
	t_textures	textures;
	Uint32		*tex_pix;
	Uint32		*screen_pix;
	Uint32		*sky_pix;
	t_rgb		pink;
	t_rgb		black;
}				t_sdl;

typedef struct	s_door
{
	double		prev_time;
	double		orig_time;
	double		time_scale;
	double		orig_scale;
	t_pair		map;
	int			value;
	int			open;
	int			close;
	int			hold;
	int			added;
}				t_door;

typedef struct	s_wolf
{
	t_linked	*enemies;
	t_linked	*e_tail;
	t_sprite	*sprite;
	t_sprite	***e_map;
	t_sprite	***collect;
	t_door		***doors;
	t_sprite	weapon;
	t_sprite	key;
	t_door_list	*open_doors;
	t_sdl		*sdl;
	t_player	player;
	t_map		*map;
	t_ray		*ray;
	t_audio		*audio;
	double		*zbuffer;
	double		*floor_dist_tab;
	double		accumulator;
	int			*sprite_order;
	double		*sprite_dist;
	int			total_sprites;
	int			player_seen;
	int			first_enemy_dead;
	int			quit;
}				t_wolf;
#endif
