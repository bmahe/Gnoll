/***************************************************************************
 *   Copyright (C) 2009 by Bruno Mahe                                      *
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

#include "../include/oisjoysticklistener.h"
#include "../include/cinputjoystickevents.h"
#include "../../core/include/cmessagemodule.h"
#include "../../core/include/cmessage.h"
#include "../../log/include/clogmacros.h"
#include <boost/shared_ptr.hpp>
#include <string>

#include "../../config.h"
#include "../include/coisinputmanager.h"


namespace Gnoll
{
	namespace Input
	{

		OISJoystickListener::OISJoystickListener()
		{
		}


		OISJoystickListener::~OISJoystickListener()
		{
		}


		bool OISJoystickListener::buttonPressed( const OIS::JoyStickEvent &arg, int button )
		{
			Gnoll::Log::CLogModule::getInstancePtr()->logMessage("JOYSTICK: Button pressed");

			Messages::MessageType buttonPressedType(OISJoystickListener::MESSAGE_TYPE_JOYSTICK_BUTTON_PRESSED());

			Gnoll::Input::JoystickEvent joystickEvent(arg, button, Gnoll::Input::Axis);

			shared_ptr<boost::any> data (new boost::any(joystickEvent) ) ;
			shared_ptr<CMessage>  message (new CMessage(buttonPressedType, data ));

			CMessageModule::getInstancePtr()->getMessageManager()->queueMessage(message);

			return true;
		}


		bool OISJoystickListener::buttonReleased( const OIS::JoyStickEvent &arg, int button )
		{
			Gnoll::Log::CLogModule::getInstancePtr()->logMessage("JOYSTICK: Button released");

			Messages::MessageType buttonReleasedType(OISJoystickListener::MESSAGE_TYPE_JOYSTICK_BUTTON_RELEASED());

			Gnoll::Input::JoystickEvent joystickEvent(arg, button, Gnoll::Input::Axis);

			shared_ptr<boost::any> data (new boost::any(joystickEvent) ) ;
			shared_ptr<CMessage>  message (new CMessage(buttonReleasedType, data ));

			CMessageModule::getInstancePtr()->getMessageManager()->queueMessage(message);

			return true;
		}


		bool OISJoystickListener::axisMoved( const OIS::JoyStickEvent &arg, int axis )
		{
			Gnoll::Log::CLogModule::getInstancePtr()->logMessage("JOYSTICK: axis moved");

			Messages::MessageType axisMovedType(OISJoystickListener::MESSAGE_TYPE_JOYSTICK_AXIS_MOVED());

			Gnoll::Input::JoystickEvent joystickEvent(arg, axis, Gnoll::Input::Axis);

			shared_ptr<boost::any> data (new boost::any(joystickEvent) ) ;
			shared_ptr<CMessage>  message (new CMessage(axisMovedType, data ));

			CMessageModule::getInstancePtr()->getMessageManager()->queueMessage(message);

			return true;
		}
	}
}

