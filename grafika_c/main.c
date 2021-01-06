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
    GLFWwindow* window = glfwCreateWindow(800, 600, "My GLFW Window", NULL, NULL);
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
    /**/
    GLfloat teren_wys[TN+1][TN+1] = { -1 };
    for (int i = 0; i < (TN + 1) * (TN + 1); ++i)
    {
        *(teren_wys[0] + i) = 0;
    }
    GLfloat teren_siatka[TN * TN * 12];
    for (int i = 0; i < TN; ++i)
    {
        for (int j = 0; j < TN; ++j)
        {
            //teren_wys[i][j] = -1;
            int n = (i * TN + j) * 12;
            teren_siatka[n + 0] = i;
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
    bind_vbo(id_vao, id_vbo, poz_atryb,3);

    /**
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
    /**
    GLfloat test2[] = {
        0, -1.0, 0,
        1, -1.0, 0,
        1, -1.0, -1,
        0, -1.0, -1,

        0, -1.0, -1,
        1, -1.0, -1,
        1, -1.0, -2,
        0, -1.0, -2,

        1, -1.0, 0,
        2, -1.0, 0,
        2, -1.0, -1,
        1, -1.0, -1,

        1, -1.0, -1,
        2, -1.0, -1,
        2, -1.0, -2,
        1, -1.0, -2

    };
    GLuint id_vbo = init_vbo(test2, sizeof(test2));
    GLuint id_vao = init_vao();
    bind_vbo(id_vao, id_vbo, poz_atryb, 3);
    /**/
    glUseProgram(id_programu);

    float mvp[16];
    float mT[16]; //= macierzTranslacji(-50,-2,50);
    float mR[16]; 
    float mS[16]; 
    float mP[16]; //= macierzProjekcji(radiany(90), 1, .1, 100);
    //float* mP = macierzProjekcji2(-5, 5, -5, 5, 5, 160);
    
    macierzJednostkowa(mvp);
    macierzProjekcji(mP, radiany(90), 4/3, .1, 100);
    
    float ruch = 50.f;


    while (!glfwWindowShouldClose(okno))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        ruch += 0.01f;
        macierzJednostkowa(mvp);
        macierzTranslacji(mT, -50, -2, ruch);
        mnozenie(mvp, mP, mT);

        glUniformMatrix4fv(uni_mvp, 1, GL_TRUE, mvp);
        for(int i = 0; i < TN*TN; ++i)
            glDrawArrays(GL_LINE_LOOP, i*4, 4);
        glfwSwapBuffers(okno);
        glfwPollEvents();
    }
    glfwDestroyWindow(okno);
    glfwTerminate();
    return 0;
}