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

VALUE rb_sfml_demo_3d(VALUE self) {
    sfVideoMode mode = {800, 600, 32};
    sfWindow *window = sfWindow_create(mode, "Demo 3D", sfResize | sfClose, NULL);

    sfWindow_setActive(window, sfTrue);
    glMatrixMode(GL_PROJECTION);

    // sfTransform projection = sfTransform_fromMatrix(-0.1f, 0.1f, -0.1f, 0.1f, 0.1f, 100.0f, 1, 1, 1);
    // glLoadMatrixf(projection.matrix);

    glEnable(GL_DEPTH_TEST);

    while (sfWindow_isOpen(window)) {
        sfEvent event;
        while (sfWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfWindow_close(window);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float transform[] = {
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, -5.0,
                0.0, 0.0, 0.0, 1.0
        };

        float vertices[] = {
                -1.0, -1.0, -1.0,
                -1.0, -1.0, 1.0,
                -1.0, 1.0, 1.0,
                -1.0, 1.0, -1.0,
                1.0, -1.0, -1.0,
                1.0, -1.0, 1.0,
                1.0, 1.0, 1.0,
                1.0, 1.0, -1.0
        };

        draw_cube(vertices, transform);

        sfWindow_display(window);
    }

    sfWindow_destroy(window);

    return 0;
}