/*************************************************************************
*  Copyright (C) 2004 by Olivier Galizzi                                 *
*  olivier.galizzi@imag.fr                                               *
*                                                                        *
*  This program is free software; it is licensed under the terms of the  *
*  GNU General Public License v2 or later. See file LICENSE for details. *
*************************************************************************/

#include"ElasticContactLaw.hpp"
#include<yade/pkg-dem/ScGeom.hpp>
#include<yade/pkg-dem/FrictPhys.hpp>
#include<yade/pkg-dem/DemXDofGeom.hpp>
#include<yade/core/Omega.hpp>
#include<yade/core/Scene.hpp>
#include<yade/core/Scene.hpp>

YADE_PLUGIN((Law2_ScGeom_FrictPhys_Basic)(Law2_Dem3DofGeom_FrictPhys_Basic)(ElasticContactLaw)(Law2_Dem6DofGeom_FrictPhys_Beam));

ElasticContactLaw::ElasticContactLaw() : GlobalEngine()
{
	sdecGroupMask=1;
	momentRotationLaw = true;
	neverErase = false;
	#ifdef SCG_SHEAR
		useShear=false;
	#endif
}




void ElasticContactLaw::action(Scene* rootBody)
{
	if(!functor) functor=shared_ptr<Law2_ScGeom_FrictPhys_Basic>(new Law2_ScGeom_FrictPhys_Basic);
	functor->momentRotationLaw=momentRotationLaw;
	functor->sdecGroupMask=sdecGroupMask;
	#ifdef SCG_SHEAR
		functor->useShear=useShear;
	#endif
	functor->neverErase=neverErase;
	FOREACH(const shared_ptr<Interaction>& I, *rootBody->interactions){
		if(!I->isReal()) continue;
		#ifdef YADE_DEBUG
			// these checks would be redundant in the functor (LawDispatcher does that already)
			if(!dynamic_cast<ScGeom*>(I->interactionGeometry.get()) || !dynamic_cast<FrictPhys*>(I->interactionPhysics.get())) continue;	
		#endif
			functor->go(I->interactionGeometry, I->interactionPhysics, I.get(), rootBody);
	}
}


CREATE_LOGGER(Law2_ScGeom_FrictPhys_Basic);
void Law2_ScGeom_FrictPhys_Basic::go(shared_ptr<InteractionGeometry>& ig, shared_ptr<InteractionPhysics>& ip, Interaction* contact, Scene* ncb){
	Real dt = Omega::instance().getTimeStep();

			int id1 = contact->getId1(), id2 = contact->getId2();
			// FIXME: mask handling should move to LawFunctor itself, outside the functors
			if( !(Body::byId(id1,ncb)->getGroupMask() & Body::byId(id2,ncb)->getGroupMask() & sdecGroupMask) ) return;
			ScGeom*    currentContactGeometry= static_cast<ScGeom*>(ig.get());
			FrictPhys* currentContactPhysics = static_cast<FrictPhys*>(ip.get());			
						
			if(currentContactGeometry->penetrationDepth <0)
			{
				if (neverErase) {
					currentContactPhysics->shearForce = Vector3r::ZERO;
					currentContactPhysics->normalForce = Vector3r::ZERO;}
				else 	ncb->interactions->requestErase(id1,id2);
				return;
			}	
	
			State* de1 = Body::byId(id1,ncb)->state.get();
			State* de2 = Body::byId(id2,ncb)->state.get();

			Vector3r& shearForce 			= currentContactPhysics->shearForce;
	
			// no need for this, initialized to Vector3r::ZERO in NormShearPhys ctor
			// if (contact->isFresh(ncb)) shearForce=Vector3r(0,0,0);
					
			Real un=currentContactGeometry->penetrationDepth;
			TRVAR3(currentContactGeometry->penetrationDepth,de1->se3.position,de2->se3.position);
			currentContactPhysics->normalForce=currentContactPhysics->kn*std::max(un,(Real) 0)*currentContactGeometry->normal;
	
			#ifdef SCG_SHEAR
				if(useShear){
					currentContactGeometry->updateShear(de1,de2,dt);
					shearForce=currentContactPhysics->ks*currentContactGeometry->shear;
				} else {
			#endif
					currentContactGeometry->updateShearForce(shearForce,currentContactPhysics->ks,currentContactPhysics->prevNormal,de1,de2,dt);
			#ifdef SCG_SHEAR
				}
			#endif

			
			// PFC3d SlipModel, is using friction angle. CoulombCriterion
			Real maxFs = currentContactPhysics->normalForce.SquaredLength() * std::pow(currentContactPhysics->tangensOfFrictionAngle,2);
			if( shearForce.SquaredLength() > maxFs )
			{
				Real ratio = Mathr::Sqrt(maxFs) / shearForce.Length();
				shearForce *= ratio;
				#ifdef SCG_SHEAR
					// in this case, total shear displacement must be updated as well
					if(useShear) currentContactGeometry->shear*=ratio;
				#endif
			}
	
			applyForceAtContactPoint(-currentContactPhysics->normalForce-shearForce , currentContactGeometry->contactPoint , id1 , de1->se3.position , id2 , de2->se3.position , ncb);
			currentContactPhysics->prevNormal = currentContactGeometry->normal;
}

