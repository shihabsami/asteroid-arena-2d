#include "game_init.h"
#include "../utilities/game_manager.h"

double l_time;
game_manager* manager;

void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // for smooth points/edges/polygons
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glClearColor
        (
            static_cast<GLclampf>(c::arena_fill.r),
            static_cast<GLclampf>(c::arena_fill.g),
            static_cast<GLclampf>(c::arena_fill.b), 1.0
        );
    manager->display();

    glutSwapBuffers();
    error_check("game_init::on_display");
}

void on_reshape(int width, int height) {
    glViewport(ORIGIN_X, ORIGIN_Y, width, height);
    g::width = static_cast<double>(width);
    g::height = static_cast<double>(height);

    double aspect_ratio = g::width / g::height;
    if (aspect_ratio > 1.0) {
        g::x_units = TOTAL_UNITS * aspect_ratio;
        g::y_units = TOTAL_UNITS;
    } else if (aspect_ratio < 1.0) {
        g::x_units = TOTAL_UNITS;
        g::y_units = TOTAL_UNITS / aspect_ratio;
    } else {
        g::x_units = TOTAL_UNITS;
        g::y_units = TOTAL_UNITS;
    }

    /*
     * resize orthographic projection in order to
     * maintain the same aspect ratio as the viewport
     */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        -g::x_units / 2, g::x_units / 2,
        -g::y_units / 2, g::y_units / 2,
        ORTHO_Z_NEAR, ORTHO_Z_FAR);

    manager->registry->ui->update();
    error_check("game_init::on_reshape");
}

void on_idle() {
    /*
     * update current and delta time
     * delta time is converted to seconds
     */
    g::c_time = static_cast<double>(glutGet(GLUT_ELAPSED_TIME));
    g::d_time = (g::c_time - l_time) / 1000;
    l_time = g::c_time;
    glutPostRedisplay();
    error_check("game_init::on_idle");
}

// input functions delegate calls to handler class
void on_mouseclick(int button, int state, int x, int y) {
    manager->i_handler->on_mouseclick(button, state, x, y);
    error_check("game_init::on_mouseclick");
}

void on_keydown(unsigned char key, int x, int y) {
    manager->i_handler->on_keydown(key, x, y);
    error_check("game_init::on_keydown");
}

void on_keyup(unsigned char key, int x, int y) {
    manager->i_handler->on_keyup(key, x, y);
    error_check("game_init::on_keyup");
}

void init_game(int* argcp, char** argv, game_window* window) {
    glutInit(argcp, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(window->position_x, window->position_y);
    glutInitWindowSize(window->width, window->height);

    g::width = static_cast<double>(window->width);
    g::height = static_cast<double>(window->height);
    manager = new game_manager();

    glutCreateWindow(GAME_TITLE);
    if (window->is_fullscreen) glutFullScreen();

    // register callback methods
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutIdleFunc(on_idle);

    glutMouseFunc(on_mouseclick);
    glutIgnoreKeyRepeat(false);
    glutKeyboardFunc(on_keydown);
    glutKeyboardUpFunc(on_keyup);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        -g::width / 2, g::width / 2,
        -g::height / 2, g::height / 2,
        ORTHO_Z_NEAR, ORTHO_Z_FAR);
    glutMainLoop();
}
