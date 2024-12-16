#version 330

in vec3 passTexCoord;

uniform sampler2DArray tex;

out vec4 fragColor;

void main() {
    fragColor = texture(tex, passTexCoord);
}
