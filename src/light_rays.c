#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "vec3d.h"
#include "color.h"

static t_color	compute_shading_color(t_ray_object *light, t_ray_inf *ray_inf
		, t_ray_inf *light_ray, double angle)
{
	t_color	light_color;
	t_color	diffuse_color;
	//t_vec3d	reflect_vec;
	//double	light_specular;

	//reflect_vec = vec3d_sub(vec3d_scalar(
	//			light_ray->normal, 2 * angle), light_ray->direction);
	//light_specular = pow(-vec3d_dot_product(
	//			reflect_vec, ray_inf->direction), 8);
	light_color = color_scalar(
			light->color, (light->intensity * angle) / pow(light_ray->dist, 2));
	// TODO: specular light->intensity * light_specular
	diffuse_color = color_mul(ray_inf->object->color, light_color);
	return (diffuse_color);
}

static void		compute_light_color(t_data *data, t_ray_object *light
		, t_ray_inf *ray_inf, t_ray_inf *light_ray)
{
	double	angle;

	if (light->type == RAYOBJ_AMBIENTLIGHT)
		ray_inf->color = color_add(ray_inf->color, color_mul(
					ray_inf->object->color, color_scalar(
						light->color, light->intensity)));
	else if (!has_object_in_ray(data, light_ray, light_ray->dist))
	{
		angle = vec3d_dot_product(light_ray->normal, light_ray->direction);
		if (angle > .0)
			ray_inf->color = color_add(ray_inf->color, compute_shading_color(
						light, ray_inf, light_ray, angle));
	}
}

void			trace_light_rays(t_data *data, t_ray_inf *ray_inf)
{
	t_ray_inf		light_ray;
	t_list			*cur;
	t_ray_object	*light;

	light_ray.normal = ray_inf->normal;
	light_ray.origin = vec3d_add(ray_inf->intersect, vec3d_scalar(
				ray_inf->normal, 1e-4));
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
