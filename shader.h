#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>

const GLchar *defaultVertexSource[] =
{
	"#version 330 core\n"
	"layout (location = 0) in vec2 coord;\n"
	 "out vec2 uv;\n"
	"uniform float time;\n"
	"uniform ivec2 resolution;\n"
	 "void main() {"
	 "   const vec2 uv_verts[4] = vec2[4]( vec2(0, 1),"
	 "                                vec2(1, 1),"
	 "                                vec2(1, 0),"
	 "                                vec2(0, 0));"
	 "   gl_Position = vec4(vec2(coord.x, -coord.y) / resolution * 2, 1, 1);"
	 "	 uv = uv_verts[gl_VertexID]; }"
};

const GLchar *watermelonVertexSource[] =
{
	"#version 330 core\n"
	"layout (location = 0) in vec2 coord;\n"
	 "out vec2 uv;\n"
	"uniform float time;\n"
	"uniform ivec2 resolution;\n"
	 "void main() {"
	 "   const vec2 uv_verts[4] = vec2[4]( vec2(0, 1),"
	 "                                vec2(1, 1),"
	 "                                vec2(1, 0),"
	 "                                vec2(0, 0));"
	 "   gl_Position = vec4(vec2(coord.x, -coord.y) / resolution * 2 + vec2(0, sin(time)/6), 1, 1);"
	 "	 uv = uv_verts[gl_VertexID]; }"
};

const GLchar *defaultFragmentSource[] =
{
	"#version 330 core\n"
	"in vec2 uv;\n"
	"uniform sampler2D tex;\n"
	"uniform float time;\n"
	"void main() { gl_FragColor = vec4(1, 1, 1, texture(tex, uv).r); }\n"
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

GLuint defaultShader;
GLuint watermelonShader;

#endif // SHADER_H
