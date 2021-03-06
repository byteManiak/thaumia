#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>

// this file implements some shaders
// to do: separate shaders in their own .h/.glsl files in a "shaders" folder

const GLchar *defaultVertexSource[] =
{
	"#version 330 core\n"
	"layout (location = 0) in vec2 coord;\n"
	"layout (location = 1) in float texID;\n"
	"out float textureID;\n"
	"out vec2 uv;\n"
	"uniform float time;\n"
	"uniform ivec2 resolution;\n"
	"uniform vec2 offset;\n"
	 "void main() {"
	 "   const vec2 uv_verts[6] = vec2[6]( vec2(0, 1),"
	 "                                vec2(0, 0),"
	 "                                vec2(1, 0),"
	 "								  vec2(0, 1),"
	"								  vec2(1, 1),"
	"								  vec2(1, 0));"
	 "   gl_Position = vec4((vec2(coord.x, -coord.y) + vec2(offset.x, -offset.y))/ resolution * 2, 1, 1);"
	 "	 uv = uv_verts[gl_VertexID%6]; }"
};

const GLchar *defaultFragmentSource[] =
{
	"#version 330 core\n"
	"in float textureID;\n"
	"in vec2 uv;\n"
	"uniform sampler2D tex;\n"
	"uniform float time;\n"
	"void main() { gl_FragColor = texture(tex, uv); }\n"
};

GLuint getShader(const GLchar **vertex_source, const GLchar **fragment_source)
{
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader, 1, vertex_source, NULL);
	glShaderSource(fragment_shader, 1, fragment_source, NULL);

	GLint err;

	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &err);
	GLchar out_v[err];
	glGetShaderInfoLog(vertex_shader, err, NULL, out_v);
	if(err) fprintf(stderr, "[vertexShaderCompile] %s\n", out_v);

	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &err);
	GLchar out_f[err];
	glGetShaderInfoLog(fragment_shader, err, NULL, out_f);
	if(err) fprintf(stderr, "[fragmentShaderCompile] %s\n", out_f);

	GLuint shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);

	glLinkProgram(shader_program);

	return shader_program;
}

GLuint testShader;
GLuint defaultShader;
GLuint watermelonShader;
GLuint fontShader;

#endif // SHADER_H
