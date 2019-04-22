#include <math.h>
#include "camera.h"
#include "vec3d.h"
#include "lib.h"
#include "raytracer.h"

void		camera_event(t_data *data)
{
	if (data->lib.cam_keys == 0 && data->square_pixels_per_ray > 0)
		data->square_pixels_per_ray -= 1;
	if (data->lib.cam_keys != 0)
		data->square_pixels_per_ray = 15;
	if (data->lib.cam_keys & CAMERA_RIGHT)
		rotate_camera(&data->camera, (t_vec3d){0, 1, 0}, M_PI / 90);
	if (data->lib.cam_keys & CAMERA_LEFT)
		rotate_camera(&data->camera, (t_vec3d){0, 1, 0}, -1 * M_PI / 90);
	if (data->lib.cam_keys & CAMERA_DOWN)
		rotate_camera(&data->camera, data->camera.right, M_PI / 90);
	if (data->lib.cam_keys & CAMERA_UP)
		rotate_camera(&data->camera, data->camera.right, -1 * M_PI / 90);
	if (data->lib.cam_keys & CAMERA_TR_LEFT)
		data->camera.origin = vec3d_sub(data->camera.origin, data->camera.right);
	if (data->lib.cam_keys & CAMERA_TR_RIGHT)
		data->camera.origin = vec3d_add(data->camera.origin, data->camera.right);
	if (data->lib.cam_keys & CAMERA_TR_FRONT)
		data->camera.origin = vec3d_add(data->camera.origin, data->camera.direction);
	if (data->lib.cam_keys & CAMERA_TR_BACK)
		data->camera.origin = vec3d_sub(data->camera.origin, data->camera.direction);
	if (data->lib.cam_keys & CAMERA_TR_UP)
		data->camera.origin.y -= 1;
	if (data->lib.cam_keys & CAMERA_TR_DOWN)
		data->camera.origin.y += 1;
}

static void	camera_release_key(SDL_Event *event, t_data *data)
{
	if (event->key.type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_RIGHT)
			data->lib.cam_keys &= ~CAMERA_RIGHT;
		if (event->key.keysym.sym == SDLK_LEFT)
			data->lib.cam_keys &= ~CAMERA_LEFT;
		if (event->key.keysym.sym == SDLK_DOWN)
			data->lib.cam_keys &= ~CAMERA_DOWN;
		if (event->key.keysym.sym == SDLK_UP)
			data->lib.cam_keys &= ~CAMERA_UP;
		if (event->key.keysym.sym == SDLK_a)
			data->lib.cam_keys &= ~CAMERA_TR_LEFT;
		if (event->key.keysym.sym == SDLK_d)
			data->lib.cam_keys &= ~CAMERA_TR_RIGHT;
		if (event->key.keysym.sym == SDLK_w)
			data->lib.cam_keys &= ~CAMERA_TR_FRONT;
		if (event->key.keysym.sym == SDLK_s)
			data->lib.cam_keys &= ~CAMERA_TR_BACK;
		if (event->key.keysym.sym == SDLK_KP_PLUS)
			data->lib.cam_keys &= ~CAMERA_TR_UP;
		if (event->key.keysym.sym == SDLK_KP_MINUS)
			data->lib.cam_keys &= ~CAMERA_TR_DOWN;
	}
}

void		camera_press_key(SDL_Event *event, t_data *data)
{
	if (event->key.type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_RIGHT)
			data->lib.cam_keys |= CAMERA_RIGHT;
		if (event->key.keysym.sym == SDLK_LEFT)
			data->lib.cam_keys |= CAMERA_LEFT;
		if (event->key.keysym.sym == SDLK_DOWN)
			data->lib.cam_keys |= CAMERA_DOWN;
		if (event->key.keysym.sym == SDLK_UP)
			data->lib.cam_keys |= CAMERA_UP;
		if (event->key.keysym.sym == SDLK_a)
			data->lib.cam_keys |= CAMERA_TR_LEFT;
		if (event->key.keysym.sym == SDLK_d)
			data->lib.cam_keys |= CAMERA_TR_RIGHT;
		if (event->key.keysym.sym == SDLK_w)
			data->lib.cam_keys |= CAMERA_TR_FRONT;
		if (event->key.keysym.sym == SDLK_s)
			data->lib.cam_keys |= CAMERA_TR_BACK;
		if (event->key.keysym.sym == SDLK_KP_PLUS)
			data->lib.cam_keys |= CAMERA_TR_UP;
		if (event->key.keysym.sym == SDLK_KP_MINUS)
			data->lib.cam_keys |= CAMERA_TR_DOWN;
	}
	camera_release_key(event, data);
}
