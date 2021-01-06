#pragma once

#include<GL/glew.h>

#include<stdio.h>
#include<malloc.h>
GLuint wczytaj_shader(GLuint program);

GLuint LoadShadersf(const char* vertex_file_path, const char* fragment_file_path);
