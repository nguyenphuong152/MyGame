#pragma once

class CHiddenScene {
public:
	int map;

	int hidden_scene_cam_x;
	int hidden_scene_cam_y;

	int player_pos_out_pipe_x;
	int player_pos_out_pipe_y;

	int player_pos_in_x;
	int player_pos_in_y;

	CHiddenScene(int map, int camx, int camy, int playerx, int playery, int player_inx,int player_iny);
	//void GetHiddenSceneData(int& map, int& camx, int& camy, int& playerx, int& playery, int &player_inx, int &player_iny);
	~CHiddenScene();
};