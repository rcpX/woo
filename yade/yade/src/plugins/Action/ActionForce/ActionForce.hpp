/***************************************************************************
 *   Copyright (C) 2004 by Olivier Galizzi                                 *
 *   olivier.galizzi@imag.fr                                               *
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTIONFORCE_HPP__
#define __ACTIONFORCE_HPP__

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Action.hpp"
#include "Vector3.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

class ActionForce : public Action
{

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Attributes											///
///////////////////////////////////////////////////////////////////////////////////////////////////

	public : Vector3r force;

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor/Destructor									///
///////////////////////////////////////////////////////////////////////////////////////////////////

	/*! Constructor */
	public : ActionForce();

	/*! Destructor */
	public : virtual ~ActionForce();

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Methods											///
///////////////////////////////////////////////////////////////////////////////////////////////////
	
	public : virtual void add(const shared_ptr<Action>& a);
	public : virtual void sub(const shared_ptr<Action>& a);
	public : virtual void reset();
	public : virtual shared_ptr<Action> clone();
		
///////////////////////////////////////////////////////////////////////////////////////////////////
/// Serialization										///
///////////////////////////////////////////////////////////////////////////////////////////////////

	REGISTER_CLASS_NAME(ActionForce);
	public    : virtual void registerAttributes();
	
///////////////////////////////////////////////////////////////////////////////////////////////////
/// Indexable											///
///////////////////////////////////////////////////////////////////////////////////////////////////

	REGISTER_CLASS_INDEX(ActionForce);
	
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

REGISTER_SERIALIZABLE(ActionForce,false);

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __ACTIONFORCE_HPP__

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

