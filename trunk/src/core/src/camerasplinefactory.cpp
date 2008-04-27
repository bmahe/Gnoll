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


/*-------------------------------CameraSplineFactory-----------------------*\
|   This is a first person camera factory                                   |
|                                                                           |
|   Changelog :                                                             |
|               04/12/2008 - Gabriel - Initial release                      |
\*-------------------------------------------------------------------------*/

#include "../include/camerasplinefactory.h"
#include "../include/cameraspline.h"
#include "../include/defaultcamerasplinelistener.h"
#include "../include/cmessagelistenercamera.h"
#include "../include/cmessage.h"
#include "../include/cmessagetype.h"
#include "../include/cmessagemanager.h"
#include "../../input/include/coisinputmodule.h"
#include "../../input/include/ctranslationevents.h"
#include "../../input/include/cinputmouseevents.h"

namespace Gnoll
{
	namespace Core
	{
		boost::shared_ptr<Camera> CameraSplineFactory::createCamera(const Glib::ustring& instanceName)
		{
			CMessageModule* messageModule = CMessageModule::getInstancePtr();

			shared_ptr<CMessageListenerCamera> listenerInput = shared_ptr<CMessageListenerCamera>(
															   new Gnoll::Core::DefaultCameraSplineListener);
			messageModule->getMessageManager()->addListener ( listenerInput, CMessageType(Gnoll::Input::ACTION_EVENT_TYPE) );

			boost::shared_ptr<Camera> pCam = boost::shared_ptr<Camera>(new CameraSpline(instanceName));

			listenerInput->setCamera(pCam);

			return pCam;
		}
	};
};


