
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


/*---------------------------DefaultCameraFirstPersonListener--------------*\
|   This is a message's listener for camera first person                    |
|                                                                           |
|   Changelog :                                                             |
|               04/12/2008 - Gabriel - Initial release                      |
\*-------------------------------------------------------------------------*/

#ifndef INCLUDED_DEFAULTCAMERAFIRSTPERSONLISTENER_H
#define INCLUDED_DEFAULTCAMERAFIRSTPERSONLISTENER_H

#include "cmessagelistenercamera.h"

namespace Gnoll
{
	namespace Core
	{
		class DefaultCameraFirstPersonListener : public CMessageListenerCamera
		{
		public:
			/**
			 * This is a constructor
			 */
			DefaultCameraFirstPersonListener();

			/**
			 * This is a destructor
			 */
			~DefaultCameraFirstPersonListener();

			/**
			 * This method is called in order to process a message
			 * @param message The message this method will have to process
			 */
			void handle ( shared_ptr<CMessage> message );
		};
	};
};

#endif
