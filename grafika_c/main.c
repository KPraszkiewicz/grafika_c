#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<stdio.h>

#include"shader.h"
#include"funkcje.h"
#include"Macierz.h"

#define TN 100


static void error_callback(int error, const char* description)
{
    printf("Error: %s\n",description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
GLFWwindow* init_gl()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 0;
    GLFWwindow* window = glfwCreateWindow(800, 800, "My GLFW Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        return 0;

    glfwSetKeyCallback(window, key_callback);

    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* shading = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("%s\n%s\n%s\n%s\n", vendor, renderer, version, shading);
    return window;
}

int main(void)
{
    GLFWwindow* okno = init_gl();
    GLuint id_programu = LoadShadersf("vs.glsl","fs.glsl");
    GLuint poz_atryb = glGetAttribLocation(id_programu, "pozycja");
    GLint uni_mvp = glGetUniformLocation(id_programu, "MVP");
    /*
    GLfloat wierzcholki[] = { 0,0,0, 1,0,0, 0,1,0 };
    GLuint id_vbo;
    glGenBuffers(1, &id_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, id_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wierzcholki), wierzcholki, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint poz_atryb = glGetAttribLocation(id_programu, "pozycja");
    GLuint id_vao;
    glGenVertexArrays(1, &id_vao);
    glBindBuffer(GL_ARRAY_BUFFER, id_vbo);
    glVertexAttribPointer(poz_atryb, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(poz_atryb);
    glUseProgram(id_programu);

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDrawArrays(GL_QUADS, 0, 4);
    glfwSwapBuffers(okno);
    */
    /*
    GLfloat teren_wys[TN+1][TN+1] = { 0 };
    GLfloat teren_siatka[TN * TN * 12];
    for (int i = 0; i < TN; ++i)
    {
        for (int j = 0; j < TN; ++j)
        {
            teren_wys[i][j] = 0;
            int n = (i * TN + j) * 12;
            teren_siatka[n] = i;
            teren_siatka[n + 1] = teren_wys[i][j];
            teren_siatka[n + 2] = -j;

            teren_siatka[n + 3] = i;
            teren_siatka[n + 4] = teren_wys[i][j+1];
            teren_siatka[n + 5] = -(j  + 1);

            teren_siatka[n + 6] = i + 1;
            teren_siatka[n + 7] = teren_wys[i+1][j+1];
            teren_siatka[n + 8] = -(j + 1);

            teren_siatka[n + 9] = i + 1;
            teren_siatka[n + 10] = teren_wys[i+1][j];
            teren_siatka[n + 11] = -j;       
        }
    }
    

    GLuint id_vbo = init_vbo(teren_siatka, sizeof(teren_siatka));
    GLuint id_vao = init_vao();
    bind_vbo(id_vao, id_vbo, poz_atryb,4);
    
    */
    GLfloat test[] = {
        0.0, 0.0, 0.0,
        0.5, 0.0, 0.0,
        0.5, 0.5, 0.0,
        0.0, 0.5, 0.0,

        0.0, 0.5, 0.0,
        0.5, 0.5, 0.0,
        0.5, 1.0, 0.0,
        0.0, 1.0, 0.0,

        0.5, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.5, 0.0,
        0.5, 0.5, 0.0,

        0.5, 0.5, 0.0,
        1.0, 0.5, 0.0,
        1.0, 1.0, 0.0,
        0.5, 1.0, 0.0
        
    };
    GLuint id_vbo = init_vbo(test, sizeof(test));
    GLuint id_vao = init_vao();
    bind_vbo(id_vao, id_vbo, poz_atryb, 3);
    glUseProgram(id_programu);

    float* mvp;
    float* mT;
    float* mR = macierzObrotuY(radiany(45));
    float* mP = macierzProjekcji2(5, -5, 5, -5, 5, 160);
    float od = -5;
    while (!glfwWindowShouldClose(okno))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        od -= 0.01;
        mvp = macierzJednostkowa();
        mT = macierzTranslacji(-0.5, -0.5, od);
        mvp = mnozenie(mvp, mP);
        mvp = mnozenie(mvp, mT);
        glUniformMatrix4fv(uni_mvp, 1, GL_TRUE, mvp);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        glDrawArrays(GL_LINE_LOOP, 4, 4);
        glDrawArrays(GL_LINE_LOOP, 8, 4);
        glDrawArrays(GL_LINE_LOOP, 12, 4);
        glfwSwapBuffers(okno);
        glfwPollEvents();
    }
    glfwDestroyWindow(okno);
    glfwTerminate();
    return 0;
}