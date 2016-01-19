#include "ProtoController.h"

void ProtoController::init() {
	setLight(0, { -100, 100, 200 }, { 1, 1, 1 });
	shadowsOn();
	t = Toroid({ 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 }, { 1, 1, 1, .75f }, 12, 12, 125, 45);
	t.setDiffuseMap("ship_plate_rainbow.jpg");
	t.setBumpMap("ship_plate_rainbow.jpg");
	t.setTextureScale({ 0.5f, 0.35f });
	t.setSpecularMaterial({ 1, 1, 1, 1 });
	t.setShininess(9);
	pcg = new ProtoGeomComposite();
	//pcg->init();

	plane = ProtoPlane({ 0 }, { 0 }, { 500, 500 }, { 1, 1, 1, 1 }, 1, 1);
	t.setSpecularMaterial({ 1, 1, 1, 1 });
	t.setShininess(9);
	plane.setDiffuseMap("ship_plate.jpg");
	plane.setTextureScale({ .2f, .2f });
	plane.setBumpMap("ship_plate.jpg");
	plane.setSpecularMaterial({ 1, 1, 1, 1 });
	plane.setShininess(39);

	testBullet();

	class A{
	};
	
	std::unique_ptr<A> testVal(new A());
	A* conversion = testVal.get();

	//stitchTiles("C:\\Users\\Ira\\Dev\\Protobyte_0.1.5_quark\\Protobyte\\Projects\\Output\\TestRender01_2016_1_18_23_3_3", 24);
}

void ProtoController::run() {
	
	if (getFrameCount() == 32){
		//trace(getFrameCount());
		save("TestRender01", 4);
	}
}

void ProtoController::display() {
	static float theta = 0.0f;

	setLight(0, { sin(theta += PI / 540.0f)*200.0f, 100, 200 }, { 1, 1, 1 });

	beginArcBall();
	//translate(0, 0, -400);

	push();
	translate(0, 0, -300);
	//rotate(180, 0, 1, 0);
	scale(3000);
	plane.display();
	pop();

	rotate(getFrameCount()*.3, { 0, 0, 1 });


	push();
	translate(-300, 200, 290);
	rotate(getFrameCount()*.2, { 1, .2f, 0 });
	t.display();
	pop();

	push();
	translate(300, 200, 290);
	rotate(-getFrameCount()*.2, { 1, .75f, 0 });
	t.display();
	pop();

	push();
	translate(-300, -200, 290);
	rotate(getFrameCount()*1.2, { 1, .05f, 0 });
	t.display();
	pop();

	push();
	translate(300, -200, 290);
	rotate(-getFrameCount()*.2, { 1, 0, 0 });
	rotate(-getFrameCount()*2.2, { 0, 1, 0 });
	rotate(-getFrameCount()*1.2, { 0, 0, 1 });
	t.display();
	pop();

	translate(0, -100, -150);
	//pcg->display();
	endArcBall();



	//compositeObj.display();  --> push, trans, obj1.display(), pop, push, trans, obj2.display(), pop,
}

// Key and Mouse Events
void ProtoController::keyPressed(){
}

void ProtoController::mousePressed(){
}

void ProtoController::mouseRightPressed(){
}

void ProtoController::mouseReleased(){
}

void ProtoController::mouseRightReleased(){
}

void ProtoController::mouseMoved(){
}

void ProtoController::mouseDragged(){
}

// Window Events
void ProtoController::onResized(){
}

void ProtoController::onClosed(){
}

void ProtoController::testBullet(){
	///-----includes_end-----

	int i;
	///-----initialization_start-----

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));

	///-----initialization_end-----

	///create a few basic rigid bodies
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -56, 0));

	{
		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
	}


	{
		//create a dynamic rigidbody

		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar	mass(1.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

		startTransform.setOrigin(btVector3(2, 10, 0));

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		dynamicsWorld->addRigidBody(body);
	}



	/// Do some simulation


	///-----stepsimulation_start-----
	for (i = 0; i < 100; i++)
	{
		dynamicsWorld->stepSimulation(1.f / 60.f, 10);

		//print positions of all objects
		for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(trans);

			}
			else
			{
				trans = obj->getWorldTransform();
			}
			printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		}
	}

	///-----stepsimulation_end-----

	//cleanup in the reverse order of creation/initialization

	///-----cleanup_start-----

	//remove the rigidbodies from the dynamics world and delete them
	for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < collisionShapes.size(); j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();

	///-----cleanup_end-----
	//printf("Press a key to exit\n");
	//getchar();
}