/*
* Copyright (c) 2011-2014 Paul Wortmann
* General purpose, cross platform, computer game engine. [http://www.physhexgames.co.nr]
*
* This file is part of Project_0.
*
* Project_0 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* @author Paul Wortmann [paul.wortmann@gmail.com]
*
*/

#include "physics.hpp"
#include <math.h>


physics_class::physics_class         (void)
{
    physics_class::generate_sin_table();
    physics_class::generate_cos_table();
};

physics_class::~physics_class         (void)
{

};

bool  physics_class::cube_collision        (float x1, float y1, float z1, float w1, float h1, float d1, float x2, float y2, float z2, float w2, float h2, float d2)
{
    if (((x1-(w1/2) < x2+(w2/2)) && (x2+(w2/2) > x1-(w1/2))) && ((x2-(w2/2) < x1+(w1/2)) && (x1+(w1/2) > x2-(w2/2)))
     && ((y1-(h1/2) < y2+(h2/2)) && (y2+(h2/2) > y1-(h1/2))) && ((y2-(h2/2) < y1+(h1/2)) && (y1+(h1/2) > y2-(h2/2)))
     && ((z1-(d1/2) < z2+(d2/2)) && (z2+(d2/2) > z1-(d1/2))) && ((z2-(d2/2) < z1+(d1/2)) && (z1+(d1/2) > z2-(d2/2)))) return(true);
    else return(false);
}

bool  physics_class::quadrangle_collision   (float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    if (((x1-(w1/2) < x2+(w2/2)) && (x2+(w2/2) > x1-(w1/2))) && ((x2-(w2/2) < x1+(w1/2)) && (x1+(w1/2) > x2-(w2/2)))
     && ((y1-(h1/2) < y2+(h2/2)) && (y2+(h2/2) > y1-(h1/2))) && ((y2-(h2/2) < y1+(h1/2)) && (y1+(h1/2) > y2-(h2/2)))) return(true);
    else return(false);
}

bool  physics_class::circle_collision(float x1, float y1, float r1, float x2, float y2, float r2)
{
    if (((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)) < ((r1+r2)*(r1+r2))) return(true);
    else return(false);
}

bool  physics_class::sphere_collision(float x1, float y1, float z1, float r1, float x2, float y2, float z2, float r2)
{
    if ((((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))+((z1-z2)*(z1-z2))) < ((r1+r2)*(r1+r2))) return(true);
    else return(false);
}

float  physics_class::distance_2D(float x1, float y1, float x2, float y2)
{
    return(sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))));
}

float  physics_class::distance_3D(float x1, float y1, float z1, float x2, float y2, float z2)
{
    return(sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))+((z1-z2)*(z1-z2))));
}

bool   physics_class::point_in_circle          (float cx, float cy, float cr, float px, float py)
{
    if ((((px-cx) * (px-cx)) + ((py-cy) * (py-cy))) < (cr*cr)) return(true);
    else return(false);
};

bool  physics_class::point_in_quadrangle  (float qx, float qw, float qy, float qh, float px, float py) //rectangle!
{
    if ((px > (qx-(qw/2))) && (px < (qx+(qw/2))) && (py > (qy-(qh/2))) && (py < (qy+(qh/2)))) return(true);
    else return(false);
};

bool   physics_class::point_in_diamond         (float dx, float dw, float dy, float dh, float px, float py)
{
    if ((py >= (dy - (dh/2.0f))) && (py <= (dy + (dh/2.0f))) && (px >= (dx - ((dw/2.0f) - (py - dy)))) && (px <= (dx + ((dw/2.0f) - (py - dy))))) return(true);
    else return(false);
};

float  physics_class::point_side_of_line       (float x1, float y1, float x2, float y2, float px, float py)
{
    return((py-y1)-((y2-y1)/(x2-x1))*(px-x1));
};

float  physics_class::line_slope_2D(float x1, float y1, float x2, float y2)
{
    return((y2-y1)/(x2-x1));
};

float  physics_class::line_angle(float x1, float y1, float x2, float y2)
{
    return(atan2(y2 - y1, x2 - x1));
};

float  physics_class::line_point_2D_x(float x1, float distance, float angle)
{
    return(x1 + distance*physics_class::cos_table[(int)angle]);
};

float physics_class::line_point_2D_y(float y1, float distance, float angle)
{
    return(y1 + distance*physics_class::sin_table[(int)angle]);
};

float  physics_class::rotate_point_2D_x(float cx,float cy,float px,float py,int angle)
{
    return(((px-cx) * physics_class::cos_table[angle] - (py-cy) * physics_class::sin_table[angle])+cx);
}

float  physics_class::rotate_point_2D_y(float cx,float cy,float px,float py,int angle)
{
    return(((px-cx) * physics_class::sin_table[angle] + (py-cy) * physics_class::cos_table[angle])+cy);
}

float  physics_class::move_velocity_angle_2D_x    (float  x, float v,  float radians)
{
    return(x + (v*physics_class::sin_table[(int)physics_class::radians_to_degrees(radians)]));
};

float  physics_class::move_velocity_angle_2D_y    (float  y, float v,  float radians)
{
    return(y + (v*physics_class::cos_table[(int)physics_class::radians_to_degrees(radians)]));
};

float  physics_class::move_velocity_angle_2D_x    (float  x, float v,  int degrees)
{
    return(x + (v*physics_class::sin_table[degrees]));
};

float  physics_class::move_velocity_angle_2D_y    (float  y, float v,  int degrees)
{
    return(y + (v*physics_class::cos_table[degrees]));
};

float  physics_class::degrees_to_radians   (float degrees)
{
    return(degrees * (M_PI/180));
};

float  physics_class::radians_to_degrees   (float radians)
{
    return(radians * (180/M_PI));
};

void   physics_class::generate_sin_table   (void)
{
    for(int sin_count = 0; sin_count < 360; sin_count++)
        physics_class::sin_table[sin_count] = sin(sin_count* (M_PI/180));
};

void   physics_class::generate_cos_table   (void)
{
    for(int cos_count = 0; cos_count < 360; cos_count++)
        physics_class::cos_table[cos_count] = cos(cos_count* (M_PI/180));
};

bool   physics_class::point_in_polygon(int number_of_vertecies, vertex_3f_class vertex[], float px, float py)
{
    bool return_value = false;
    for (int i = 0, j = number_of_vertecies-1; i < number_of_vertecies; j = i++)
    {
        if (((vertex[i].y>py) != (vertex[j].y>py)) && (px < (vertex[j].x-vertex[i].x) * (py-vertex[i].y) / (vertex[j].y-vertex[i].y) + vertex[i].x)) return_value = !return_value;
    }
    return(return_value);
};

int   physics_class::sigma(int n)
{
    if (n <= 0) return (0);
    else return (n + sigma(n - 1));
};
