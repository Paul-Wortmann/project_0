

#include "map.h"
#include "../RoboEngine/system/enginelog.h"

extern game_class game;

f3_type rotate_vertex(f3_type vertex, f2_type origin, float angle)
{
    f3_type return_vertex;
    return_vertex.x = cos(angle) * (vertex.x - origin.x) - sin (angle) * (vertex.y - origin.y) + origin.x;
    return_vertex.y = sin(angle) * (vertex.x - origin.x) + cos (angle) * (vertex.y - origin.y) + origin.y;
    return(return_vertex);
}

int map_class::load  (map_type &map_pointer, std::string file_name)
{
    unsigned int return_value = EXIT_SUCCESS;
    xml_type xml_data;
    map_pointer.number_of_objects = 0;
    return_value = game.core.xml_parser.load(xml_data,file_name.c_str());
    for (int xml_count = 0; xml_count < xml_data.number_of_data; xml_count++)
    {
        if (xml_data.data[xml_count].key.compare("object") == 0) map_pointer.number_of_objects++;
    }
    if (map_pointer.object_data) delete map_pointer.object_data;
    map_pointer.object_data = new object_data_type[map_pointer.number_of_objects+1];
    for (int object_count = 0; object_count < map_pointer.number_of_objects; object_count++)
    {
        map_pointer.object_data[object_count].dimension.x  = 0.0f;
        map_pointer.object_data[object_count].dimension.y  = 0.0f;
        map_pointer.object_data[object_count].position.x   = 0.0f;
        map_pointer.object_data[object_count].position.y   = 0.0f;
        map_pointer.object_data[object_count].body_type    = BODY_TYPE_STATIC;
        map_pointer.object_data[object_count].friction     = 0.2f;
        map_pointer.object_data[object_count].restitution  = 0.0f;
        map_pointer.object_data[object_count].density      = 1.0f;
    }
    map_pointer.physics_data.gravity.x = 0.0f;
    map_pointer.physics_data.gravity.y = 9.8f;
    #define XML_BLOCK_UNKNOWN 0
    #define XML_BLOCK_WORLD   1
    #define XML_BLOCK_OBJECT  2
    #define XML_KEY_UNKNOWN   0
    #define XML_KEY_DIMENSION 1
    #define XML_KEY_POSITION  2
    #define XML_KEY_ROTATION  3
    #define XML_KEY_TEXTURE   4
    #define XML_KEY_GRAVITY   5
    #define XML_KEY_PHYSICS   6
    int object_count = 0;
    int block_type = XML_BLOCK_UNKNOWN;
    int key_type   = XML_KEY_POSITION;
    for (int xml_count = 0; xml_count < xml_data.number_of_data; xml_count++)
    {
        if (xml_data.data[xml_count].key_present)
        {
            if (xml_data.data[xml_count].key.compare("world")      == 0) block_type = XML_BLOCK_WORLD;
            if (xml_data.data[xml_count].key.compare("object")     == 0) block_type = XML_BLOCK_OBJECT;
            if (xml_data.data[xml_count].key.compare("/object")    == 0) object_count++;
            if (xml_data.data[xml_count].key.compare("dimension")  == 0) key_type = XML_KEY_DIMENSION;
            if (xml_data.data[xml_count].key.compare("/dimension") == 0) key_type = XML_KEY_UNKNOWN;
            if (xml_data.data[xml_count].key.compare("position")   == 0) key_type = XML_KEY_POSITION;
            if (xml_data.data[xml_count].key.compare("/position")  == 0) key_type = XML_KEY_UNKNOWN;
            if (xml_data.data[xml_count].key.compare("rotation")   == 0) key_type = XML_KEY_ROTATION;
            if (xml_data.data[xml_count].key.compare("/rotation")  == 0) key_type = XML_KEY_UNKNOWN;
            if (xml_data.data[xml_count].key.compare("texture")    == 0) key_type = XML_KEY_TEXTURE;
            if (xml_data.data[xml_count].key.compare("/texture")   == 0) key_type = XML_KEY_UNKNOWN;
            if (xml_data.data[xml_count].key.compare("gravity")    == 0) key_type = XML_KEY_GRAVITY;
            if (xml_data.data[xml_count].key.compare("/gravity")   == 0) key_type = XML_KEY_UNKNOWN;
            if (xml_data.data[xml_count].key.compare("physics")    == 0) key_type = XML_KEY_PHYSICS;
            if (xml_data.data[xml_count].key.compare("/physics")   == 0) key_type = XML_KEY_UNKNOWN;
        }
        if ((block_type == XML_BLOCK_WORLD) && (xml_data.data[xml_count].key_present) && (xml_data.data[xml_count].value_present))
        {
            if ((xml_data.data[xml_count].key.compare("x") == 0) && (key_type == XML_KEY_GRAVITY)) map_pointer.physics_data.gravity.x = atof(xml_data.data[xml_count].value.c_str());
            if ((xml_data.data[xml_count].key.compare("y") == 0) && (key_type == XML_KEY_GRAVITY)) map_pointer.physics_data.gravity.y = atof(xml_data.data[xml_count].value.c_str());
        }
        if ((block_type == XML_BLOCK_OBJECT) && (xml_data.data[xml_count].key_present) && (xml_data.data[xml_count].value_present))
        {
            if ((xml_data.data[xml_count].key.compare("x") == 0) && (key_type == XML_KEY_DIMENSION)) map_pointer.object_data[object_count].dimension.x = atof(xml_data.data[xml_count].value.c_str());
            if ((xml_data.data[xml_count].key.compare("y") == 0) && (key_type == XML_KEY_DIMENSION)) map_pointer.object_data[object_count].dimension.y = atof(xml_data.data[xml_count].value.c_str());
            if ((xml_data.data[xml_count].key.compare("x") == 0) && (key_type == XML_KEY_POSITION))  map_pointer.object_data[object_count].position.x  = atof(xml_data.data[xml_count].value.c_str());
            if ((xml_data.data[xml_count].key.compare("y") == 0) && (key_type == XML_KEY_POSITION))  map_pointer.object_data[object_count].position.y  = atof(xml_data.data[xml_count].value.c_str());
            if ((xml_data.data[xml_count].key.compare("x") == 0) && (key_type == XML_KEY_ROTATION))  map_pointer.object_data[object_count].rotation    = atof(xml_data.data[xml_count].value.c_str());
            if ((xml_data.data[xml_count].key.compare("diffuse")   == 0) && (key_type == XML_KEY_TEXTURE)) map_pointer.object_data[object_count].texture.diffuse = xml_data.data[xml_count].value.c_str();
            if ((xml_data.data[xml_count].key.compare("normal")    == 0) && (key_type == XML_KEY_TEXTURE)) map_pointer.object_data[object_count].texture.normal = xml_data.data[xml_count].value.c_str();
            if ((xml_data.data[xml_count].key.compare("specular")  == 0) && (key_type == XML_KEY_TEXTURE)) map_pointer.object_data[object_count].texture.specular = xml_data.data[xml_count].value.c_str();
            if ((xml_data.data[xml_count].key.compare("body_type") == 0) && (key_type == XML_KEY_PHYSICS))
            {
                if (xml_data.data[xml_count].value.compare("static")  == 0) map_pointer.object_data[object_count].body_type = BODY_TYPE_STATIC;
                if (xml_data.data[xml_count].value.compare("dynamic") == 0) map_pointer.object_data[object_count].body_type = BODY_TYPE_DYNAMIC;
            }
            if ((xml_data.data[xml_count].key.compare("friction")    == 0) && (key_type == XML_KEY_PHYSICS)) map_pointer.object_data[object_count].friction    = atof(xml_data.data[xml_count].value.c_str());
            if ((xml_data.data[xml_count].key.compare("restitution") == 0) && (key_type == XML_KEY_PHYSICS)) map_pointer.object_data[object_count].restitution = atof(xml_data.data[xml_count].value.c_str());
            if ((xml_data.data[xml_count].key.compare("density")     == 0) && (key_type == XML_KEY_PHYSICS)) map_pointer.object_data[object_count].density     = atof(xml_data.data[xml_count].value.c_str());
        }
    }
    map_pointer.physics_data.world = new b2World(map_pointer.physics_data.gravity);
    map_pointer.physics_data.world->SetGravity(map_pointer.physics_data.gravity);
    for (int object_count = 0; object_count < map_pointer.number_of_objects; object_count++)
    {
        game.core.log.write("adding object -> "+game.core.misc.itos(object_count));
        map_pointer.object_data[object_count].object = game.core.object_manager.add(game.core.object_manager.number_of_objects+1);
        map_pointer.object_data[object_count].object->render.texture.diffuse  = game.core.sprite_sheet_manager.add(map_pointer.object_data[object_count].texture.diffuse.c_str(),64,64);
        map_pointer.object_data[object_count].object->render.texture.normal   = game.core.sprite_sheet_manager.add(map_pointer.object_data[object_count].texture.normal.c_str(),64,64);
        map_pointer.object_data[object_count].object->render.texture.specular = game.core.sprite_sheet_manager.add(map_pointer.object_data[object_count].texture.specular.c_str(),64,64);
        map_pointer.object_data[object_count].object->render.number_of_vertex = 4;
        map_pointer.object_data[object_count].object->render.vertex = new f3_type[map_pointer.object_data[object_count].object->render.number_of_vertex];
        map_pointer.object_data[object_count].object->render.vertex[0].x =  map_pointer.object_data[object_count].position.x + (map_pointer.object_data[object_count].dimension.x/2.0f);
        map_pointer.object_data[object_count].object->render.vertex[0].y =  map_pointer.object_data[object_count].position.y + (map_pointer.object_data[object_count].dimension.y/2.0f);
        map_pointer.object_data[object_count].object->render.vertex[0].z =  1.0f;
        map_pointer.object_data[object_count].object->render.vertex[1].x =  map_pointer.object_data[object_count].position.x - (map_pointer.object_data[object_count].dimension.x/2.0f);
        map_pointer.object_data[object_count].object->render.vertex[1].y =  map_pointer.object_data[object_count].position.y + (map_pointer.object_data[object_count].dimension.y/2.0f);
        map_pointer.object_data[object_count].object->render.vertex[1].z =  1.0f;
        map_pointer.object_data[object_count].object->render.vertex[2].x =  map_pointer.object_data[object_count].position.x - (map_pointer.object_data[object_count].dimension.x/2.0f);
        map_pointer.object_data[object_count].object->render.vertex[2].y =  map_pointer.object_data[object_count].position.y - (map_pointer.object_data[object_count].dimension.y/2.0f);
        map_pointer.object_data[object_count].object->render.vertex[2].z =  1.0f;
        map_pointer.object_data[object_count].object->render.vertex[3].x =  map_pointer.object_data[object_count].position.x + (map_pointer.object_data[object_count].dimension.x/2.0f);
        map_pointer.object_data[object_count].object->render.vertex[3].y =  map_pointer.object_data[object_count].position.y - (map_pointer.object_data[object_count].dimension.y/2.0f);
        map_pointer.object_data[object_count].object->render.vertex[3].z =  1.0f;
        for (int i = 0; i < map_pointer.object_data[object_count].object->render.number_of_vertex; i++)
        {
            map_pointer.object_data[object_count].object->render.vertex[i] = rotate_vertex(map_pointer.object_data[object_count].object->render.vertex[i],map_pointer.object_data[object_count].position,map_pointer.object_data[object_count].rotation);
        }
        map_pointer.object_data[object_count].bodydef.position.Set(map_pointer.object_data[object_count].position.x,map_pointer.object_data[object_count].position.y);
        if (map_pointer.object_data[object_count].body_type == BODY_TYPE_STATIC)  map_pointer.object_data[object_count].bodydef.type = b2_staticBody;
        if (map_pointer.object_data[object_count].body_type == BODY_TYPE_DYNAMIC) map_pointer.object_data[object_count].bodydef.type = b2_dynamicBody;
        map_pointer.object_data[object_count].body = map_pointer.physics_data.world->CreateBody(&map_pointer.object_data[object_count].bodydef);
        map_pointer.object_data[object_count].fixturedef.density     = map_pointer.object_data[object_count].density;
        map_pointer.object_data[object_count].fixturedef.friction    = map_pointer.object_data[object_count].friction;
        map_pointer.object_data[object_count].fixturedef.restitution = map_pointer.object_data[object_count].restitution;
        map_pointer.object_data[object_count].shapedef.SetAsBox(map_pointer.object_data[object_count].dimension.x/2.0f,map_pointer.object_data[object_count].dimension.y/2.0f);
        map_pointer.object_data[object_count].fixturedef.shape = &map_pointer.object_data[object_count].shapedef;
        map_pointer.object_data[object_count].body->CreateFixture(&map_pointer.object_data[object_count].fixturedef);
        game.core.log.write("added object -> "+game.core.misc.itos(object_count));
    }
    return (return_value);
}

int map_class::save  (map_type &map_pointer, std::string file_name)
{
    unsigned int return_value = EXIT_FAILURE;
    return (return_value);
}

int map_class::process(map_type &map_pointer)
{
    map_pointer.physics_data.world->Step(1.0/30.0,8,3);
    for (int object_count = 0; object_count < map_pointer.number_of_objects; object_count++)
    {
        if (map_pointer.object_data[object_count].body_type == BODY_TYPE_DYNAMIC)
        {
            for (int i = 0; i < 4; i++)
            {
                map_pointer.object_data[object_count].object->render.vertex[3-i].x = ((b2PolygonShape*)map_pointer.object_data[object_count].body->GetFixtureList()->GetShape())->GetVertex(i).x;
                map_pointer.object_data[object_count].object->render.vertex[3-i].y = ((b2PolygonShape*)map_pointer.object_data[object_count].body->GetFixtureList()->GetShape())->GetVertex(i).y;
                std::cout << "x - "+game.core.misc.ftos(map_pointer.object_data[object_count].object->render.vertex[i].x) << std::endl;
                std::cout << "y - "+game.core.misc.ftos(map_pointer.object_data[object_count].object->render.vertex[i].y) << std::endl;
            }
        }
    }
}
