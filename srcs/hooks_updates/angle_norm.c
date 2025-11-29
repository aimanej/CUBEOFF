#include "../../includes/cub3d.h"

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return angle;
}
