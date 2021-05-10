#include "MapObjects.h"
#include "Ground.h"
#include "GameObject.h"
#include "Brick.h"
#include "Box.h"
#include "Boundary.h"
#include "Camera.h"
#include "RedVenusFireTrap.h"
#include "GreenVenusFireTrap.h"
#include "tinyxml.h"
#include "Koopas.h"
#include "Goomba.h"
#include "ParaGoomba.h"
#include "Piranha.h"
#include "ObjectBoundary.h"
#include "ParaKoopa.h"
#include "Coin.h"
#include "PowerUp.h"
#include "One-upMushroom.h"
#include "BreakableBrick.h"
#include "Switch.h"

CMapObjects* CMapObjects::__instance = NULL;

CMapObjects* CMapObjects::GetInstance()
{
	if (__instance == NULL) __instance = new CMapObjects();
	else return __instance;
}

void CMapObjects::GenerateObject(const char* mapFilePath,vector<LPGAMEOBJECT>& objects)
{
	TiXmlDocument doc(mapFilePath);
	if (!doc.LoadFile())
	{
		DebugOut(L"[ERR] TMX FAILED %s\n", ToLPCWSTR(doc.ErrorDesc()));
		return;
	}

	TiXmlElement* root = doc.RootElement();
	TiXmlElement* layer = nullptr;

	for (layer = root->FirstChildElement(); layer != NULL; layer = layer->NextSiblingElement())
	{
		//render object
		const char* attributeName = layer->Attribute("name");
		TiXmlElement* element = layer->FirstChildElement();
		if (attributeName != NULL)
		{
			CGameObject* obj = NULL;
			float x, y, width, height;
			if (strcmp(attributeName, "Solid") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);
					element->QueryFloatAttribute("width", &width);
					element->QueryFloatAttribute("height", &height);

					obj = new CGround(width, height);
					obj->SetPosition(x, y);
					objects.push_back(obj);

					element = element->NextSiblingElement();
				}
			}
			else if (strcmp(attributeName, "Ghost") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);
					element->QueryFloatAttribute("width", &width);
					element->QueryFloatAttribute("height", &height);

					obj = new CBox(width, height);
					obj->SetPosition(x, y);
					objects.push_back(obj);

					element = element->NextSiblingElement();
				}
			}
			else if (strcmp(attributeName, "Boundary") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);
					element->QueryFloatAttribute("width", &width);
					element->QueryFloatAttribute("height", &height);

					obj = new CBoundary(width, height);
					obj->SetPosition(x, y);
					objects.push_back(obj);

					element = element->NextSiblingElement();
				}
			}
			else if (strcmp(attributeName, "ObjectBoundary") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);
					element->QueryFloatAttribute("width", &width);
					element->QueryFloatAttribute("height", &height);

					obj = new CObjectBoundary(width, height);
					obj->SetPosition(x, y);
					objects.push_back(obj);

					element = element->NextSiblingElement();
				}
			}
			else if (strcmp(attributeName, "Camera") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);
					element->QueryFloatAttribute("width", &width);
					element->QueryFloatAttribute("height", &height);

					obj = CCamera::GetInstance();
					CCamera::GetInstance()->SetProperty(5300, y, width, height); //sua vi tri cam
					objects.push_back(obj);

					element = element->NextSiblingElement();
				}
			}
			else if (strcmp(attributeName, "QuestionBlocks") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);

					CGameObject* item = NULL;
					if (strcmp(element->Attribute("name"), "bcoin") == 0)
					{
						item = new CCoin(CoinType::jumping_coin, x, y);
						objects.push_back(item);
					}
					else if (strcmp(element->Attribute("name"), "powerup") == 0)
					{
						item = new CPowerUp(x, y);
						objects.push_back(item);
					}
					else if (strcmp(element->Attribute("name"), "one-up") == 0)
					{
						item = new COneUpMushroom(x, y);
						const char* aniRaw = element->Attribute("type");
						int ani = atoi(aniRaw);
						item->SetAnimation(ani);
						objects.push_back(item);
					}
					else if (strcmp(element->Attribute("name"), "switch") == 0)
					{
						item = new CSwitch();
						const char* aniRaw = element->Attribute("type");
						int ani = atoi(aniRaw);
						item->SetAnimation(ani);
						objects.push_back(item);
					}

					if (strcmp(element->Attribute("type"), "1") == 0)
					{
						obj = new CBrick(item, y, BrickType::question_brick);
					}
					else
					{
						obj = new CBrick(item, y, BrickType::twinkle_brick);
					}
					obj->SetPosition(x, y);
					objects.push_back(obj);
					

					element = element->NextSiblingElement();
				}
			}
			else if (strcmp(attributeName, "Enemy") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);
					const char* enemyName = element->Attribute("name");
					const char* aniRaw = element->Attribute("type");
					int ani = atoi(aniRaw);

					if (strcmp(enemyName, "red_venus")  == 0)
					{
						obj = new CRedVenusFireTrap();
					}
					else if (strcmp(enemyName, "red_koopa") == 0)
					{
						obj = new CKoopas();
					}
					else if (strcmp(enemyName, "goomba")  == 0)
					{	
						obj = new CGoomBa();
					}
					else if (strcmp(enemyName, "para-goomba") == 0)
					{
						obj = new CParaGoomba();
					}
					else if (strcmp(enemyName, "piranha")== 0)
					{
						obj = new CPiranha();
					}else if (strcmp(enemyName, "green_venus")  == 0)
					{
						obj = new CGreenVenusFireTrap();
					}
					else if (strcmp(enemyName, "green_para-koopa") == 0)
					{
						obj = new CParaKoopa();
					}

					obj->SetAnimation(ani);
					obj->SetPosition(x, y);
					objects.push_back(obj);

					element = element->NextSiblingElement();
				}
			}
			else if (strcmp(attributeName, "Coin") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);

					obj = new CCoin(CoinType::spinning_coin, x, y);
					objects.push_back(obj);

					element = element->NextSiblingElement();
				}
			}
			else if (strcmp(attributeName, "Brick") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);

					obj = new CBreakableBrick(x, y);
					objects.push_back(obj);

					element = element->NextSiblingElement();
				}
			}
		}
	}
}