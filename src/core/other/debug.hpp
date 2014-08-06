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

#ifndef DEBUG_H
#define DEBUG_H

#include <string>

#define FLAG_DEBUG_CONSOLE 1
#define FLAG_DEBUG_LOG     2
#define FLAG_DEBUG_MSGBOX  4

class debug_class
{
    public:
        bool        enabled;
        bool        enabled_log;
        bool        enabled_console;
        bool        enabled_msgbox;
         debug_class(void);
        ~debug_class(void);
        void        write(std::string message);
        void        write(std::string message, int flags);
};

#endif //DEBUG_H

