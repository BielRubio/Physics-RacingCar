#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//Initialize variables

	camView = (CAM_VIEW)0;
	currentLap = LAPS::START;
	race = RACESTATE::DEFAULT;
	state = GAMESTATE::TITLESCREEN;

	//Initialize map
	AddCheckPoint({ 0, 0, 0 }, 90, 20, White, 2, false);//Goal
	//road
	deathZone = Cube(2000, 25, 2000);
	deathZone.SetPos(0, -50, 0);
	pb_deathZone = App->physics->AddBody(deathZone, 0);
	pb_deathZone->SetId(-1);

	road1 = Cube(20, 0.2, 300); //10,150
	road1.SetPos(0, 0, 0);
	road1.color = { 0.5,1,1 };
	pb_road1 = App->physics->AddBody(road1, 0);
	
	

	road2 = Cube(50, 0.2, 50);
	road2.SetPos(-25 + 10, 0, 150+25); //-15,175
	road2.color = { 0.5f,0.5f,0.5f };
	pb_road2 = App->physics->AddBody(road2, 0);
	AddCheckPoint({ 0, 0, 150 }, 90, 20, {0.5,1,1}, 3, false);
	

	road3 = Cube(100, 0.2, 20);
	road3.SetPos(-15 - 75, 0, 175 + 15); // -125, 210
	road3.color = { 0.5f,0.5f,0.5f };
	pb_road3 = App->physics->AddBody(road3, 0);

	road4 = Cube(50, 0.2, 50);
	road4.SetPos(-125 - 40, 0,210 - 5); // -180,230
	road4.color = { 0.5f,0.5f,0.5f };
	pb_road4 = App->physics->AddBody(road4, 0);

	road5 = Cube(20, 0.2, 50);
	road5.SetPos(-180, 0, 230 + 25); // -170,255
	road5.color = { 0.5f,0.5f,0.5f };
	pb_road5 = App->physics->AddBody(road5, 0);
	AddCheckPoint({ -180, 0, 230 }, 90, 20, { 0.5,1,1 }, 4, false);

	road6 = Cube(20, 0.2, 100);
	road6.SetPos(-180, 5.3, 255+50.6);
	road6.color = { 0.5f,0.5f,0.5f };
	road6.SetRotation(-10, { 1,0,0 });
	pb_road6 = App->physics->AddBody(road6, 0);

	joint1 = Cylinder(0.7, 20);
	joint1.SetPos(-180, 13.4, 355);
	joint1.color = { 0.5f,0.5f,0.5f };
	pb_joint1 = App->physics->AddBody(joint1, 0);

	road7 = Cube(20, 0.2, 150);
	road7.SetPos(-180, 14, 355 + 75);
	road7.color = { 0.5f,0.5f,0.5f };
	pb_road7 = App->physics->AddBody(road7, 0);

	road8 = Cube(50, 0.2, 20);
	road8.SetPos(-180 - 35, 14, 495);
	road8.color = { 0.5f,0.5f,0.5f };
	pb_road7 = App->physics->AddBody(road8, 0);

	road9 = Cube(20, 0.2, 50);
	road9.SetPos(-180 - 50, 14, 495- 35);
	road9.color = { 0.5f,0.5f,0.5f };
	pb_road9 = App->physics->AddBody(road9, 0);

	road10 = Cube(100, 0.2, 20);
	road10.SetPos(-280 - 10, 14, 495 - 50);
	road10.color = { 0.5f,0.5f,0.5f };
	pb_road10 = App->physics->AddBody(road10, 0);

	road11 = Cube(50, 0.2, 50);
	road11.SetPos(-290 - 75, 14, 445 - 15);
	road11.color = { 0.5f,0.5f,0.5f };
	pb_road11 = App->physics->AddBody(road11, 0);
	AddCheckPoint({ -290, 14, 445 }, 180, 20, { 0.5,1,1 }, 5, false);

	road12 = Cube(10, 0.2, 50);
	road12.SetPos(-390 + 5, 14, 445 - 40 - 25);
	road12.color = { 0.5f,0.5f,0.5f };
	pb_road12 = App->physics->AddBody(road12, 0);

	road13 = Cube(50, 0.2, 50);
	road13.SetPos(-290 - 75, 14, 330);
	road13.color = { 0.5f,0.5f,0.5f };
	pb_road13 = App->physics->AddBody(road13, 0);

	road14 = Cube(10, 0.2, 50);
	road14.SetPos(-390 + 45, 14, 330 - 50);
	road14.color = { 0.5f,0.5f,0.5f };
	pb_road14 = App->physics->AddBody(road14, 0);

	road15 = Cube(50, 0.2, 50);
	road15.SetPos(-290 - 75, 14, 330 - 100);
	road15.color = { 0.5f,0.5f,0.5f };
	pb_road15 = App->physics->AddBody(road15, 0);

	road16 = Cube(10, 0.2, 20);
	road16.SetPos(-290 - 75, 14, 230 - 35);
	road16.color = { 0.5f,0.5f,0.5f };
	pb_road16 = App->physics->AddBody(road16, 0);
	AddCheckPoint({ -365, 14, 230 }, 270, 20, { 0.5,1,1 }, 6, false);

	road17 = Cube(70, 0.2, 120);
	road17.SetPos(-290 - 75, 0, 120);
	road17.color = { 0.5f,0.5f,0.5f };
	pb_road17 = App->physics->AddBody(road17, 0);

	road18 = Cube(20, 0.2, 70);
	road18.SetPos(-290 - 75, 0, 25);
	road18.color = { 0.5f,0.5f,0.5f };
	pb_road18 = App->physics->AddBody(road18, 0);

	road19 = Cube(40, 0.2, 20);
	road19.SetPos(-280 - 75, 0, -20);
	road19.color = { 0.3,1,1 };
	pb_road19 = App->physics->AddBody(road19, 0);
	pb_road19->body->setFriction(0.2);

	road20 = Cube(40, 0.2, 20);
	road20.SetPos(-260 - 75, 0, -40);
	road20.color = { 0.3,1,1 };
	pb_road20 = App->physics->AddBody(road20, 0);
	pb_road20->body->setFriction(0.2);

	road21 = Cube(40, 0.2, 20);
	road21.SetPos(-240 - 75, 0, -60);
	road21.color = { 0.3,1,1 };
	pb_road21 = App->physics->AddBody(road21, 0);
	pb_road21->body->setFriction(0.2);

	road22 = Cube(40, 0.2, 20);
	road22.SetPos(-220 - 75, 0, -80);
	road22.color = { 0.3,1,1 };
	pb_road22 = App->physics->AddBody(road22, 0);
	pb_road22->body->setFriction(0.2);

	road23 = Cube(40, 0.2, 20);
	road23.SetPos(-200 - 75, 0, -100);
	road23.color = { 0.3,1,1 };
	pb_road23 = App->physics->AddBody(road23, 0);
	pb_road23->body->setFriction(0.2);

	road24 = Cube(80, 0.2, 80);
	road24.SetPos(-180 - 75, 0, -150);
	road24.color = { 0.3,1,1 };
	pb_road24 = App->physics->AddBody(road24, 0);
	pb_road24->body->setFriction(0.2);

	roundab1 = Cylinder(20,30);
	roundab1.SetPos(-180 - 75, 0, -150);
	roundab1.SetRotation(90, { 0,0,1 });
	roundab1.color = Magenta;
	pb_roundab1 = App->physics->AddBody(roundab1, 0);

	barrier1 = Cube(20, 4, 1);
	barrier1.SetPos(-180 - 105, 2, -150);
	barrier1.color = Red;
	pb_barrier1 = App->physics->AddBody(barrier1, 5);

	hinge = Cube(20, 1, 1);
	hinge.SetPos(-180 - 105, 4.5, -150);
	hinge.color = Magenta;
	pb_hinge = App->physics->AddBody(hinge, 0);

	App->physics->AddConstraintHinge(*pb_barrier1, *pb_hinge, { -180 - 105, 4.5, -150 }, { -180 - 105, 4.5, -150 }, { 1,0,0 }, {1,0,0},true);

	/*float aux[16];
	pb_barrier1->GetTransform(aux);
	barrier1.SetPos(pb_barrier1->GetPos().getX(), pb_barrier1->GetPos().getY(), pb_barrier1->GetPos().getZ());
	barrier1.SetRotation(acos(aux[5]),{1,0,0});*/

	road25 = Cube(20, 0.2, 120);
	road25.SetPos(-210 - 75, 0, -250);
	road25.color = { 0.5f,0.5f,0.5f };
	pb_road25 = App->physics->AddBody(road25, 0);
	AddCheckPoint({ -285, 0, -250 }, 270, 20, { 0.5,1,1 }, 7, false);

	road26 = Cube(60, 0.2, 20);
	road26.SetPos(-170 - 95, 0, -320);
	road26.color = { 0.5f,0.5f,0.5f };
	pb_road26 = App->physics->AddBody(road26, 0);

	road27 = Cube(20, 20, 20);
	road27.SetPos(-170 - 55, -9, -320);
	road27.SetRotation(5, { 0,0,1 });
	road27.color = { 0.5f,0.5f,0.5f };
	pb_road27 = App->physics->AddBody(road27, 0);

	road28 = Cube(20, 20, 20);
	road28.SetPos(-170, -9, -320);
	road28.SetRotation(-5, { 0,0,1 });
	road28.color = { 0.5f,0.5f,0.5f };
	pb_road28 = App->physics->AddBody(road28, 0);

	road29 = Cube(60, 0.2, 20);
	road29.SetPos(-130, 0, -320);
	road29.color = { 0.5f,0.5f,0.5f };
	pb_road29 = App->physics->AddBody(road29, 0);

	road30 = Cube(50, 0.2, 50);
	road30.SetPos(-75, 0, -305);
	road30.color = { 0.5f,0.5f,0.5f };
	pb_road30 = App->physics->AddBody(road30, 0);

	road31 = Cube(20, 0.2, 80);
	road31.SetPos(-60, 0, -240);
	road31.color = { 0.5f,0.5f,0.5f };
	pb_road31 = App->physics->AddBody(road31, 0);

	road32 = Cube(80, 0.2, 50);
	road32.SetPos(-30, 0, -175);
	road32.color = { 0.5f,0.5f,0.5f };
	pb_road32 = App->physics->AddBody(road32, 0);

	//Finish
	fpoleL = Cylinder(0.3, 20);
	fpoleL.SetPos(10, 10, 0);
	fpoleL.SetRotation(90, { 0,0,1 });
	fpoleL.color = Black;
	pb_fpoleL = App->physics->AddBody(fpoleL, 0);

	fpoleR = Cylinder(0.3, 20);
	fpoleR.SetPos(-10, 10, 0);
	fpoleR.SetRotation(90, { 0,0,1 });
	fpoleR.color = Black;
	pb_fpoleR = App->physics->AddBody(fpoleR, 0);

	flag = Cube(20, 6, 0.3);
	flag.SetPos(0,15,0);
	flag.color = White;
	pb_flag = App->physics->AddBody(flag, 0);

	timer.Start();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

