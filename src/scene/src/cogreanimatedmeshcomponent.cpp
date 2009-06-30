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


/*--------------------------COgreAnimatedMeshComponent---------------------*\
|   This is a component able to display Ogre models that are animated       |
|                                                                           |
|                                                                           |
\*-------------------------------------------------------------------------*/


#include "../../dynamicobject/include/float.h"
#include "../../graphic/include/cgraphicmodule.h"
#include "../../log/include/clogmacros.h"
#include "../../graphic/include/cgraphicmodule.h"
#include "../../stats/include/cstatsmodule.h"

#include "../../core/include/cmessagetype.h"
#include "../../core/include/cmessagemodule.h"
#include "../include/cogreanimatedmeshcomponent.h"
#include "../include/gobject.h"

using namespace Gnoll::DynamicObject;
using namespace Gnoll::Log;

namespace Gnoll {

	namespace Scene {

		class OgreAnimatedMeshListener : public CMessageListener
		{
			private:
				COgreAnimatedMeshComponent* component;

			public:

				/**
				 * This is a constructor
				 */
				OgreAnimatedMeshListener(COgreAnimatedMeshComponent* _component) : component(_component) {}

				/**
				 * This is a destructor
				 */
				virtual ~OgreAnimatedMeshListener() {}

				/**
				 * This method is called in order to process a message
				 * @param message The message this method will have to process
				 */
				virtual void handle (shared_ptr<CMessage> message)
				{
					float lasttime = Gnoll::Stats::CStatsModule::getInstancePtr()->getRenderTime();

					component->update(lasttime/1000.0f);
				}
		};


		COgreAnimatedMeshComponent::COgreAnimatedMeshComponent()
		{
			this->m_parentPageName = "";
			this->m_parent = NULL;
		}


		COgreAnimatedMeshComponent::~COgreAnimatedMeshComponent()
		{
		}


		Gnoll::Scene::GObject * COgreAnimatedMeshComponent::getParent() const
		{
			return m_parent;
		}


		void COgreAnimatedMeshComponent::setParent(Gnoll::Scene::GObject *m_parent)
		{
			this->m_parent = m_parent;
		}


		const std::string& COgreAnimatedMeshComponent::getParentPageName() const
		{
			return m_parentPageName;
		}


		void COgreAnimatedMeshComponent::setParentPage(const std::string& m_parentPageName)
		{
			this->m_parentPageName = m_parentPageName;
		}


		void COgreAnimatedMeshComponent::init(Gnoll::Scene::GObject* parent, CPage* page)
		{

			/**
			 * A parent must exist
			 */
			if (parent == NULL)
			{
				GNOLL_LOG() << this->getInstance() << " object initialized without any parent";
				return;
			}

			/**
			 * A parent page must exist
			 */
			if (page == NULL)
			{
				GNOLL_LOG() << parent->getInstance() << ":" << this->getInstance() << " object initialized without any parent page" << "\n";
				return;
			}

			this->m_parent         = parent;
			this->m_parentPageName = page->getInstance();

			shared_ptr< Gnoll::DynamicObject::String > meshName = this->getAttribute < Gnoll::DynamicObject::String > (COgreAnimatedMeshComponent::ATTRIBUTE_MESH());
			string meshNameStr(*meshName);

			SceneNode *parentNode = page->getPageRootNode();
			SceneNode *meshNode   = parentNode->createChildSceneNode( m_parentPageName + "_" + this->getInstance() );

			std::string entName = m_parentPageName + "_" + this->getInstance() + COgreAnimatedMeshComponent::ENTITY_SUFFIX();
			Ogre::SceneManager* sm = Gnoll::Graphic::CGraphicModule::getInstancePtr()->getSceneManager();

			Ogre::Entity *ent = sm->createEntity( entName, meshNameStr );
			meshNode->attachObject( ent );


			/**
			 * Check if its an animated mesh and get back the set of AnimationState
			 */
			AnimationStateSet *animationStateSet = ent->getAllAnimationStates();
			if(animationStateSet == 0)
			{
				GNOLL_LOG() << parent->getInstance() << ":" << this->getInstance() << " is not a animated mesh !" << "\n";
			}

			/**
		     * Select the first by default
			 */
			if(animationStateSet != 0)
			{
				AnimationStateIterator iter = animationStateSet->getAnimationStateIterator();
				AnimationState* animationState = iter.getNext();
				std::cout << animationState->getAnimationName() << std::endl;
				animationState->setEnabled(true);
				animationState->setLoop(true);
			}

			shared_ptr< Gnoll::DynamicObject::Float > zero ( new Gnoll::DynamicObject::Float(0.0f));
			shared_ptr< Gnoll::DynamicObject::Float > one ( new Gnoll::DynamicObject::Float(1.0f));



			/**
			 * Scale the object
			 */

			shared_ptr< Gnoll::DynamicObject::Float > scaleX = this->getAttributeOrDefault < Gnoll::DynamicObject::Float > (COgreAnimatedMeshComponent::ATTRIBUTE_SCALE_X(), one);
			shared_ptr< Gnoll::DynamicObject::Float > scaleY = this->getAttributeOrDefault < Gnoll::DynamicObject::Float > (COgreAnimatedMeshComponent::ATTRIBUTE_SCALE_Y(), one);
			shared_ptr< Gnoll::DynamicObject::Float > scaleZ = this->getAttributeOrDefault < Gnoll::DynamicObject::Float > (COgreAnimatedMeshComponent::ATTRIBUTE_SCALE_Z(), one);


			meshNode->setScale(*scaleX, *scaleY, *scaleZ);


			/**
			 * Rotate the object
			 */

			shared_ptr< Gnoll::DynamicObject::Float > rotX = this->getAttributeOrDefault < Gnoll::DynamicObject::Float > (COgreAnimatedMeshComponent::ATTRIBUTE_ROTATE_X(), zero);
			shared_ptr< Gnoll::DynamicObject::Float > rotY = this->getAttributeOrDefault < Gnoll::DynamicObject::Float > (COgreAnimatedMeshComponent::ATTRIBUTE_ROTATE_Y(), zero);
			shared_ptr< Gnoll::DynamicObject::Float > rotZ = this->getAttributeOrDefault < Gnoll::DynamicObject::Float > (COgreAnimatedMeshComponent::ATTRIBUTE_ROTATE_Z(), zero);

			meshNode->rotate(Ogre::Vector3(1,0,0), Ogre::Radian(*rotX));
			meshNode->rotate(Ogre::Vector3(0,1,0), Ogre::Radian(*rotY));
			meshNode->rotate(Ogre::Vector3(0,0,1), Ogre::Radian(*rotZ));


			/**
			 * Translate the object
			 */
			shared_ptr< Gnoll::DynamicObject::Float > posX = this->getAttributeOrDefault < Gnoll::DynamicObject::Float > (COgreAnimatedMeshComponent::ATTRIBUTE_POSITION_X(), zero);
			shared_ptr< Gnoll::DynamicObject::Float > posY = this->getAttributeOrDefault < Gnoll::DynamicObject::Float > (COgreAnimatedMeshComponent::ATTRIBUTE_POSITION_Y(), zero);
			shared_ptr< Gnoll::DynamicObject::Float > posZ = this->getAttributeOrDefault < Gnoll::DynamicObject::Float > (COgreAnimatedMeshComponent::ATTRIBUTE_POSITION_Z(), zero);

			Ogre::Vector3 posGObject(*posX, *posY, *posZ);
			meshNode->translate( posGObject, Ogre::Node::TS_LOCAL);


			/**
			 * Register the listener
			 */
			CMessageModule*  messageModule  = CMessageModule::getInstancePtr();
			CMessageManager* messageManager = messageModule->getMessageManager();

			componentListener = shared_ptr<CMessageListener> (new OgreAnimatedMeshListener(this));
			messageManager->addListener ( componentListener, Gnoll::Core::CMessageType("GRAPHIC_FRAME_RENDERED") );
		}


