#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Variables para la posición de nuestro "Mario Chueco"
float player_x = 0.0f;
float player_y = 0.0f;
float player_z = -5.0f;
float rotation_angle = 0.0f;

void init_graphics3d(void) {
    // Inicializa la pantalla en 3D
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    gl_init();
    
    // Configuración de la cámara y perspectiva 3D estilo Mario 64
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 320.0f / 240.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void draw_chueco_player(void) {
    glPushMatrix();
    // Movemos al personaje según los controles
    glTranslatef(player_x, player_y, player_z);
    glRotatef(rotation_angle, 0.0f, 1.0f, 0.0f); // Rotación constante chueca

    // Dibujamos un cubo texturizable "chueco" (asiento del personaje/meme)
    glBegin(GL_QUADS);
        // Cara frontal (Aquí irá el meme del internet)
        glColor3f(1.0f, 0.0f, 0.0f); // Rojo Mario
        glVertex3f(-1.0f, -1.2f,  1.0f); // Modificado para que se vea deformado/chueco
        glVertex3f( 1.1f, -1.0f,  1.0f);
        glVertex3f( 1.0f,  1.5f,  1.0f);
        glVertex3f(-0.9f,  1.0f,  1.0f);
    glEnd();
    glPopMatrix();
}

int main(void) {
    init_graphics3d();
    controller_init();

    while(1) {
        // Capturar controles del control de N64 (o teclado en OpenEmu)
        controller_scan();
        struct controller_data keys = get_keys_pressed();

        // Mover personaje con el Stick analógico o D-Pad
        if (keys.c.pad & BUTTON_C_RIGHT) player_x += 0.1f;
        if (keys.c.pad & BUTTON_C_LEFT)  player_x -= 0.1f;
        if (keys.c.pad & BUTTON_C_UP)    player_z += 0.1f;
        if (keys.c.pad & BUTTON_C_DOWN)  player_z -= 0.1f;

        // Hacer que rote de forma "chueca" para molestar visualmente
        rotation_angle += 2.0f;

        // Renderizar la escena
        surface_t *disp = display_lock();
        if (disp) {
            gl_context_begin(disp);
            glClearColor(0.1f, 0.5f, 0.8f, 1.0f); // Fondo azul cielo de internet antiguo
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glLoadIdentity();
            
            // Dibujar los niveles e historia del internet aquí
            draw_chueco_player();

            gl_context_end();
            display_show(disp);
        }
    }
}
