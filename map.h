




#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <Box2D/Box2D.h>
#include "objectmanager.h"
#include "../resource_management/xml_parser.hpp"
#include "../other/types.hpp"

const float M2P = 20;
const float P2M = 1/M2P;

#define BODY_TYPE_STATIC  0
#define BODY_TYPE_DYNAMIC 1

struct texture_path_type
{
    std::string diffuse;
    std::string normal;
    std::string specular;
};

struct object_data_type
{
    int               body_type;
    f2_type           position;
    f2_type           dimension;
    float             rotation;
    float             friction;
    float             restitution;
    float             density;
    texture_path_type texture;
    object_type*      object;
    b2Body*           body;
    b2BodyDef         bodydef;
    b2FixtureDef      fixturedef;
    b2PolygonShape    shapedef;
};

struct physics_data_type
{
    b2Vec2    gravity;
    b2World  *world;
};

struct map_type
{
    unsigned int      number_of_objects;
    object_data_type* object_data;
    physics_data_type physics_data;
};

class map_class
{
    public:
    //int render(map_type &map_pointer);
    int load   (map_type &map_pointer, std::string file_name);
    int save   (map_type &map_pointer, std::string file_name);
    int process(map_type &map_pointer);
};

#endif //MAP_HPP

