#version 330

layout (location = 0) in vec3 modelPos;
layout (location = 1) in vec2 modelTexCoord;
layout (location = 2) in uint instData;

uniform mat4 proj, view;

out vec3 passTexCoord;

void main() {
    float x = modelPos.x + float(instData & 0xffu);
    float y = modelPos.y + float((instData >> 8u) & 0xffu);
    float z = modelPos.z + float((instData >> 16u) & 0xffu);
    float texLayer = float((instData >> 24u) & 0xffu);

    gl_Position = proj * view * vec4(x, y, z, 1.0);

    passTexCoord = vec3(modelTexCoord, texLayer);
}
