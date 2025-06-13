#version 450

struct Particle {
    vec4 position;
    vec4 velocity;
};

layout(local_size_x = 256) in;  // jeden work group = 256 w¹tków

layout(std430, binding = 0) buffer Particles {
    Particle particles[];
};

uniform float dt;

void main() {
    uint id = gl_GlobalInvocationID.x;
    //particles[id].velocity += vec4(0.0, 0.0, 0.0, 0.0) * dt;

    //gravity
    float r = length(particles[id].position.xyz);
    vec3 gravity = normalize(particles[id].position.xyz) / (r * r * r) * 1;

    //antigravity
    vec3 antigravity = -normalize(particles[id].position.xyz) / (r * r) * 1;

    //particles[id].velocity -= 1 * particles[id].position * dt;
    //particles[id].velocity.w = 0;

    particles[id].velocity += vec4(gravity + antigravity, 0.0) * dt;
    particles[id].position += particles[id].velocity * dt;
}