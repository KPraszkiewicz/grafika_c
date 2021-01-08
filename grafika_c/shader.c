#include "shader.h"

GLuint wczytaj_shader(GLuint program)
{
	// vertex shader
	static const char kod_shadera[] = "#version 430 "
		"in vec3 pozycja;void main(){gl_Position = vec4(pozycja, 1);}";
	GLuint id_shadera = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(id_shadera, 1, &kod_shadera, 0);
	glCompileShader(id_shadera);
	GLint kompil_ok;
	glGetShaderiv(id_shadera, GL_COMPILE_STATUS, &kompil_ok);

	if (!kompil_ok)
	{
		printf("Nie wczytano shadera!\n");
		return 0;
	}
	// fragment shader
	static const char kod_shadera2[] = "#version 430 "
		"void main(){gl_FragColor = vec4(1, 1, 1, 1);}";
	GLuint id_shadera2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(id_shadera2, 1, &kod_shadera2, 0);
	glCompileShader(id_shadera2);
	glGetShaderiv(id_shadera2, GL_COMPILE_STATUS, &kompil_ok);

	if (!kompil_ok)
	{
		printf("Nie wczytano shadera!\n");
		return 0;
	}

	glAttachShader(program, id_shadera);
	glAttachShader(program, id_shadera2);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status)
	{
		printf("Nie wczytano shaderow!\n");
		return 0;
	}
	return program;
}

GLuint LoadShadersf(const char* vertex_file_path, const char* fragment_file_path) 
{
	long size1,size2,i;
	char znak;
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	char* VertexShaderCode;
	FILE* plikvs;
	fopen_s(&plikvs, vertex_file_path, "r");
	if (plikvs)
	{
		fseek(plikvs, 0, SEEK_END); // seek to end of file
		size1 = (ftell(plikvs)) * sizeof(char); // get current file pointer
		fseek(plikvs, 0, SEEK_SET); // seek back to beginning of file
		rewind(plikvs);
		VertexShaderCode = (char*)malloc(size1+1);
		i = 0;
		while (!feof(plikvs))
		{
			VertexShaderCode[i] = getc(plikvs);
			if (VertexShaderCode[i] == '}')
			{
				VertexShaderCode[i + 1] = '\0';
				break;
			}
			++i;
		}
		//VertexShaderCode[size1] = '\0';
		//fread(VertexShaderCode, sizeof(char), size1, plikvs);
		//printf("kod: %s\n", VertexShaderCode);
		fclose(plikvs);
		//-----------
		//printf("\nkod: %s\n", VertexShaderCode);
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		return 0;
	}
	
	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	glShaderSource(VertexShaderID, 1, &VertexShaderCode, NULL);
	glCompileShader(VertexShaderID);
	free(VertexShaderCode);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		char* VertexShaderErrorMessage = malloc(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage);
		printf("%s\n", VertexShaderErrorMessage);
		free(VertexShaderErrorMessage);
	}

	// Read the Fragment Shader code from the file
	char* FragmentShaderCode;
	FILE* plikfs;
	fopen_s(&plikfs, fragment_file_path, "r");
	if (plikfs)
	{
		fseek(plikfs, 0, SEEK_END); // seek to end of file
		size2 = (ftell(plikfs)) * sizeof(char); // get current file pointer
		fseek(plikfs, 0, SEEK_SET); // seek back to beginning of file
		rewind(plikfs);
		FragmentShaderCode = (char*)malloc(size2+1);
		i = 0;
		while (!feof(plikfs))
		{
			
			FragmentShaderCode[i] = getc(plikfs);
			if (FragmentShaderCode[i] == '}')
			{
				FragmentShaderCode[i + 1] = '\0';
				break;
			}
			++i;
			//putchar(VertexShaderCode[i - 1]);
		}
		//fread(FragmentShaderCode, sizeof(char), size2, plikfs);
		//FragmentShaderCode[size2] = '\0';
		//printf("\nkod: %s\n", FragmentShaderCode);
		fclose(plikfs);
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", fragment_file_path);
		return 0;
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	glShaderSource(FragmentShaderID, 1, &FragmentShaderCode, NULL);
	glCompileShader(FragmentShaderID);
	//free(FragmentShaderCode);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		char* VertexShaderErrorMessage = malloc(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, VertexShaderErrorMessage);
		printf("%s\n", VertexShaderErrorMessage);
		free(VertexShaderErrorMessage);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		char* ProgramErrorMessage = malloc(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage);
		printf("%s\n", ProgramErrorMessage);
		free(ProgramErrorMessage);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}