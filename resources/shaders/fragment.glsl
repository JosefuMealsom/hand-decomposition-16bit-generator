#version 330 core
precision highp float;

in vec2 uv;

out vec4 FragColor;

uniform sampler2D texture1;
uniform vec3 color;

void main()
{
    FragColor = vec4(color, 1.);
}
