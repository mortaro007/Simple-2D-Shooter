#pragma once

#include "components/simple_scene.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);
        void BulletEnemy1Col(float projectileX, float projectileY, float projectileAngle, float projectileDistance);
        void BulletEnemy2Col(float projectileX, float projectileY, float projectileAngle, float projectileDistance);
        void BulletWallCol(float projectileX, float projectileY, float projectileAngle, float projectileDistance);
        void PlayerEnemy1Col(float playerPosX, float playerPosY, float enemyPosX, float enemyPosY);
        void PlayerEnemy2Col(float playerPosX, float playerPosY, float enemyPosX, float enemyPosY);
        void WallCol(float playerPosX, float playerPosY);
        void ObsCol(float playerPosX, float playerPosY, float deltaTimeSeconds);
        void EnemyWallCol(float enemyX, float enemyY);

    protected:
        glm::mat3 modelMatrix, visMatrix;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        time_t current_time;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        int check, checkScale;
        float raza_1, raza_2, raza_3, raza_4;
        float mouse_X, mouse_Y, mouse_Angle;
        float PI;
        float squareSide, squareEnemy1;
        int checkProjectile;
        float Projectile_Movement_X, Projectile_Movement_Y;
        float checkMousePointer, checkMouseAngle;
        float checkPosition;
        int check_Fire, check_FireRate, check_Trigger, check_FireTime;
        float check_mouseX, check_mouseY;
        float cpx, cpy;
        float Timer;
        float projectile_Distance;
        float w, h, w_enemy, h_enemy;
        float cx, cy;
        float posX, posY;
        float mapSide;
        float checkY, checkX;
        float newPosX, newPosY;
        float posEnemy1_X, posEnemy1_Y, posEnemy2_X, posEnemy2_Y;
        double seconds_since_start;
        int checkEnemies, checkEnemies2;
        float enemy_Angle;
        float enemy_positionX, enemy_positionY;
        float posEnemy1_aux_X, posEnemy1_aux_Y;
        float posEnemy2_aux_X, posEnemy2_aux_Y;
        int projectileHit, projectileHit2;
        float projectile_max;
        int wallHit;
        float pozObsX, pozObsY;
        float healthWidth, healthHeight;
        int health1, health2, health3;
        int playerWall;
        float pozObs1, pozObs2;
        int playerEnemy;
        float enemy_position2X, enemy_position2Y;
        int playerEnemy2;
        int healthCheck; int healthCheck2;
        bool gameOver;
        bool moveW, moveS, moveA, moveD;
        float pozObs3, pozObs4;
        float upX, upY;
        float downX, downY;
        float leftX, leftY;
        float rightX, rightY;
        float copyX, copyY;
        int scor;
        float w1, h1;
        float pozObs5, pozObs6, pozObs7, pozObs8;
        float posObsS, posObsSS;
        float pozObs9, pozObs10, pozObs11, pozObs12;
        float pozObs13, pozObs14;
        float pozObs15, pozObs16, pozObs17, pozObs18;

        struct Obs
        {
            float posX;
            float posY;
            float width;
            float height;
        };

        std::vector<Obs> obstacles;
    };
}