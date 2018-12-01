#version 330 core

in vec3 vertex;
in vec3 color;
out vec4 vecColor;

void main()  {
    gl_Position = vec4 (0.5 * vertex, 1.0);
    vecColor = vec4(color, 1);
}
