/*************************************************************************
*  Copyright (C) 2009 by Vincent Richefeu				 *
*  Vincent.Richefeu@hmg.inpg.fr                                          *
*                                                                        *
*  This program is free software; it is licensed under the terms of the  *
*  GNU General Public License v2 or later. See file LICENSE for details. *
*************************************************************************/

#include"BasicViscoelasticRelationships.hpp"
#include<yade/pkg-dem/SimpleViscoelasticBodyParameters.hpp>
#include<yade/pkg-dem/ViscoelasticInteraction.hpp>
#include<yade/pkg-dem/SpheresContactGeometry.hpp>
#include<yade/core/Omega.hpp>
#include<yade/core/MetaBody.hpp>


BasicViscoelasticRelationships::BasicViscoelasticRelationships()
{
}


void BasicViscoelasticRelationships::registerAttributes()
{
}


void BasicViscoelasticRelationships::go(  const shared_ptr<PhysicalParameters>& b1 // SimpleViscoelasticBodyParameters
					, const shared_ptr<PhysicalParameters>& b2 // SimpleViscoelasticBodyParameters
					, const shared_ptr<Interaction>& interaction)
{
    if(interaction->interactionPhysics) return;

    SimpleViscoelasticBodyParameters* sdec1 = static_cast<SimpleViscoelasticBodyParameters*>(b1.get());
    SimpleViscoelasticBodyParameters* sdec2 = static_cast<SimpleViscoelasticBodyParameters*>(b2.get());

    interaction->interactionPhysics = shared_ptr<ViscoelasticInteraction>(new ViscoelasticInteraction());
    ViscoelasticInteraction* contactPhysics = YADE_CAST<ViscoelasticInteraction*>(interaction->interactionPhysics.get());

    // Check that cn is dimensionless
    if (sdec1->cn >= 1.0 || sdec2->cn >= 1.0) std::cout << "Warning: non dimensionless value for cn" << std::endl;

    // FIXME Arbitrary ponderations... (Should be replaced by parameters that depends on groupMasks)
    contactPhysics->kn = 0.5 * (sdec1->kn + sdec2->kn);
    contactPhysics->ks = 0.5 * (sdec1->ks + sdec2->ks);
    contactPhysics->cn = 0.5 * (sdec1->cn + sdec2->cn);
    contactPhysics->cs = 0.0; // not viscosity in the tangent direction

    // in fact, at this stage cn is a ponderation of the critical value cn_crit = 2sqrt(kn*meff)

    shared_ptr<Body> bdy1 = (*((Omega::instance().getRootBody().get())->bodies))[ interaction->getId1() ];
    shared_ptr<Body> bdy2 = (*((Omega::instance().getRootBody().get())->bodies))[ interaction->getId2() ];
    double m1,m2;
    
    if (bdy1->isClumpMember())
    {
        const shared_ptr<Body>& clump = (*((Omega::instance().getRootBody().get())->bodies))[ bdy1->clumpId ];
        RigidBodyParameters* clumpRBP=YADE_CAST<RigidBodyParameters*> ( clump->physicalParameters.get() );
        m1 = clumpRBP->mass; 
    }
    else
    { m1 = sdec1->mass ; }
    
    if (bdy2->isClumpMember())
    {
        const shared_ptr<Body>& clump = (*((Omega::instance().getRootBody().get())->bodies))[ bdy2->clumpId ];
        RigidBodyParameters* clumpRBP=YADE_CAST<RigidBodyParameters*> ( clump->physicalParameters.get() );
        m2 = clumpRBP->mass;
    }
    else
    { m2 = sdec2->mass; }

    if (!bdy1->isDynamic) m1 *= 1e6;
    if (!bdy2->isDynamic) m2 *= 1e6;

    //cout << "m1 = " << m1 << endl;
    //cout << "m2 = " << m2 << endl;

    contactPhysics->cn *= 2.0 * sqrt(contactPhysics->kn * ((m1 * m2) / (m1 + m2)));
 
    contactPhysics->tangensOfFrictionAngle = std::tan(std::min(sdec1->frictionAngle, sdec2->frictionAngle)); 

    contactPhysics->shearForce = Vector3r(0,0,0);
    contactPhysics->prevNormal = Vector3r(0,0,0);

}

YADE_PLUGIN();