update_status ModuleSceneIntro::Update(float dt)
{
	//Change Cam view
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_STATE::KEY_DOWN) camView = CAM_VIEW::BEHIND_PLAYER;
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_STATE::KEY_DOWN) camView = CAM_VIEW::LOCK_PLAYER;
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_STATE::KEY_DOWN) camView = CAM_VIEW::FREE_CAM;
		
	switch (camView)
// Update
	{
	case CAM_VIEW::BEHIND_PLAYER:
		App->camera->LookAt({ App->player->pos.x + App->player->fwVec.x * 10, App->player->pos.y, App->player->pos.z + App->player->fwVec.z * 10 });
		App->camera->Position = { App->player->pos.x - App->player->fwVec.x * 12,App->player->pos.y + 7,App->player->pos.z - App->player->fwVec.z * 12 };
		break;
	case CAM_VIEW::LOCK_PLAYER:
		App->camera->LookAt(App->player->pos);
		break;
	}

	if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_STATE::KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_STATE::KEY_DOWN) && state == (GAMESTATE)0) state = GAMESTATE::GAMEPLAY;
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		Reset();
	}
	//Auto win
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		race = RACESTATE::WIN;
		state = GAMESTATE::END;
		currentLap = LAPS::LAST;
	}
	//Auto lose
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		race = RACESTATE::LOSE;
		state = GAMESTATE::END;
	}
	//Render map

	//Road
	road1.Render();
	road2.Render();
	road3.Render();
	road4.Render();
	road5.Render();
	road6.Render();
	joint1.Render();
	road7.Render();
	road8.Render();
	road9.Render();
	road10.Render();
	road11.Render();
	road12.Render();
	road13.Render();
	road14.Render();
	road15.Render();
	road16.Render();
	road17.Render();
	road18.Render();
	road19.Render();
	road20.Render();
	road21.Render();
	road22.Render();
	road23.Render();
	road24.Render();
	roundab1.Render();
	barrier1.Render();
	hinge.Render();
	road25.Render();
	road26.Render();
	road27.Render();
	road28.Render();
	road29.Render();
	road30.Render();
	road31.Render();
	road32.Render();

	//Finish
	fpoleL.Render();
	fpoleR.Render();
	flag.Render();



	p2List_item<CheckPoint>* c = checkPoints.getFirst();
	while (c != NULL) {
		if (c->data.checked == false) {
			c->data.colorBody.Render();
		}
		c = c->next;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	
}

