#include "libft.h"
#include "quaternion.h"
#include "camera.h"
#include "vec3d.h"

void		rotate_camera(t_camera *camera, t_vec3d rot_vec, double angle)
{
	t_vec3d	dir;
	t_vec3d	right;
	t_vec3d	up;

	dir = rotate_by_quaternion(camera->direction, rot_vec, angle);
	right = rotate_by_quaternion(camera->right, rot_vec, angle);
	up = vec3d_unit(rotate_by_quaternion(camera->up, rot_vec, angle));
	camera->direction = vec3d_unit(dir);
	camera->right = vec3d_unit(right);
	camera->up = vec3d_unit(up);
}
