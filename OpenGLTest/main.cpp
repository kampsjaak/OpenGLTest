#include <GLFW/glfw3.h>
#include "linmath.h"

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;

void render_loop()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(10);
    glLineWidth(3);
    
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 1, 0);
    glEnd();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // set up view
    glViewport(0, 0, 400, 400);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
    //glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0); // this creates a canvas you can do 2D drawing on

    vec3 camera = { 0.0f, 0.0f, -1.0f };
    mat4x4 m;
    mat4x4 v;
    mat4x4 p;
    mat4x4 mvp;

    //The model matrix controls where the object is positioned. The
    //identity matrix means no transformations.
    mat4x4_identity(m);
    mat4x4_identity(v);
    mat4x4_identity(p);
    //Apply model transformations here.

    //The view matrix controls camera position and angle.
    vec3 eye = { camera[0],camera[1],camera[2] - 3};
    vec3 center = { camera[0],camera[1],camera[2] };
    vec3 up = { 0,1,0 };
    mat4x4_look_at(v, eye, center, up);

    //The projection matrix flattens the world to 2d to be rendered on a
    //screen.
    mat4x4_perspective(p, 1.57, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1, 10); //FOV of 90°
    //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);

    //Apply the transformations. mvp=p*v*m.
    mat4x4_mul(mvp, p, v);
    mat4x4_mul(mvp, mvp, m);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Draw gears
        render_loop();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        ///* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);

        ///* Swap front and back buffers */
        //glfwSwapBuffers(window);

        ///* Poll for and process events */
        //glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}