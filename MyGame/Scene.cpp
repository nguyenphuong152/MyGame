#include "Scene.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	key_handler = NULL;
	this->id = id;
	this->sceneFilePath = filePath;
}