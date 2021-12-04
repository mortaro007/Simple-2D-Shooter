#include "Tema1.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "lab_m1/Tema1/transform2D.h"
#include "object2D.h"

using namespace std;
using namespace m1;

#define Base_Color {0.811, 0.843, 0.396}
#define Border_Color {0.219, 0.219, 0.219}
#define Projectile_Color {0.403, 0.572, 0.815}
#define Map_Color {0.666, 0.333, 0.470}
#define Wall_Color {0.294, 0.725, 0.294}
#define Enemy_Color {0.949, 0.611, 0.831}
#define Enemy2_Color {0.831, 0.015, 0.945}
#define EnemyFace_Color {0.168, 0.211, 0.694}
#define Health_Color {0.913, 0.168, 0.168}
#define Constraints_Color {0, 0, 0}

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);

	cx = squareSide / 2;
	cy = squareSide / 2;
	translateX = 0;
	translateY = 0;
	Projectile_Movement_X = 0;
	Projectile_Movement_Y = 0;
	check = 0;
	checkScale = 0;
	scaleX = 1;
	scaleY = 1;
	angularStep = 0;

	// Initialize seeding for random number generator
	srand(static_cast <unsigned> (time(0)));

	// Variables
	raza_1 = 0.08;
	raza_2 = raza_1 - 0.01;
	raza_3 = 0.03;
	raza_4 = raza_3 - 0.01;
	mouse_X = 0;
	mouse_Y = 0;
	mouse_Angle = 0;
	PI = 3.1415926f;
	squareSide = 0.07;
	mapSide = 4;
	checkProjectile = 0;
	checkMousePointer = 0;
	checkMouseAngle = 0;
	checkPosition = 0;
	squareEnemy1 = 0.15;
	Timer = 0;
	projectile_Distance = 0;
	projectile_max = 5;
	enemy_Angle = 0;
	wallHit = 0;
	scor = 0;
	gameOver = false;
	check_mouseX = 0; check_mouseY = 0;
	cpx = 0; cpy = 0;
	w = 0.5; h = 0.1;
	checkY = 0; checkX = 0;
	newPosX = 0; newPosY = 0;
	w_enemy = 0.1; h_enemy = 0.025;
	posEnemy1_X = 0; posEnemy1_Y = 0;
	posEnemy2_X = 0; posEnemy2_Y = 0;
	checkEnemies = 0; checkEnemies2 = 0;
	enemy_positionX = 0; enemy_positionY = 0;
	enemy_position2X = 0; enemy_position2Y = 0;
	posEnemy1_aux_X = 0; posEnemy1_aux_Y = 0;
	posEnemy2_aux_X = 0; posEnemy2_aux_Y = 0;
	projectileHit = 0; projectileHit2 = 0;
	pozObsX = 0.5; pozObsY = 0.5;
	pozObs1 = 1;  pozObs2 = 1;
	healthWidth = 0.2; healthHeight = 0.1;
	health1 = 0; health2 = 0; health3 = 0;
	pozObs1 = 1;  pozObs2 = 1;
	playerEnemy = 0; playerEnemy2 = 0;
	healthCheck = 0; healthCheck2 = 0;
	pozObs3 = 1.5; pozObs4 = 1.5;
	pozObs5 = 2; pozObs6 = 1;
	pozObs7 = 2.5; pozObs8 = 0.5;
	posObsS = 2.75; posObsSS = 2.75;
	pozObs9 = 1; pozObs10 = 0.2;
	pozObs11 = 2; pozObs12 = 0.2;
	pozObs13 = 0.5; pozObs14 = 2;
	pozObs15 = 0.25; pozObs16 = 2.5;
	pozObs17 = 1.1; pozObs18 = 2.5;
	upX = 0; upY = 4;
	downX = 0; downY = 0;
	leftX = 0; leftY = 0;
	rightX = 4; rightY = 0;
	copyX = 0; copyY = 0;
	w1 = 0.1; h1 = 4;

	logicSpace.x = 0; logicSpace.y = 0;
	logicSpace.width = 1; logicSpace.height = 1;

	Mesh* circle1 = object2D::CreateCircle("circle1", raza_1, glm::vec3(Border_Color)); // Cerc principal
	AddMeshToList(circle1);

	Mesh* circle2 = object2D::CreateCircle("circle2", raza_2, glm::vec3(Base_Color));   // Cerc principal
	AddMeshToList(circle2);

	Mesh* circle3 = object2D::CreateCircle("circle3", raza_3, glm::vec3(Border_Color)); // Cerc secundar 1
	AddMeshToList(circle3);

	Mesh* circle4 = object2D::CreateCircle("circle4", raza_3, glm::vec3(Border_Color)); // Cerc secundar 2
	AddMeshToList(circle4);

	Mesh* circle5 = object2D::CreateCircle("circle5", raza_4, glm::vec3(Base_Color));   // Cerc secundar 1
	AddMeshToList(circle5);

	Mesh* circle6 = object2D::CreateCircle("circle6", raza_4, glm::vec3(Base_Color));   // Cerc secundar 2
	AddMeshToList(circle6);

	Mesh* projectile = object2D::CreateSquare("projectile", corner, squareSide, glm::vec3(Projectile_Color)); // Proiectil
	AddMeshToList(projectile);

	Mesh* wall = object2D::CreateRectangle("wall", corner, w, h, glm::vec3(Wall_Color)); // Perete
	AddMeshToList(wall);

	Mesh* map = object2D::CreateSquare("map", corner, mapSide, glm::vec3(Map_Color)); // Mapa
	AddMeshToList(map);

	Mesh* square1 = object2D::CreateSquare("square1", corner, squareEnemy1, glm::vec3(Enemy_Color)); // Fata inamic 1
	AddMeshToList(square1);

	Mesh* square2 = object2D::CreateSquare("square2", corner, squareEnemy1, glm::vec3(Enemy2_Color)); // Fata inamic 2
	AddMeshToList(square2);

	Mesh* healthFill = object2D::CreateRectangle("healthFill", corner, healthWidth, healthHeight, glm::vec3(Health_Color)); // Viata full
	AddMeshToList(healthFill);

	Mesh* healthOutline = object2D::CreateRectangleOutline("healthOutline", corner, healthWidth, healthHeight, glm::vec3(Health_Color)); // Viata empty
	AddMeshToList(healthOutline);

	Mesh* walls = object2D::CreateRectangle("walls", corner, w, h, glm::vec3(0, 0, 0)); // Perete
	AddMeshToList(walls);

	Mesh* walls1 = object2D::CreateRectangle("walls1", corner, w1, h1, glm::vec3(1, 1, 0)); // Obj
	AddMeshToList(walls1);

	Mesh* walls2 = object2D::CreateRectangle("walls2", corner, w, h, glm::vec3(0.666, 0.333, 0.470)); // Obj
	AddMeshToList(walls2);

	Mesh* squareBig = object2D::CreateRectangle("squareBig", corner, 0.75, 0.75, glm::vec3(0.925, 0.945, 0.231)); // Obj
	AddMeshToList(squareBig);

	Mesh* RectangleBig2 = object2D::CreateRectangle("RectangleBig2", corner, 2.5, 0.15, glm::vec3(0.925, 0.945, 0.231)); // Obj
	AddMeshToList(RectangleBig2);

	Mesh* RectangleBig3 = object2D::CreateRectangle("RectangleBig3", corner, 0.45, 0.15, glm::vec3(0.878, 0.435, 0)); // Obj
	AddMeshToList(RectangleBig3);

	Mesh* RectangleBig4 = object2D::CreateRectangle("RectangleBig4", corner, 0.45, 0.15, glm::vec3(0.419, 0.066, 0.592)); // Obj
	AddMeshToList(RectangleBig4);

	obstacles.push_back({ pozObsX, pozObsY, w, h });
	obstacles.push_back({ pozObs1, pozObs2, w, h });
	obstacles.push_back({ pozObs3, pozObs4, w, h });
	obstacles.push_back({ posObsS, posObsS, 0.75, 0.75 });
	obstacles.push_back({ pozObs5, pozObs6, w, h });
	obstacles.push_back({ pozObs7, pozObs8, w, h });
	obstacles.push_back({ pozObs9, pozObs10, w, h });
	obstacles.push_back({ pozObs11, pozObs12, w, h });
	obstacles.push_back({ pozObs13, pozObs14, 2.5, 0.15 });
	obstacles.push_back({ pozObs15, pozObs16, 0.45, 0.15 });
	obstacles.push_back({ pozObs17, pozObs18, 0.45, 0.15 });
	obstacles.push_back({ upX, upY, 4, 0.1 });
	obstacles.push_back({ leftX, leftY, 0, 4 });
	obstacles.push_back({ rightX, rightY, 0, 4 });
	obstacles.push_back({ downX, downY, 4, 0 });
}

glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty, smin;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;
	tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
	ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}

void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);
	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}

void Tema1::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tema1::Update(float deltaTimeSeconds)
{
	// Initializare X,Y pentru rezolutie
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);

	float posX = resolution.x / 2;
	float posY = resolution.y / 2;

	// Initializare X,Y pentru cursor
	glm::ivec2 mouse = window->GetCursorPosition();
	mouse_X = mouse.x;
	mouse_Y = resolution.y - mouse.y; // Se scade din res.y deoarece variabila ar fi inversat pozitia lui Y

	float raza_1_1 = raza_1 / 2 + 0.01;

	// Calcul unghi mouse
	if (mouse_X - translateX - posX >= 0)
		mouse_Angle = atan((mouse_Y - translateY - posY) / (mouse_X - translateX - posX));
	else
		mouse_Angle = PI + atan((mouse_Y - translateY - posY) / (mouse_X - translateX - posX));

	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(0, 0, 0), true);

	newPosX = logicSpace.width / 2;
	newPosY = logicSpace.height / 2;;

	posEnemy1_X = 1;
	posEnemy1_Y = 1;

	// Modul viata jucator impartit in 3 dreptunghiuri

	if (health1 == 0)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
		modelMatrix *= transform2D::Translate(translateX, translateY);
		modelMatrix *= transform2D::Translate(newPosX + newPosX / 1.1, newPosX + newPosY / 1.3);
		modelMatrix *= transform2D::Scale(0.5, 0.5);
		RenderMesh2D(meshes["healthFill"], shaders["VertexColor"], modelMatrix); // Health Fill 1
	}
	else
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
		modelMatrix *= transform2D::Translate(translateX, translateY);
		modelMatrix *= transform2D::Translate(newPosX + newPosX / 1.1, newPosX + newPosY / 1.3);
		modelMatrix *= transform2D::Scale(0.5, 0.5);
		RenderMesh2D(meshes["healthOutline"], shaders["VertexColor"], modelMatrix); // Health Outline 1
	}

	if (health2 == 0)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
		modelMatrix *= transform2D::Translate(translateX, translateY);
		modelMatrix *= transform2D::Translate(newPosX + newPosX / 0.91, newPosX + newPosY / 1.3);
		modelMatrix *= transform2D::Scale(0.5, 0.5);
		RenderMesh2D(meshes["healthFill"], shaders["VertexColor"], modelMatrix); // Health Fill 2
	}
	else
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
		modelMatrix *= transform2D::Translate(translateX, translateY);
		modelMatrix *= transform2D::Translate(newPosX + newPosX / 0.9, newPosX + newPosY / 1.3);
		modelMatrix *= transform2D::Scale(0.5, 0.5);
		RenderMesh2D(meshes["healthOutline"], shaders["VertexColor"], modelMatrix); // Health Outline 2
	}

	if (health3 == 0)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
		modelMatrix *= transform2D::Translate(translateX, translateY);
		modelMatrix *= transform2D::Translate(newPosX + newPosX / 0.77, newPosX + newPosY / 1.3);
		modelMatrix *= transform2D::Scale(0.5, 0.5);
		RenderMesh2D(meshes["healthFill"], shaders["VertexColor"], modelMatrix); // Health Fill 2
	}
	else
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
		modelMatrix *= transform2D::Translate(translateX, translateY);
		modelMatrix *= transform2D::Translate(newPosX + newPosX / 0.77, newPosX + newPosY / 1.3);
		modelMatrix *= transform2D::Scale(0.5, 0.5);
		RenderMesh2D(meshes["healthOutline"], shaders["VertexColor"], modelMatrix); // Health Outline 2
	}

	if (gameOver == true)
	{
		cout << "----------" << endl;
		cout << "Game Over" << endl;
		Exit();
	}

	if (checkEnemies == 0) // Calcul pozitie random Inamic 1
	{
		posEnemy1_X = abs(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3.5f)));
		posEnemy1_Y = abs(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3.5f)));
		posEnemy1_aux_X = posEnemy1_X;
		posEnemy1_aux_Y = posEnemy1_Y;
		checkEnemies = 1;
	}

	if (checkEnemies == 1 && playerEnemy == 0 && projectileHit == 0)
	{
		enemy_Angle = atan2(translateX + newPosX - enemy_positionX - posEnemy1_aux_X - 0.05, translateY + newPosY - enemy_positionY - posEnemy1_aux_Y - 0.05);

		if (enemy_positionX + posEnemy1_aux_X < translateX + newPosX)
			enemy_positionX += 0.3 * deltaTimeSeconds;
		else if (enemy_positionX + posEnemy1_aux_X > translateX + newPosX)
			enemy_positionX -= 0.3 * deltaTimeSeconds;

		if (enemy_positionY + posEnemy1_aux_Y < translateY + newPosY)
			enemy_positionY += 0.3 * deltaTimeSeconds;
		else if (enemy_positionY + posEnemy1_aux_Y > translateY + newPosY)
			enemy_positionY -= 0.3 * deltaTimeSeconds;

		float mijposEX = posEnemy1_X + squareEnemy1 / 6;
		float mijposEY = posEnemy1_Y + squareEnemy1 / 5;

		modelMatrix = glm::mat3(1);
		modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
		modelMatrix *= transform2D::Translate(enemy_positionX, enemy_positionY);
		modelMatrix *= transform2D::Translate(posEnemy1_aux_X + squareSide / 2, posEnemy1_aux_Y + squareSide / 2);
		modelMatrix *= transform2D::Rotate(-enemy_Angle);
		modelMatrix *= transform2D::Translate(-posEnemy1_aux_X - squareSide / 2, -posEnemy1_aux_Y - squareSide / 2);
		modelMatrix *= transform2D::Translate(posEnemy1_aux_X, posEnemy1_aux_Y);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix); // Patrat inamic 1  
	}
	else if (playerEnemy == 1)
	{
		checkEnemies = 0;
		posEnemy1_X = 0;
		posEnemy1_Y = 0;
		healthCheck = healthCheck + 1;
		if (health1 == 0)
			health1 = 1;
		if (healthCheck > 2)
			health2 = 1;
		if (healthCheck > 4)
			health3 = 1;

		if (healthCheck > 6 && health1 == 1 && health2 == 1 && health3 == 1)
		{
			gameOver = true;
		}
	}
	else if (projectileHit == 1)
	{
		scor += 1;
		checkEnemies = 0;
		projectileHit = 0;
		posEnemy1_X = 0;
		posEnemy1_Y = 0;
	}


	if (checkEnemies2 == 0) // Calcul pozitie random Inamic 2
	{
		posEnemy2_X = abs(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3.5f)));
		posEnemy2_Y = abs(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3.5f)));
		posEnemy2_aux_X = posEnemy2_X;
		posEnemy2_aux_Y = posEnemy2_Y;
		checkEnemies2 = 1;
	}

	if (checkEnemies2 == 1 && playerEnemy2 == 0 && projectileHit2 == 0)
	{
		enemy_Angle = atan2(translateX + newPosX - enemy_position2X - posEnemy2_aux_X - 0.05, translateY + newPosY - enemy_position2Y - posEnemy2_aux_Y - 0.05);

		if (enemy_position2X + posEnemy2_aux_X < translateX + newPosX)
			enemy_position2X += 0.3 * deltaTimeSeconds;
		else if (enemy_position2X + posEnemy2_aux_X > translateX + newPosX)
			enemy_position2X -= 0.3 * deltaTimeSeconds;

		if (enemy_position2Y + posEnemy2_aux_Y < translateY + newPosY)
			enemy_position2Y += 0.3 * deltaTimeSeconds;
		else if (enemy_position2Y + posEnemy2_aux_Y > translateY + newPosY)
			enemy_position2Y -= 0.3 * deltaTimeSeconds;

		float mijposEX = posEnemy2_X + squareEnemy1 / 6;
		float mijposEY = posEnemy2_Y + squareEnemy1 / 5;

		modelMatrix = glm::mat3(1);
		modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
		modelMatrix *= transform2D::Translate(enemy_position2X, enemy_position2Y);
		modelMatrix *= transform2D::Translate(posEnemy2_aux_X + squareSide / 2, posEnemy2_aux_Y + squareSide / 2);
		modelMatrix *= transform2D::Rotate(-enemy_Angle);
		modelMatrix *= transform2D::Translate(-posEnemy2_aux_X - squareSide / 2, -posEnemy2_aux_Y - squareSide / 2);
		modelMatrix *= transform2D::Translate(posEnemy2_aux_X, posEnemy2_aux_Y);
		RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix); // Patrat inamic 2  
	}
	else if (playerEnemy2 == 1)
	{
		checkEnemies2 = 0;
		posEnemy2_X = 0;
		posEnemy2_Y = 0;
		healthCheck = healthCheck + 1;
		if (health1 == 0)
			health1 = 1;
		if (healthCheck > 2)
			health2 = 1;
		if (healthCheck > 4)
			health3 = 1;

		if (healthCheck > 6 && health1 == 1 && health2 == 1 && health3 == 1)
		{
			gameOver = true;
		}
	}
	else if (projectileHit2 == 1)
	{
		scor += 1;
		checkEnemies2 = 0;
		projectileHit2 = 0;
		posEnemy2_X = 0;
		posEnemy2_Y = 0;
	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(translateX, translateY);
	modelMatrix *= transform2D::Translate(newPosX, newPosY);
	modelMatrix *= transform2D::Rotate(mouse_Angle - PI / 2);
	modelMatrix *= transform2D::Translate(-newPosX, -newPosY);
	modelMatrix *= transform2D::Translate(newPosX - raza_1_1, newPosY + raza_1 - 0.02);
	RenderMesh2D(meshes["circle6"], shaders["VertexColor"], modelMatrix); // Cerc secundar mijloc

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(translateX, translateY);
	modelMatrix *= transform2D::Translate(newPosX, newPosY);
	modelMatrix *= transform2D::Rotate(mouse_Angle - PI / 2);
	modelMatrix *= transform2D::Translate(-newPosX, -newPosY);
	modelMatrix *= transform2D::Translate(newPosX + raza_1_1, newPosY + raza_1 - 0.02);
	RenderMesh2D(meshes["circle5"], shaders["VertexColor"], modelMatrix); // Cerc secundar mijloc

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(translateX, translateY);
	modelMatrix *= transform2D::Translate(newPosX, newPosY);
	modelMatrix *= transform2D::Rotate(mouse_Angle - PI / 2);
	modelMatrix *= transform2D::Translate(-newPosX, -newPosY);
	modelMatrix *= transform2D::Translate(newPosX + raza_1_1, newPosY + raza_1 - 0.02);
	RenderMesh2D(meshes["circle4"], shaders["VertexColor"], modelMatrix); // Cerc secundar outline

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(translateX, translateY);
	modelMatrix *= transform2D::Translate(newPosX, newPosY);
	modelMatrix *= transform2D::Rotate(mouse_Angle - PI / 2);
	modelMatrix *= transform2D::Translate(-newPosX, -newPosY);
	modelMatrix *= transform2D::Translate(newPosX - raza_1_1, newPosY + raza_1 - 0.02);
	RenderMesh2D(meshes["circle3"], shaders["VertexColor"], modelMatrix); // Cerc secundar outline

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(translateX, translateY);
	modelMatrix *= transform2D::Translate(newPosX, newPosY);
	modelMatrix *= transform2D::Rotate(mouse_Angle - PI / 2);
	modelMatrix *= transform2D::Translate(-newPosX, -newPosY);
	modelMatrix *= transform2D::Translate(newPosX, newPosY);
	RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix); // Cerc principal mijloc

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(translateX, translateY);
	modelMatrix *= transform2D::Translate(newPosX, newPosY);
	modelMatrix *= transform2D::Rotate(mouse_Angle - PI / 2);
	modelMatrix *= transform2D::Translate(-newPosX, -newPosY);
	modelMatrix *= transform2D::Translate(newPosX, newPosY);
	RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix); // Cerc principal outline

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(pozObsX, pozObsY);
	RenderMesh2D(meshes["wall"], shaders["VertexColor"], modelMatrix); // Render obs1

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(pozObs1, pozObs2);
	RenderMesh2D(meshes["wall"], shaders["VertexColor"], modelMatrix); // Render obs2

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(pozObs3, pozObs4);
	RenderMesh2D(meshes["wall"], shaders["VertexColor"], modelMatrix); // Render obs3

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(posObsS, posObsSS);
	RenderMesh2D(meshes["squareBig"], shaders["VertexColor"], modelMatrix); // Render obs4

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(pozObs5, pozObs6);
	RenderMesh2D(meshes["wall"], shaders["VertexColor"], modelMatrix); // Render obs5

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(pozObs7, pozObs8);
	RenderMesh2D(meshes["wall"], shaders["VertexColor"], modelMatrix); // Render obs6

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(pozObs9, pozObs10);
	RenderMesh2D(meshes["wall"], shaders["VertexColor"], modelMatrix); // Render obs7

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(pozObs11, pozObs12);
	RenderMesh2D(meshes["wall"], shaders["VertexColor"], modelMatrix); // Render obs8

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(pozObs13, pozObs14);
	RenderMesh2D(meshes["RectangleBig2"], shaders["VertexColor"], modelMatrix); // Render obs9

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(pozObs15, pozObs16);
	RenderMesh2D(meshes["RectangleBig3"], shaders["VertexColor"], modelMatrix); // Render obs8

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(pozObs17, pozObs18);
	RenderMesh2D(meshes["RectangleBig4"], shaders["VertexColor"], modelMatrix); // Render obs9

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(upX, upY);
	RenderMesh2D(meshes["walls"], shaders["VertexColor"], modelMatrix); // Render Wall Up

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Rotate(RADIANS(-90));
	modelMatrix *= transform2D::Translate(rightX, rightY);
	RenderMesh2D(meshes["walls1"], shaders["VertexColor"], modelMatrix); // Render Wall Right

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(downX, downY);
	RenderMesh2D(meshes["walls2"], shaders["VertexColor"], modelMatrix); // Render Wall Down

	WallCol(translateX, translateY);
	ObsCol(translateX, translateY, deltaTimeSeconds);

	PlayerEnemy1Col(newPosX + translateX, newPosY + translateY, posEnemy1_aux_X + enemy_positionX, posEnemy1_aux_Y + enemy_positionY);
	PlayerEnemy2Col(newPosX + translateX, newPosY + translateY, posEnemy2_aux_X + enemy_position2X, posEnemy2_aux_Y + enemy_position2Y);

	if (checkProjectile == 1)                       // Proiectil
	{                                               // Conditii + Render + Unrender
		modelMatrix = glm::mat3(1);


		if (checkMousePointer == 0)
		{
			checkMouseAngle = mouse_Angle;
			cpx = newPosX - 0.045;
			cpy = newPosY - 0.045;
			Timer = 0;
			projectile_Distance = 0;
			checkMousePointer = 1;
		}
		else
		{
			BulletWallCol(cpx + translateX, cpy + translateY, checkMouseAngle, Timer);
			BulletEnemy1Col(cpx + translateX, cpy + translateY, checkMouseAngle, Timer);
			BulletEnemy2Col(cpx + translateX, cpy + translateY, checkMouseAngle, Timer);

			if (wallHit == 0 && projectileHit == 0)
			{
				modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
				modelMatrix *= transform2D::Translate(Timer * cos(checkMouseAngle), Timer * sin(checkMouseAngle));
				modelMatrix *= transform2D::Translate(translateX, translateY);
				modelMatrix *= transform2D::Translate(cpx, cpy);
				Timer += 0.02f;
				projectile_Distance += 0.05f;
				RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);
			}

			else if (wallHit == 1)
			{
				Timer = 0;
				checkProjectile = 0;
				wallHit = 0;
				projectileHit = 0;
				projectileHit2 = 0;
			}
		}

		if (projectile_max < projectile_Distance || projectileHit == 1 || projectileHit2 == 1)
		{
			Timer = 0;
			checkMousePointer = 0;
			checkProjectile = 0;
			projectile_Distance = 0;
			wallHit = 0;
		}
	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(0, 0);
	RenderMesh2D(meshes["map"], shaders["VertexColor"], modelMatrix); // Render background harta

	modelMatrix = glm::mat3(1);
	modelMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	modelMatrix *= transform2D::Translate(leftX, leftY);
	RenderMesh2D(meshes["walls2"], shaders["VertexColor"], modelMatrix); // Render Wall Left

	checkY = translateY + raza_1;
	checkX = translateX + raza_1;

	cout << "Scor: " << scor << endl;
}