		 void COgreAnimatedMeshComponent::exit()
		 {
			GNOLL_LOG() << "Gobject " << this->m_parent->getInstance() << " is DEinitializing its component named " << this->getInstance() << "\n";
			if (this->m_parentPageName == "")
			{

				GNOLL_LOG() << m_parent->getInstance() << ":" << this->getInstance() << " object cannot be DEinitialized without a parent page" << "\n";
				return;
			}

			string instanceNameStr(this->getInstance());

			std::string entName = m_parentPageName + "_" + instanceNameStr  + COgreAnimatedMeshComponent::ENTITY_SUFFIX();
			Ogre::SceneManager* sm = Gnoll::Graphic::CGraphicModule::getInstancePtr()->getSceneManager();

			SceneNode* meshNode = sm->getSceneNode( m_parentPageName + "_" + instanceNameStr );
			meshNode->detachObject( entName );

			sm->destroyEntity(entName);
			sm->destroySceneNode( m_parentPageName + "_" + instanceNameStr  );

			/**
			 * Unregister the listener
			 */
			CMessageModule*  messageModule  = CMessageModule::getInstancePtr();
			CMessageManager* messageManager = messageModule->getMessageManager();

			messageManager->delListener ( componentListener, Gnoll::Core::CMessageType("GRAPHIC_FRAME_RENDERED") );
		}

		void COgreAnimatedMeshComponent::update(float time)
		{
			string instanceNameStr(this->getInstance());

			std::string entName = m_parentPageName + "_" + instanceNameStr  + COgreAnimatedMeshComponent::ENTITY_SUFFIX();
			Ogre::SceneManager* sm = Gnoll::Graphic::CGraphicModule::getInstancePtr()->getSceneManager();

			SceneNode* meshNode = sm->getSceneNode( m_parentPageName + "_" + instanceNameStr );
			Entity* ent = (Entity*) meshNode->getAttachedObject(entName);

			/**
			 * Update all animation that are enabled
			 */
			ConstEnabledAnimationStateIterator iter = ent->getAllAnimationStates()->getEnabledAnimationStateIterator();
			while(iter.hasMoreElements())
			{
				AnimationState* animationState = iter.getNext();
				animationState->addTime(time);
			}

		}

		shared_ptr<xmlpp::Document> COgreAnimatedMeshComponent::serializeXML()
		{
			shared_ptr<xmlpp::Document> document = DynamicObject::serializeXML();
			xmlpp::Element* root = document->get_root_node();

			if (root != NULL)
			{
				root->set_name( COgreAnimatedMeshComponent::DYNAMIC_OBJECT_NAME() );
			}

			return document;
		}

	}
}