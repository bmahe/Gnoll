/***************************************************************************
 *   Copyright (C) 2006 by Puzzle Team                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


/*---------------------------------itimer.h--------------------------------*\
|   An interface for timer functions                                        |
|                                                                           |
|   Changelog :                                                             |
|               05/12/2007 - Vince - Initial release                        |
|                                                                           |
\*-------------------------------------------------------------------------*/


#ifndef __ITIMER_H__
#define __ITIMER_H__


/**
 *   An abstract base class for timer classes
 */
class ITimer
{
    public:
        /**
         *   A virtual destructor
         */
        virtual ~ITimer()  {}


        /**
         *   Returns amount of milliseconds since timer start or reset
         *   @return amount of milliseconds
         */
        virtual unsigned long int getMsecs() = 0;


        /**
         *   Reset the timer
         */
        virtual void reset() = 0;
};


#endif // __ITIMER_H__