// same as elasticContactLaw, but using Dem3DofGeom
void Law2_Dem3DofGeom_FrictPhys_Basic::go(shared_ptr<InteractionGeometry>& ig, shared_ptr<InteractionPhysics>& ip, Interaction* contact, Scene*){
	Dem3DofGeom* geom=static_cast<Dem3DofGeom*>(ig.get());
	FrictPhys* phys=static_cast<FrictPhys*>(ip.get());
	Real displN=geom->displacementN();
	if(displN>0){ scene->interactions->requestErase(contact->getId1(),contact->getId2()); return; }
	phys->normalForce=phys->kn*displN*geom->normal;
	Real maxFsSq=phys->normalForce.SquaredLength()*pow(phys->tangensOfFrictionAngle,2);
	Vector3r trialFs=phys->ks*geom->displacementT();
	if(trialFs.SquaredLength()>maxFsSq){ geom->slipToDisplacementTMax(sqrt(maxFsSq)); trialFs*=sqrt(maxFsSq/(trialFs.SquaredLength()));}
	phys->shearForce=trialFs;
	applyForceAtContactPoint(phys->normalForce+trialFs,geom->contactPoint,contact->getId1(),geom->se31.position,contact->getId2(),geom->se32.position,scene);
}

// same as elasticContactLaw, but using Dem3DofGeom
void Law2_Dem6DofGeom_FrictPhys_Beam::go(shared_ptr<InteractionGeometry>& ig, shared_ptr<InteractionPhysics>& ip, Interaction* contact, Scene* scene){
	// normal & shear forces
	Dem6DofGeom* geom=static_cast<Dem6DofGeom*>(ig.get());
	FrictPhys* phys=static_cast<FrictPhys*>(ip.get());
	Real displN=geom->displacementN();
	phys->normalForce=phys->kn*displN*geom->normal;
	phys->shearForce=phys->ks*geom->displacementT();
	applyForceAtContactPoint(phys->normalForce+phys->shearForce,geom->contactPoint,contact->getId1(),geom->se31.position,contact->getId2(),geom->se32.position,scene);
	// bend&twist:
	Vector3r bend; Real twist;
	geom->bendTwistAbs(bend,twist);
	Vector3r tt=bend*phys->kn+geom->normal*twist*phys->kn;
	cerr<<twist<<";"<<bend<<endl;
	scene->forces.addTorque(contact->getId1(),tt);
	scene->forces.addTorque(contact->getId2(),-tt);
}
