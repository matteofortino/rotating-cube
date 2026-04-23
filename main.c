#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
// --- CONFIGURAZIONE FACILE ---
// Modifica questi valori per cambiare il comportamento
#define ROTATION_SPEED 1.5f // Moltiplicatore velocità
#define ROTATE_X true       // Attiva/Disattiva rotazione su X
#define ROTATE_Y true       // Attiva/Disattiva rotazione su Y
#define ROTATE_Z false      // Attiva/Disattiva rotazione su Z

int main(void) {
    // Inizializzazione
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Raylib - Cubo con Matrici di Rotazione");

    // Definiamo la telecamera
    Camera3D camera = {0};
    camera.position = (Vector3){4.0f, 4.0f, 4.0f}; // Posizione della camera
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};   // Punto che la camera guarda
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};       // Direzione "alto"
    camera.fovy = 45.0f;                           // Campo visivo
    camera.projection = CAMERA_PERSPECTIVE;

    float angle = 0.0f;
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // 1. Aggiornamento logica
        angle += ROTATION_SPEED * GetFrameTime();

        // Creazione della matrice di rotazione combinata
        // Partiamo da una matrice identità (nessuna rotazione)
        Matrix rotationMat = MatrixIdentity();

        if (ROTATE_X)
            rotationMat = MatrixMultiply(rotationMat, MatrixRotateX(angle));
        if (ROTATE_Y)
            rotationMat = MatrixMultiply(rotationMat, MatrixRotateY(angle));
        if (ROTATE_Z)
            rotationMat = MatrixMultiply(rotationMat, MatrixRotateZ(angle));

        // 2. Disegno
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Applichiamo la matrice di rotazione direttamente nel disegno
        // rlPushMatrix/rlPopMatrix isolano la trasformazione solo a questo cubo
        rlPushMatrix();
        rlMultMatrixf(MatrixToFloat(rotationMat));

        DrawCube(Vector3Zero(), 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(Vector3Zero(), 2.0f, 2.0f, 2.0f, MAROON);
        rlPopMatrix();

        DrawGrid(10, 1.0f);
        EndMode3D();

        DrawText("Modifica le macro nel codice per cambiare assi e velocità", 10, 10, 20, DARKGRAY);
        DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
