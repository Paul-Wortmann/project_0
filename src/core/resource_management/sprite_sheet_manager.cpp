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

#include "sprite_sheet_manager.hpp"
#include "../../game.hpp"

extern game_class game;

sprite_sheet_manager_class::sprite_sheet_manager_class(void)
{
    sprite_sheet_manager_class::last               = NULL;
    sprite_sheet_manager_class::root               = NULL;
    sprite_sheet_manager_class::number_of_sprite_sheets = 0;
}

sprite_sheet_manager_class::~sprite_sheet_manager_class(void)
{
    sprite_sheet_type* temp_pointer;
    temp_pointer = sprite_sheet_manager_class::root;
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

sprite_sheet_type *sprite_sheet_manager_class::add(std::string file_name, int width, int height)
{
    if (sprite_sheet_manager_class::number_of_sprite_sheets == 0)
    {
        sprite_sheet_manager_class::root = new sprite_sheet_type;
        sprite_sheet_manager_class::root->next = NULL;
        sprite_sheet_manager_class::last = new sprite_sheet_type;
        sprite_sheet_manager_class::last = root;
        sprite_sheet_manager_class::last->next = NULL;
    }
    else
    {
        sprite_sheet_type* temp_pointer = sprite_sheet_manager_class::root;
        if (temp_pointer != NULL)
        {
            while (temp_pointer != NULL)
            {
                if (strcmp(file_name.c_str(),temp_pointer->data.file_name.c_str()) == 0) return(temp_pointer);
                temp_pointer = temp_pointer->next;
            }
        }
        sprite_sheet_manager_class::last->next = new sprite_sheet_type;
        sprite_sheet_manager_class::last = sprite_sheet_manager_class::last->next;
        sprite_sheet_manager_class::last->next = new sprite_sheet_type;
        sprite_sheet_manager_class::last->next = NULL;
    }
    sprite_sheet_manager_class::last->data.file_name          = file_name.c_str();
    sprite_sheet_manager_class::last->data.sprite_width       = width;
    sprite_sheet_manager_class::last->data.sprite_height      = height;
    sprite_sheet_manager_class::last->data.angle              = 0.0f;
    sprite_sheet_manager_class::last->data.loaded = sprite_sheet_manager_class::load(last);
    if (sprite_sheet_manager_class::last->data.loaded) sprite_sheet_manager_class::number_of_sprite_sheets++;
    return(sprite_sheet_manager_class::last);
}

bool sprite_sheet_manager_class::load(sprite_sheet_type *sprite_sheet)
{
    bool            return_value   = false;
    SDL_Surface    *image_surface  = NULL;
    if ((image_surface = game.core.file.load_image(sprite_sheet->data.file_name.c_str())))
    {
        GLint           number_of_colors;
        GLenum          texture_format = 0;
        return_value                   = true;
        number_of_colors = image_surface->format->BytesPerPixel;
        if (number_of_colors == 4)
        {
            if (image_surface->format->Rmask == 0x000000ff) texture_format = GL_RGBA;
            else texture_format = GL_BGRA;
        }
        else if (number_of_colors == 3)
        {
            if (image_surface->format->Rmask == 0x000000ff) texture_format = GL_RGB;
            else texture_format = GL_BGR;
        }
        glGenTextures  (1, &sprite_sheet->data.data);
        glBindTexture  (GL_TEXTURE_2D, sprite_sheet->data.data);
        glEnable       (GL_BLEND);
        glBlendFunc    (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexEnvf      (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexImage2D   (GL_TEXTURE_2D, 0, number_of_colors, image_surface->w, image_surface->h, 0, texture_format, GL_UNSIGNED_BYTE, image_surface->pixels);
    }
    else
    {
        return_value = false;
        game.core.log.write("Failed to load image ->"+sprite_sheet->data.file_name);
    }
    if (image_surface) SDL_FreeSurface(image_surface);
    sprite_sheet->data.loaded = return_value;
    return(return_value);
}

void sprite_sheet_manager_class::draw(sprite_sheet_type *sprite_sheet, float pos_x, float pos_y, float pos_z, float width, float height, float angle, int sprite)
{
    if (sprite_sheet->data.loaded)
    {
        if (sprite_sheet->data.data)
        {
            const float verticies[] = {
            pos_x, pos_y,
            pos_x + width, pos_y,
            pos_x + width, pos_y + height,
            pos_x, pos_y + height};
            /*
            const float texture_verticies[] = {
            pos_x, pos_y,
            pos_x + width, pos_y,
            pos_x + width, pos_y + height,
            pos_x, pos_y + height};
            */
            const float texture_verticies[] = {
            0, 0,
            32, 0,
            32, 32,
            0, 32};

            glPushMatrix();
            glBindTexture( GL_TEXTURE_2D, sprite_sheet->data.data);
            glLoadIdentity();

            //glVertexPointer(2, GL_FLOAT, verticies);

            //glTextureVertexPointer(2, GL_FLOAT, texture_verticies);
            //glDrawArrays(GL_TRI_STRIP, 0, 4);

            glBegin( GL_QUADS );
            glTexCoord2i( 0, 1 );glVertex3f(pos_x-width,pos_y-height, pos_z);
            glTexCoord2i( 0, 0 );glVertex3f(pos_x-width,pos_y+height, pos_z);
            glTexCoord2i( 1, 0 );glVertex3f(pos_x+width,pos_y+height, pos_z);
            glTexCoord2i( 1, 1 );glVertex3f(pos_x+width,pos_y-height, pos_z);
            glEnd();

            glPopMatrix();
        }
        else
        {
            game.core.log.write("Fail - Texture manager draw image function called without image data.");
            game.core.log.write("Fail - You are most likely missing data files, please re-install.");
            game.state = GAME_STATE_ERROR;
        }
    }
    else
    {
        game.core.log.write("Fail - Texture manager draw image function called without image data.");
        game.core.log.write("Fail - You are most likely missing data files, please re-install.");
        game.state = GAME_STATE_ERROR;
    }
}


/*
        const float tw = float(spriteWidth) / texWidth;
        const float th = float(spriteHeight) / texHeight;
        const int numPerRow = texWidth / spriteWidth;
        const float tx = (frameIndex % numPerRow) * tw;
        const float ty = (frameIndex / numPerRow + 1) * th;

        const float texVerts[] = {
            tx, ty,
            tx + tw, ty,
            tx + tw, ty + th,
            tx, ty + th
        };
*/
        // ... Bind the texture, enable the proper arrays

