#version 330 core
precision highp float;

in vec2 uv;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    FragColor = vec4(uv.x, uv.y, 0., 1.);

    // FragColor = vec4(1., 1., 1., 1.);
}
