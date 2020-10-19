#version 300 es
precision lowp float;

in vec2 TexCoords;

uniform sampler2D texture_diffuse;
uniform vec4 tint;

out vec4 FragColor;

void main() {
    FragColor = texture(texture_diffuse, TexCoords) * tint;
}
