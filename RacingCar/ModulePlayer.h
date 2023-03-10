#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 5.0f * DEGTORAD
#define BRAKE_POWER 50.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void Respawn();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	vec3 pos;
	vec3 fwVec;

	int lastCheckPoint = 0;
	int lastCP = 7;
	
	bool letMovement = false; 

	float countdown, loseCondition, currentTime;
};