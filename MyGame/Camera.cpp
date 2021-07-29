#include "Camera.h"
#include "Game.h"
#include "Utils.h"
#include "Boundary.h"
#include "MarioStateFly.h"
#include "MarioStateDrop.h"
#include "MarioStateJump.h"
#include "MarioOverworldState.h"
#include "Pipe.h"
#include "Ground.h"
#include "Box.h"
#include "Brick.h"
#include "HUD.h"


CCamera::CCamera(float y,float width, float height)
{
	this->width = CAM_WIDTH;
	this->height = CAM_HEIGHT;
	isEnable = true;
	start_y = y;
	player = CGame::GetInstance()->GetPlayer();
	InitCamera();
	hiddenscenes = NULL;
	inactive = false;
}

void CCamera::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void CCamera::Render()
{
	//DebugOut(L"cam y %f \n", y);
	RenderBoundingBox();
}

void CCamera::SetState(int state)
{
	CGameObject::SetState(state);
}

void CCamera::CalculateCamX(float& cx)
{
	//player = CGame::GetInstance()->GetPlayer();
	cx = player->x - this->width / 2;

	if (cx < 0) cx = CAM_START_X;
}

void CCamera::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {
	
	if (player == NULL) return;

	CGameObject::Update(dt);

	if (CGame::GetInstance()->current_scene == INTRO||inactive)
	{
		vx = 0;
		vy = 0;
		return;
	}
	  
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (player->state != MARIO_STATE_DIE && player->marioState != CMarioState::walking_overworld.GetInstance())
	{
		cam_center_X = x + (width / 2 )- (MARIO_RACOON_BBOX_WIDTH/2);
		cam_center_Y = y + (height / 2) - (MARIO_RACOON_BBOX_HEIGHT/2);
        
		FollowPlayerHorizontally();
		FollowPlayerVertically();
		CalcPotentialCollisions(colObject, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
        
		float nx = 0, ny;
		FilterCollision(coEvents, coEventsResult,nx,ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBoundary*>(e->obj))
				{
					if (e->ny < 0)
					{
						isReachBoundaryBottom = true;
					}
				}
				else {
						if (e->nx != 0)
						{
							FollowPlayerHorizontally();
							x += dx;
						}
						if (e->ny != 0)
						{
							FollowPlayerVertically();
							y += dy;
						}
				}
				
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else {
		inactive = true;
	}
}

void CCamera::FollowPlayerHorizontally()
{
	if (state == CAMERA_STATE_HIDDEN_SCENE3)
	{
		vx = CAMERA_AUTO_VELOCITY_X;
		player->MovingMarioWithCamera();
	}
	else {
		if ((player->vx > 0 && player->x < cam_center_X) // walk right
			|| (player->vx < 0 && player->x > cam_center_X))// walk left
		{
			vx = 0.0f;
		}
		else {
			vx = player->vx;
		}
	}
}

void CCamera::FollowPlayerVertically()
{
	if (state == CAMERA_STATE_HIDDEN_SCENE3)
	{
		vx = CAMERA_AUTO_VELOCITY_X;
		player->MovingMarioWithCamera();
	}
	
	if (player->GetState() == CMarioState::fly.GetInstance() && player->GetLevel() == MARIO_LEVEL_RACOON)
	{
		isReachBoundaryBottom = false;
	}

	if (state == CAMERA_STATE_HIDDEN_SCENE1) {
		vy = 0;
		isReachBoundaryBottom = true;
	}

	if (isReachBoundaryBottom == false)
	{
		if ((player->vy < 0 && player->y < cam_center_Y) ||
			(player->vy > 0 && player->y > cam_center_Y) )
		{
			vy = player->vy;
		}
		else {
			vy = 0.0f;
		}
	}
}

void CCamera::AutoMoveToSecretScreen()
{
	isReachBoundaryBottom = false;
	inactive = false;
	CGame::GetInstance()->GetMainCamera()->SetPosition(SECRET_PIPE_X_1, SECRET_PIPE_Y_1);
	HUD::GetInstance()->SetPosition(HUD_POSITION_Y);
}

void CCamera::GetCamPos(float& x, float& y, float& cam_width, float& cam_height)
{
	x = this->x;
	y = this->y;
	cam_width = this->width;
	cam_height = this->height;
}

void CCamera::InitCamera()
{
	float cx;
	CalculateCamX(cx);

	SetPosition(cx, start_y);
	SetState(CAMERA_STATE_NORMAL);
	isReachBoundaryBottom = false;
}


void CCamera::AdjustPositionToHiddenScene()
{
	SetState(CAMERA_STATE_HIDDEN_SCENE1);
	if (CGame::GetInstance()->current_scene == WORLD1_3_MAP)
	{
		SetState(CAMERA_STATE_HIDDEN_SCENE3);
	}

	SetPosition((float)hiddenscenes->hidden_scene_cam_x, (float)hiddenscenes->hidden_scene_cam_y);
	HUD::GetInstance()->SetPosition(HUD_POSITION_Y+45);
	inactive = false;
}

void CCamera::GoBackToNormal()
{

	float cy = start_y;
	if (CGame::GetInstance()->current_scene == WORLD1_3_MAP)
	{
		cy = 10;
	}

	float cx;
	CalculateCamX(cx);
	isReachBoundaryBottom = false;
	inactive = false;
	SetPosition(cx, cy);

	HUD::GetInstance()->SetPosition(HUD_POSITION_Y);
	SetState(CAMERA_STATE_NORMAL);
}

void CCamera::MoveToHiddenScene()
{
	float cx;
	CalculateCamX(cx);
	SetPosition(cx, MAGIC_WHISTLE_SCENE_Y);
	HUD::GetInstance()->SetPosition(HUD_POSITION_Y+45);
	inactive = true;
}