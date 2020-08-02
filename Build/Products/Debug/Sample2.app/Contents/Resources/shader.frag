#version 410 core
uniform sampler2D tex;
uniform vec4 color;
out vec4 fragColour;


void main()
{
    fragColour = color * texture(tex, gl_PointCoord);
}