void Tema1::BulletEnemy1Col(float projectileX, float projectileY, float projectileAngle, float projectileDistance)
{
	float projectile_X = projectileX + viewSpace.x / 2 + projectileDistance * cos(projectileAngle);
	float projectile_Y = projectileY + viewSpace.y / 2 + projectileDistance * sin(projectileAngle);
	float pos_X = posEnemy1_aux_X + enemy_positionX;
	float pos_Y = posEnemy1_aux_Y + enemy_positionY;

	if (projectile_X + squareSide >= pos_X &&
		projectile_X <= pos_X + squareEnemy1 &&
		projectile_Y + squareSide >= pos_Y &&
		projectile_Y <= squareEnemy1 + pos_Y
		)
	{
		projectileHit = 1;
	}
}

void Tema1::BulletEnemy2Col(float projectileX, float projectileY, float projectileAngle, float projectileDistance)
{
	float projectile_X = projectileX + viewSpace.x / 2 + projectileDistance * cos(projectileAngle);
	float projectile_Y = projectileY + viewSpace.y / 2 + projectileDistance * sin(projectileAngle);
	float pos_X = posEnemy2_aux_X + enemy_position2X;
	float pos_Y = posEnemy2_aux_Y + enemy_position2Y;

	if (projectile_X + squareSide >= pos_X &&
		projectile_X <= pos_X + squareEnemy1 &&
		projectile_Y + squareSide >= pos_Y &&
		projectile_Y <= squareEnemy1 + pos_Y
		)
	{
		projectileHit2 = 1;
	}
}

