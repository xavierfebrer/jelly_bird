#version 300 es
precision lowp float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 mvp;
uniform vec2 offset;
uniform vec2 scale;
uniform bool flipX;
uniform bool flipY;

out vec2 TexCoords;

void main() {
        TexCoords = vec2(
       (((flipX ? 1.0f - aTexCoords.x : aTexCoords.x) * scale.x) + offset.x),
       (((flipY ? 1.0f - aTexCoords.y : aTexCoords.y) * scale.y) + offset.y));
        gl_Position = mvp * vec4(aPos, 1.0);
}