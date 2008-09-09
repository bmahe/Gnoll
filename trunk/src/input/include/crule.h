/***************************************************************************
 *   Copyright (C) 2008 by Paf                                             *
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


/*-------------------------CInputEventsTranslator.h-------------------------*\
|   An input rule based on a dynamicobject			             |
|                                                                            |
|   Changelog :                                                              |
|               15/08/2008 - WT  - Initial release                           |
\*--------------------------------------------------------------------------*/


#include "../include/ctranslationevents.h"

#include <map>
#include <string>


#ifndef __CRULE_H__
#define __CRULE_H__


namespace Gnoll
{

	namespace Input
	{

		class CRule
		{
		public:

			/**
			 * Constructor
			 */
			CRule(const std::string &instanceName);


			/**
			 * Update the conditions
			 */
			void updateRule(const ActionEvent &ae);

			/**
			 * Check if the conditions are enabled
			 */
			bool checkConditions();

			/**
			 * Fire the rule action
			 */
			bool fireAction() const;

			/**
			 * Accessor to the rule trigger
			 */
			std::string getTrigger() const { return m_trigger; }


		private:

			// Conditions enabling the rule
			std::map<std::string, bool> m_conditions;

			// Exceptions disabling the rule
			std::map<std::string, bool> m_exceptions;

			// Trigger fire the action
			std::string m_trigger;

			// Action message to be fired
			std::string m_action;
		};

	}
}


#endif
