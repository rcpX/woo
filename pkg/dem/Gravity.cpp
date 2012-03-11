#include<yade/pkg/dem/Gravity.hpp>
#include<yade/pkg/dem/Clump.hpp>
#include<yade/core/Field.hpp>
#include<yade/core/Scene.hpp>
// #include<boost/regex.hpp>

YADE_PLUGIN(dem,(Gravity)(AxialGravity) /* (CentralGravityEngine)(AxialGravityEngine)(HdapsGravityEngine)*/ );

void Gravity::pyHandleCustomCtorArgs(py::tuple& args, py::dict& kw){
	if(py::len(args)==1){ gravity=py::extract<Vector3r>(args[0]); args=py::tuple(); }
}

void Gravity::run(){
	const bool trackEnergy(unlikely(scene->trackEnergy));
	const Real dt(scene->dt);
	FOREACH(const shared_ptr<Node>& n, field->nodes){
		//if(mask!=0 && (b->groupMask & mask)==0) continue;
		//scene->forces.addForce(b->getId(),gravity*b->state->mass);
		// work done by gravity is "negative", since the energy appears in the system from outside
		DemData& dyn(n->getData<DemData>());

		// clumps skipped
		if(dyn.isClump()) continue;

		dyn.force+=gravity*dyn.mass;
		if(trackEnergy){
			Real e=0;
			if(dyn.isBlockedNone()){
				#if 1
					e=-gravity.dot(dyn.vel)*dyn.mass*dt;
				#else
					// attempt to better estimate current velocity from acceleration :-|
					e=-gravity.dot(dyn.vel+.5*dt*(dyn.force/dyn.mass))*dyn.mass*dt;
				#endif
			}
			else { for(int ax:{0,1,2}){ if(!(dyn.isBlockedAxisDOF(ax,false))) e-=gravity[ax]*dyn.vel[ax]*dyn.mass*dt; } }
			scene->energy->add(e,"grav",gravWorkIx,EnergyTracker::IsIncrement);
		}
	}
}

void AxialGravity::run(){
	axisDir.normalize();
	FOREACH(const shared_ptr<Node>& n, field->nodes){
		/* http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html */
		const Vector3r& x0=n->pos;
		const Vector3r& x1=axisPt;
		const Vector3r x2=axisPt+axisDir;
		Vector3r closestAxisPoint=x1+(x2-x1) * /* t */ (-(x1-x0).dot(x2-x1))/((x2-x1).squaredNorm());
		Vector3r toAxis=closestAxisPoint-x0; toAxis.normalize();
		if(toAxis.squaredNorm()==0) continue;
		DemData& dyn(n->getData<DemData>());
		dyn.addForceTorque(accel*dyn.mass*toAxis,Vector3r::Zero());
	}
}


#if 0
void CentralGravityEngine::run(){
	const Vector3r& centralPos=Body::byId(centralBody)->state->pos;
	FOREACH(const shared_ptr<Body>& b, *scene->bodies){
		if(!b || b->isClump() || b->getId()==centralBody) continue; // skip clumps and central body
		if(mask!=0 && (b->groupMask & mask)==0) continue;
		Real F=accel*b->state->mass;
		Vector3r toCenter=centralPos-b->state->pos; toCenter.normalize();
		scene->forces.addForce(b->getId(),F*toCenter);
		if(reciprocal) scene->forces.addForce(centralBody,-F*toCenter);
	}
}

Vector2i HdapsGravityEngine::readSysfsFile(const string& name){
	char buf[256];
	ifstream f(name.c_str());
	if(!f.is_open()) throw std::runtime_error(("HdapsGravityEngine: unable to open file "+name).c_str());
	f.read(buf,256);f.close();
	const boost::regex re("\\(([0-9+-]+),([0-9+-]+)\\).*");
   boost::cmatch matches;
	if(!boost::regex_match(buf,matches,re)) throw std::runtime_error(("HdapsGravityEngine: error parsing data from "+name).c_str());
	//cerr<<matches[1]<<","<<matches[2]<<endl;
	return Vector2i(lexical_cast<int>(matches[1]),lexical_cast<int>(matches[2]));

}

void HdapsGravityEngine::run(){
	if(!calibrated) { calibrate=readSysfsFile(hdapsDir+"/calibrate"); calibrated=true; }
	Real now=PeriodicEngine::getClock();
	if(now-lastReading>1e-3*msecUpdate){
		Vector2i a=readSysfsFile(hdapsDir+"/position");
		lastReading=now;
		a-=calibrate;
		if(abs(a[0]-accel[0])>updateThreshold) accel[0]=a[0];
		if(abs(a[1]-accel[1])>updateThreshold) accel[1]=a[1];
		Quaternionr trsf(AngleAxisr(.5*accel[0]*M_PI/180.,-Vector3r::UnitY())*AngleAxisr(.5*accel[1]*M_PI/180.,-Vector3r::UnitX()));
		gravity=trsf*zeroGravity;
	}
	GravityEngine::run();
}

#endif