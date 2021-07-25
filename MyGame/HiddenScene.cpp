#include "HiddenScene.h"

CHiddenScene::CHiddenScene(int map, int camx, int camy, int playerx, int playery, int player_in_x, int player_in_y)
{
	this->map = map;
	hidden_scene_cam_x = camx;
	hidden_scene_cam_y = camy;
	player_pos_out_pipe_x = playerx;
	player_pos_out_pipe_y = playery;
	player_pos_in_x = player_in_x;
	player_pos_in_y = player_in_y;
}

CHiddenScene::~CHiddenScene()
{
	this->map = 0;
	hidden_scene_cam_x = 0;
	hidden_scene_cam_y = 0;
	player_pos_out_pipe_x = 0;
	player_pos_out_pipe_y = 0;
	player_pos_in_x = 0;
	player_pos_in_y = 0;
}
