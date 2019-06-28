/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:39:04 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/13 12:54:01 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# define WIN_WIDTH 960
# define WIN_HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define WALL_WIDTH 1024
# define WALL_HEIGHT 1024
# define MAX_TEX_NUM 16
# define TEX_TOTAL 36
# define SFX_TOTAL 15
# define E_DIR_SIZE 5
# define G_SHO_SIZE 3
# define Z_SHO_SIZE 4
# define G_DEA_SIZE 5
# define Z_DEA_SIZE	7
# define EUP_TEX 0
# define ELEFT_TEX 1
# define ERIGHT_TEX 2
# define EDOWN_TEX 3
# define KEY_TEX 19
# define BAR_TEX 16
# define PIL_TEX 17
# define LIG_TEX 18
# define TAB_TEX 29
# define SKE_TEX 27
# define WEL_TEX 28
# define VIN_TEX 30
# define TRE_TEX 31
# define ETA_TEX 32
# define KNI_TEX 33
# define GUARD_SHOOT 3
# define ZOMB_SHOOT 4
# define GUARD_DEATH 5
# define ZOMB_DEATH 7
# define G_SPEED 10.0f
# define Z_SPEED 12.0f
# define G_MOVE_DELAY 350
# define Z_MOVE_DELAY 200
# define D 98
# define LD 99
# include <stdint.h>
# include <time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_mixer.h"
# include "SDL2/ft2build.h"
# include "SDL2/png.h"
# include "SDL2/pngconf.h"
# include "SDL2/pnglibconf.h"
# include "SDL2/config_types.h"
# include "SDL2/ogg.h"
# include "SDL2/os_types.h"
# include "SDL2/codec.h"
# include "SDL2/vorbisenc.h"
# include "SDL2/vorbisfile.h"
# include "wolf_lists.h"
# include "wolf_structs.h"
# include "libft/libft.h"

void			free_map(t_map **m);
void			clean_door_list(t_door_list **doors);
void			clean_enemy_list(t_linked **enemies);
void			free_sdl_struct(t_sdl **sdl);
void			free_everything(t_wolf **wolf);
void			init_wolf(t_wolf *wolf, t_map *map, int total_sprites);
void			damage(t_linked *e, t_player *p,
						SDL_Surface **health, Mix_Chunk **sfx);
void			generate_walls(SDL_Surface **texture);
void			generate_sprites(SDL_Surface **texture);
void			update_door_timer(t_wolf *wolf, t_door_list **d_list);
void			refresh_enemy_list(t_linked **enemies, t_wolf *wolf);
void			check_door(t_wolf *w, t_player *p, t_map *m, int d);
void			sprite_cast(t_wolf *w, int *s_order, double *s_dist);
void			check_bullet_collision(t_ray *ray,
									t_sprite ***e_map, t_wolf *wolf);
void			handle_bullet_col(t_wolf *wolf, t_map *map);
void			render_hp(t_wolf *wolf);
void			dda(t_wolf *wolf, t_ray *ray, t_map *map, int bullet);
void			draw_skybox(t_ray *ray, SDL_Surface **skybox,
							t_sdl *sdl, int x);
void			draw_wall(t_line line, t_wolf *wolf, t_sdl *sdl, int x);
void			get_tex_bounds(t_wolf *wolf, t_sdl *sdl, t_ray *ray);
void			get_wall_bounds(t_ray *ray, t_player player, t_wolf *wolf);
void			move_forward(t_player *player, t_map *map, Mix_Chunk **sounds);
void			move_back(t_player *player, t_map *map);
void			rotate_right(t_player *player);
void			rotate_left(t_player *player);
void			update_weapon_pos(t_wolf *wolf);
void			update_key_pos(t_wolf *wolf);
void			ray_cast(t_wolf *wolf);
void			check_pickups(t_wolf *wolf);
void			update_and_refresh_frame(t_wolf *wolf);
void			handle_events(t_wolf *wolf);
void			init_audio(t_wolf *wolf);
void			set_range(t_decisions *decisions, int move, int shoot);
void			set_decision_ranges(double length, t_linked *enemy);
void			make_decision(t_linked *enemy);
void			move_enemy(t_player player, t_linked *enemy,
							t_ai *ai, t_wolf *wolf);
void			death_anim(t_linked *enemy, t_wolf *wolf);
void			shoot(t_player *player, t_linked *enemy,
						SDL_Surface **health, Mix_Chunk **sounds);
void			handle_enemy_ai(t_wolf *wolf, t_player *player,
									t_linked *enemies);
void			setup_text(t_sdl *sdl, t_player player);
void			draw_sprites(t_sprite *sprite, t_wolf *wolf, int inventory);
void			floor_cast(t_wolf *wolf, t_ray *ray, int x);
void			*cleanup(t_list *lst, t_map *m, char **split);
void			sort_sprites(int *order, double *distance, int first, int last);
void			*get_angle(t_sprite *sprite,
							t_player *player, t_enemy *enemy);
void			*map_error(char *message);
int				is_file(const char *file);
int				is_number(char *str);
int				setup_game(t_wolf **wolf, t_map **map, int argc, char **argv);
int				check_enemy_bullet(double dx, double dy, t_linked *enemy,
									t_wolf *wolf);
int				is_enclosed(t_map *map);
int				only_walls(t_map *map);
int				get_channel(void);
int				validate_sdl(t_sdl *sdl);
int				validate_map_texes(t_map *map);
double			*init_fdt(void);
double			get_wall_dist(t_ray *ray, t_player *player);
double			get_precise_hit_location(double wall_dist, t_ray *ray,
											t_player *player);
Uint32			*get_texture(t_sprite *sprite, t_player *player,
								t_textures *tex);
t_ray			*init_ray(t_player player, int x);
t_rgb			create_rgb(Uint8 r, Uint8 g, Uint8 b);
t_map			*read_map(char *file);
t_door			***init_doors(t_map *map);
t_sprite		***init_collect(t_map *map, t_sprite *sprites,
								int total_sprites);
t_sprite		***init_e_map(t_wolf *wolf);
t_sprite		*read_sprite_file(char *file, int *total_sprites, t_map *m);
t_sprite		*load_sprites(t_list *lst, int total_sprites);
t_sprite		init_sprite(double x, double y, int tex_num, int is_enemy);
t_sdl			*init_sdl_struct(t_player player);
t_point			get_transform(t_draw_vars *dv, t_player *p);
SDL_Surface		*set_health_text(int hp, SDL_Surface *cur_health);
SDL_Surface		**load_death(char *dir, int zombie);
SDL_Surface		**load_shoot(char *dir, int zombie);
SDL_Surface		**load_forward(char *dir);
SDL_Surface		**load_forwardright(char *dir);
SDL_Surface		**load_forwardleft(char *dir);
SDL_Surface		**load_left(char *dir);
SDL_Surface		**load_right(char *dir);
SDL_Surface		**load_backright(char *dir);
SDL_Surface		**load_backleft(char *dir);
SDL_Surface		**load_back(char *dir);
SDL_Surface		**generate_sky(void);
SDL_Surface		*convert_bitmap(SDL_Surface *image);
SDL_Color		make_color(int r, int g, int b);
#endif