void Tema1::BulletWallCol(float projectileX, float projectileY, float projectileAngle, float projectileDistance)
{
	float projectile_X = projectileX + viewSpace.x / 2 + projectileDistance * cos(projectileAngle);
	float projectile_Y = projectileY + viewSpace.y / 2 + projectileDistance * sin(projectileAngle);

	for (int i = 0; i < obstacles.size(); ++i)
	{
		if (projectile_X + squareSide >= obstacles[i].posX &&
			projectile_X <= obstacles[i].posX + obstacles[i].width &&
			projectile_Y <= obstacles[i].posY + obstacles[i].height &&
			projectile_Y + squareSide >= obstacles[i].posY)
		{
			wallHit = 1;
		}
	}
}

void Tema1::PlayerEnemy1Col(float playerPosX, float playerPosY, float enemyPosX, float enemyPosY)
{
	float pos_X = playerPosX;
	float pos_Y = playerPosY;
	float pos_en_X = enemyPosX;
	float pos_en_Y = enemyPosY;

	if (pos_X <= pos_en_X + squareEnemy1 &&
		pos_X + raza_1 >= pos_en_X &&
		pos_Y <= pos_en_Y + squareEnemy1 &&
		raza_1 + pos_Y >= pos_en_Y)
	{
		playerEnemy = 1;
	}
	else
		playerEnemy = 0;
}

