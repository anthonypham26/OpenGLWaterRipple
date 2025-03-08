#version 330 core

in vec3 fragColor;   // Received color from vertex shader
in vec2 TexCoord;    // Received texture coordinates from vertex shader

uniform sampler2D basicTexture; // Texture sampler
uniform float u_programTime;
uniform float u_timeOfClick;
uniform vec2 u_mousePos; 

out vec4 FinalColor; // Output final color

// Function to animate texture coordinates
vec2 animateTexCoords(vec2 coords) {
    // waveTime starts at 0 on click
    float waveTime = u_programTime - u_timeOfClick;
    // Start case
    if (u_timeOfClick == 0.0) {
        return coords;
    }

    // Euclidean distance between the current coordinate and the click position
    float dist = sqrt(pow(coords.x - u_mousePos.x, 2.0) + pow(coords.y - u_mousePos.y, 2.0));
    
    // Distortion along the x and y axes for a circular ripple
    float waveX = tan(sin(waveTime - dist * 30.0)) * 0.1;
    float waveY = tan(cos(waveTime - dist * 30.0)) * 0.1;
    
    // Exponential decay of the wave effect over time
    float waveStrength = exp(-waveTime * 0.5);
    
    // Apply the decay to the distortion effect
    vec2 offset = vec2(waveX, waveY) * waveStrength;
    
    return coords + offset;
}

void main() {
    // Animate texture coordinates with the ripple effect
    vec2 animatedCoords = animateTexCoords(TexCoord);

    vec4 texColor = texture(basicTexture, animatedCoords); // Sample the texture

    // Combine with the incoming vertex color (tint in main.cpp)
    FinalColor = vec4(fragColor, 1.0) * texColor;
}
