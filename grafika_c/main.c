#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include<time.h>

#include"shader.h"
#include"funkcje.h"
#include"Macierz.h"




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

GLfloat teren_wys[TN1][TN1];
GLfloat teren_siatka[TN * TN * 3*6];

GLfloat siatka_uv[TN * TN * 2*6];

Obiekt obiekty[30];

int main(void)
{
    srand(time(0));
    GLFWwindow* okno = init_gl();
    GLuint id_programu = LoadShadersf("teren_vs.glsl", "teren_fs.glsl");
    GLuint prog_ob = LoadShadersf("obiekt_vs.glsl", "obiekt_fs.glsl");

    GLint uni_mvp = glGetUniformLocation(id_programu, "MVP");
    GLint uni_ob_mvp = glGetUniformLocation(prog_ob, "MVP");
    GLint uni_tex = glGetUniformLocation(id_programu, "basic_texture");
    
    for (int i = 0; i < TN1; ++i)
    {
        for (int j = 0; j < TN1; ++j)
            teren_wys[i][j] = 0;
    }
    
    inicjuj_plansze(teren_wys, TN1, TN1, 100, 30, 40);
    gora(teren_wys, TN1, TN1, 20, 20, 10, 0, 9);

    for (int i = 0; i < TN; ++i)
    {
        for (int j = 0; j < TN; ++j)
        {
            //teren_wys[i][j] = -1;
            int n = (i * TN + j) * 18;
            int k = (i * TN + j) * 12;
            teren_siatka[n + 0] = i;
            teren_siatka[n + 1] = teren_wys[i][j];
            teren_siatka[n + 2] = j;
            siatka_uv[k + 0] = 0;
            siatka_uv[k + 1] = 0;

            teren_siatka[n + 3] = i + 1;
            teren_siatka[n + 4] = teren_wys[i + 1][j];
            teren_siatka[n + 5] = (j);
            siatka_uv[k + 2] = 1;
            siatka_uv[k + 3] = 0;

            teren_siatka[n + 6] = i + 1;
            teren_siatka[n + 7] = teren_wys[i+1][j+1];
            teren_siatka[n + 8] = (j + 1);
            siatka_uv[k + 4] = 1;
            siatka_uv[k + 5] = 1;

            teren_siatka[n + 9] = i + 1;
            teren_siatka[n + 10] = teren_wys[i + 1][j + 1];
            teren_siatka[n + 11] = (j + 1);
            siatka_uv[k + 6] = 1;
            siatka_uv[k + 7] = 1;

            teren_siatka[n + 12] = i;
            teren_siatka[n + 13] = teren_wys[i][j + 1];
            teren_siatka[n + 14] = (j + 1);
            siatka_uv[k + 8] = 0;
            siatka_uv[k + 9] = 1;

            teren_siatka[n + 15] = i;
            teren_siatka[n + 16] = teren_wys[i][j];
            teren_siatka[n + 17] = (j );
            siatka_uv[k + 10] = 0;
            siatka_uv[k + 11] = 0;
        }
    }
    
    GLuint id_vbo = init_vbo(teren_siatka, sizeof(teren_siatka));
    GLuint uv_vbo = init_vbo(siatka_uv, sizeof(siatka_uv));
    GLuint id_vao = init_vao();
    bind_vbo(id_vao, id_vbo, 0, 3);
    bind_vbo(id_vao, uv_vbo, 1, 2);

    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    

    
    glUniform1i(uni_tex, 0);
    glActiveTexture(GL_TEXTURE0);
    
    auto texxx = inicjuj_teksture("tex.bmp");
    
    
    float mvp[16]; // mvp = P * kR * kT * oT * oS * oR * v4
    float mT[16]; 
    float mR[16]; 
    float mS[16]; 
    float mP[16]; 
    float mkt[16];
    float mkr[16];
    //float* mP = macierzProjekcji2(-5, 5, -5, 5, 5, 160);
    
    macierzJednostkowa(mvp);
    macierzTranslacji(mkt, -20, 0, -20);
    macierzObrotuY(mkr, 0);
    macierzProjekcji(mP, radiany(90), 4/3, .1, 100);
    macierzTranslacji(mT, -0, -0, 0);
    
    float kat = 0;
    int pozX; // -
    int pozZ; // +
    
    inicjuj_obiekty(obiekty, 50);
    for (int i = 0; i < 50; ++i)
    {
        Obiekt* o = obiekty + i;
        o->mT[7] += teren_wys[(int)o->mT[3] % TN][(int)o->mT[11] % TN];
    }


    while (!glfwWindowShouldClose(okno))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (glfwGetKey(okno, GLFW_KEY_W) == GLFW_PRESS)
        {
            mkt[11] += 0.03f * cos(kat);
            mkt[3] -= 0.03f * sin(kat);
        }
        if (glfwGetKey(okno, GLFW_KEY_S) == GLFW_PRESS)
        {
            mkt[11] -= 0.03f * cos(kat);
            mkt[3] += 0.03f * sin(kat);
        }
        if (glfwGetKey(okno, GLFW_KEY_A) == GLFW_PRESS)
        {
            mkt[11] += 0.03f * cos(kat - radiany(90));
            mkt[3] -= 0.03f * sin(kat - radiany(90));
        }
        if (glfwGetKey(okno, GLFW_KEY_D) == GLFW_PRESS)
        {
            mkt[11] += 0.03f * cos(kat + radiany(90));
            mkt[3] -= 0.03f * sin(kat + radiany(90));
        }
        if (glfwGetKey(okno, GLFW_KEY_Q) == GLFW_PRESS)
        {
            kat -= 0.008f;
        }
        if (glfwGetKey(okno, GLFW_KEY_E) == GLFW_PRESS)
        {
            kat += 0.008f;
        }
        if (glfwGetKey(okno, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            mkt[7] -= 0.06f;
        }
        if (glfwGetKey(okno, GLFW_KEY_C) == GLFW_PRESS)
        {
            mkt[7] += 0.06f;
        }
        // zmiana wysokoœci
        pozX = (-((int)floor(mkt[3]) + 1))%TN;
        pozZ = (-((int)floor(mkt[11]) + 1)) % TN;
        //printf("%d %d\n", pozX, pozZ);
        mkt[7] = -MAX(MAX(teren_wys[pozX][pozZ], teren_wys[pozX][pozZ + 1]), MAX(teren_wys[pozX + 1][pozZ + 1], teren_wys[pozX+1][pozZ])) - 1;
        //=========
        // teren
        glUseProgram(id_programu);
        glBindVertexArray(id_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        macierzObrotuY(mkr, kat);
        //macierzJednostkowa(mvp);
        
        mnozenie(mvp, mP, mkr);
        mnozenie(mvp, mvp, mkt);
        mnozenie(mvp, mvp, mT);
        
        glUniformMatrix4fv(uni_mvp, 1, GL_TRUE, mvp);
        glDrawArrays(GL_TRIANGLES, 0, TN*TN*6);
        //=========================
        // ----- obiekty ----------

        glUseProgram(prog_ob);
        mnozenie(mvp, mP, mkr);
        mnozenie(mvp, mvp, mkt);

        for (int i = 0; i < 50; ++i)
        {
            Obiekt* o = obiekty + i;
            glBindVertexArray(o->vao);
            //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o->ebo);
            

           
            mnozenie(o->mvp, mvp, o->mT);
            mnozenie(o->mvp, o->mvp, o->mS);

            glUniformMatrix4fv(uni_ob_mvp, 1, GL_TRUE, o->mvp);
            int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
            glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
        }
        
        // ==========================
        glfwSwapBuffers(okno);
        glfwPollEvents();
    }
    glfwDestroyWindow(okno);
    glfwTerminate();
    return 0;
}