void Tema1::PlayerEnemy2Col(float playerPosX, float playerPosY, float enemyPosX, float enemyPosY)
{
	float pos_X = playerPosX;
	float pos_Y = playerPosY;
	float pos_en_X = enemyPosX;
	float pos_en_Y = enemyPosY;

	if (pos_X <= pos_en_X + squareEnemy1 &&
		pos_X + raza_1 >= pos_en_X &&
		pos_Y <= pos_en_Y + squareEnemy1 &&
		raza_1 + pos_Y >= pos_en_Y)
	{
		playerEnemy2 = 1;
	}
	else
		playerEnemy2 = 0;
}

void Tema1::WallCol(float playerPosX, float playerPosY)
{
	moveW = playerPosY < (3.5 - raza_1) ? true : false;
	moveS = playerPosY > (0 + raza_1) ? true : false;
	moveA = playerPosX > (0 + raza_1) ? true : false;
	moveD = playerPosX < (3.5 - raza_1) ? true : false;
}

void Tema1::ObsCol(float playerPosX, float playerPosY, float deltaTimeSeconds)
{
	float actualPosX = (logicSpace.width / 2) + playerPosX;
	float actualPosY = (logicSpace.height / 2) + playerPosY;

	for (int i = 0; i < obstacles.size(); ++i)
	{
		if (actualPosX + raza_1 >= obstacles[i].posX &&
			actualPosX <= obstacles[i].posX + obstacles[i].width &&
			actualPosY <= obstacles[i].height + obstacles[i].posY&&
			actualPosY + raza_1 >= obstacles[i].posY
			)
		{
			moveD = false;
			logicSpace.x -= 1 * deltaTimeSeconds;
			translateX -= 1 * deltaTimeSeconds;
		}
		if (actualPosX - raza_1 <= obstacles[i].posX + obstacles[i].width &&
			actualPosX >= obstacles[i].posX &&
			actualPosY <= obstacles[i].posY + obstacles[i].height &&
			actualPosY + raza_1 >= obstacles[i].posY
			)
		{
			moveA = false;
			logicSpace.x += 1 * deltaTimeSeconds;
			translateX += 1 * deltaTimeSeconds;
		}
		if (actualPosX + raza_1 >= obstacles[i].posX &&
			actualPosX <= obstacles[i].posX + obstacles[i].width &&
			actualPosY <= obstacles[i].posY + obstacles[i].height &&
			actualPosY + raza_1 >= obstacles[i].posY
			)
		{
			moveW = false;
			logicSpace.y -= 1 * deltaTimeSeconds;
			translateY -= 1 * deltaTimeSeconds;
		}
		if (actualPosX + raza_1 >= obstacles[i].posX &&
			actualPosX <= obstacles[i].posX + obstacles[i].width &&
			actualPosY - raza_1 <= obstacles[i].posY + obstacles[i].height &&
			actualPosY >= obstacles[i].posY + obstacles[i].height
			)
		{
			moveS = false;
			logicSpace.y += 1 * deltaTimeSeconds;
			translateY += 1 * deltaTimeSeconds;
		}
	}
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W))
	{
			translateY += 1 * deltaTime;
			logicSpace.y += 1 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_S))
	{
			translateY -= 1 * deltaTime;
			logicSpace.y -= 1 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_A))
	{
			logicSpace.x -= 1 * deltaTime;
			translateX -= 1 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_D))
	{
			logicSpace.x += 1 * deltaTime;
			translateX += 1 * deltaTime;
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
	{
		if (Timer == 0 || Timer > projectile_Distance)
		{
			checkProjectile = 1;
			checkMousePointer = 0;
		}
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