void ModuleSceneIntro::AddCheckPoint(vec3 position, float angle, float width, Color color, int id, bool startChecked) {
	//Sensor
	Cube sensor;
	sensor.size = { 2,2,width };
	sensor.SetPos(position.x, position.y + 1, position.z);
	sensor.SetRotation(angle, { 0, 1, 0 });

	float radius = width / 2;
	vec3 positionLeftFlag(0, position.y + 2.9, radius);
	vec3 positionRightFlag(0, position.y + 2.9, -radius);
	float theta = angle * M_PI / 180;
	positionLeftFlag.x += radius * sin(theta); positionLeftFlag.z = positionLeftFlag.z * cos(theta);
	positionRightFlag.x -= radius * sin(theta); positionRightFlag.z = positionRightFlag.z * cos(theta);

	//// Sensor left mark
	//Cylinder leftFlag;
	//leftFlag.radius = 2;
	//leftFlag.height = 5;
	//leftFlag.color = color;
	//leftFlag.SetPos(positionLeftFlag.x + position.x, positionLeftFlag.y - 1, positionLeftFlag.z + position.z);
	//leftFlag.SetRotation(90, { 0, 0, 1 });

	//// Sensor right mark
	//Cylinder rightFlag;
	//rightFlag.radius = 2;
	//rightFlag.height = 5;
	//rightFlag.color = color;
	//rightFlag.SetPos(positionRightFlag.x + position.x, positionRightFlag.y - 1, positionRightFlag.z + position.z);
	//rightFlag.SetRotation(90, { 0, 0, 1 });
	//// Create Checkpoint
	CheckPoint sensorCP;
	sensorCP.body = App->physics->AddBody(sensor, 0.0f);
	sensorCP.body->SetAsSensor(true);
	sensorCP.body->SetId(id);
	sensorCP.angle = angle;
	sensorCP.checked = startChecked;
	/*sensorCP.leftC = leftFlag;
	sensorCP.rightC = rightFlag;*/
	sensorCP.colorBody = sensor;
	sensorCP.colorBody.color = color;

	/*Cylinders.add(sensorCP.leftC);
	App->physics->AddBody(sensorCP.leftC, 0);
	Cylinders.add(sensorCP.rightC);
	App->physics->AddBody(sensorCP.rightC, 0);*/

	checkPoints.add(sensorCP);
}

void ModuleSceneIntro::Reset() {
	state = GAMESTATE::TITLESCREEN;
	currentLap = LAPS::START;
	race = RACESTATE::DEFAULT;

	checkPoints.getFirst()->data.checked = false;
	p2List_item<CheckPoint>* checklist = checkPoints.getFirst()->next;
	while (checklist != NULL) {
		checklist->data.checked = true;
		checklist = checklist->next;
	}

	App->player->countdown = 3;
	App->player->loseCondition = 20;

	App->player->lastCheckPoint = 0;
	App->player->currentTime = 0;
	App->player->Respawn();
}

