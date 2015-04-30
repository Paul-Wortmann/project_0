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

#include "object_manager.hpp"
#include "../../game.hpp"

extern game_class game;

object_manager_class::object_manager_class(void)
{
    object_manager_class::last              = NULL;
    object_manager_class::root              = NULL;
    object_manager_class::number_of_objects = 0;
}

object_manager_class::~object_manager_class(void)
{
    object_type* temp_pointer;
    temp_pointer = object_manager_class::root;
    if (temp_pointer != NULL)
    {
        while (temp_pointer->next != NULL)
        {
            //delete [] temp_pointer->data.data;
            temp_pointer = temp_pointer->next;
        }
    }
    //delete [] root;
    //delete [] last;
}

object_type *object_manager_class::add(int UID)
{
    if (object_manager_class::number_of_objects == 0)
    {
        object_manager_class::root = new object_type;
        object_manager_class::root->next = NULL;
        object_manager_class::last = new object_type;
        object_manager_class::last = root;
        object_manager_class::last->next = NULL;
    }
    else
    {
        object_type* temp_pointer = object_manager_class::root;
        if (temp_pointer != NULL)
        {
            while (temp_pointer != NULL)
            {
                if (temp_pointer->base.UID == UID) return(temp_pointer);
                temp_pointer = temp_pointer->next;
            }
        }
        object_manager_class::last->next = new object_type;
        object_manager_class::last = object_manager_class::last->next;
        object_manager_class::last->next = new object_type;
        object_manager_class::last->next = NULL;
    }
    object_manager_class::last->base.UID    = UID;
    object_manager_class::last->base.loaded = true;
    object_manager_class::number_of_objects++;
    return(object_manager_class::last);
}
