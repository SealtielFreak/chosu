#include "demo_3d.h"


void draw_cube(const float *vertices, const float *transform) {
    const int index[] = {
            0, 1, 2, 3,
            3, 2, 6, 7,
            7, 6, 5, 4,
            4, 5, 1, 0,
            1, 5, 6, 2,
            4, 0, 3, 7
    };

    const GLfloat colors[] = {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 0.0,
            1.0, 0.0, 1.0,
            0.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            0.0, 0.0, 0.0
    };

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMultMatrixf(transform);

    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        glColor3fv(&colors[i * 3]);
        for (int j = 0; j < 4; j++) {
            glVertex3fv(&vertices[index[i * 4 + j] * 3]);
        }
    }

    glEnd();
}
