#version 450

struct Particle {
    vec4 position;
    vec4 velocity;
};

layout(std430, binding = 0) buffer Particles {
    Particle particles[];
};

uniform mat4 transform;

void main() {
    gl_Position = transform * particles[gl_VertexID].position;
}