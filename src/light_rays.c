#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "vec3d.h"
#include "color.h"

static t_color		compute_shading(t_ray_object *light, t_ray_inf *ray_inf
		, t_ray_inf *light_ray, double cosine_angle)
{
	t_color	diffuse;
	t_color	specular;
	t_vec3d	reflection_dir;
	double	shine_factor;

	if (cosine_angle <= .0)
		diffuse = (t_color){.0, .0, .0};
	else
		diffuse = color_scalar(color_mul(
					light->color, ray_inf->object->color), cosine_angle);
	specular = (t_color){.0, .0, .0};
	if (cosine_angle >= .0)
	{
		reflection_dir = vec3d_sub(vec3d_scalar(
					light_ray->normal, 2 * cosine_angle), light_ray->direction);
		shine_factor = -vec3d_dot_product(reflection_dir, ray_inf->direction);
		if (shine_factor > 1)
			shine_factor = 1;
		if (shine_factor > 0)
			specular = color_scalar(color_mul(
						light->color, ray_inf->object->color), pow(
							shine_factor, ray_inf->object->shininess)
					* ray_inf->object->specular);
	}
	return (color_scalar(color_add(diffuse, specular)
				, light->intensity / pow(light_ray->dist, 2)));
}

static void		compute_light_color(t_data *data, t_ray_object *light
		, t_ray_inf *ray_inf, t_ray_inf *light_ray)
{
	double	cosine_angle;

	if (light->type == RAYOBJ_AMBIENTLIGHT)
	{
		ray_inf->color = color_add(ray_inf->color, color_mul(
					ray_inf->object->color, color_scalar(
						light->color, light->intensity)));
	}
	else if (!has_object_in_ray(data, light_ray, light_ray->dist))
	{
		cosine_angle = vec3d_dot_product(light_ray->normal, light_ray->direction);
		ray_inf->color = color_add(ray_inf->color, compute_shading(
					light, ray_inf, light_ray, cosine_angle));
	}
}

void			trace_light_rays(t_data *data, t_ray_inf *ray_inf)
{
	t_ray_inf		light_ray;
	t_list			*cur;
	t_ray_object	*light;

	light_ray.normal = vec3d_unit(ray_inf->normal);
	light_ray.origin = vec3d_add(ray_inf->intersect, vec3d_scalar(
				light_ray.normal, 1e-4));
	cur = data->lights;
	while (cur != NULL)
	{
		light = (t_ray_object *)cur->content;
		light_ray.direction = vec3d_sub(light->origin, light_ray.origin);
		light_ray.dist = vec3d_length(light_ray.direction);
		light_ray.direction = vec3d_unit(light_ray.direction);
		compute_light_color(data, light, ray_inf, &light_ray);
		cur = cur->next;
	}
}
