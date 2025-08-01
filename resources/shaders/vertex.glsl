#version 330 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normals;
layout(location = 2) in vec2 a_uv;

layout(std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;
out vec2 uv;

void main() {
    uv = a_uv;
    gl_Position = projection * view * model * vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
}
