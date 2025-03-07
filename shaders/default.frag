#version 330 core

in vec3 fragColor;   // Received color from vertex shader
in vec2 TexCoord;    // Received texture coordinates from vertex shader

uniform sampler2D basicTexture; // Texture sampler
uniform float u_time; 
uniform vec2 u_mousePos; 

out vec4 FinalColor; // Output final color

// Function to animate texture coordinates
vec2 animateTexCoords(vec2 coords) {
    // Compute how far this fragment is from the mouse click position
    float dist = distance(coords, u_mousePos);

    // Parameters to tweak the ripple effect
    float freq      = 15.0;    // Higher => more ripples in the same space
    float speed     = 3.0;     // How quickly ripples move over time
    float amplitude = 0.02;    // How strong the distortion is

    // Wave function: The sine will oscillate based on distance & time
    float wave = sin(dist * freq - u_time * speed) * amplitude;

    // Direction from the click to the current coords
    vec2 dir = normalize(coords - u_mousePos);

    // Offset the coords outward or inward along dir
    coords += dir * wave;

    return coords;
}

void main() {
    // Distort the coordinates based on a ripple effect around u_mousePos
    vec2 animatedCoords = animateTexCoords(TexCoord);
    // Sample the texture using the shifted coordinates
    vec4 texColor = texture(basicTexture, animatedCoords);

    // Multiply by the color passed from the vertex shader (if you want vertex tint)
    FinalColor = vec4(fragColor, 1.0) * texColor;
}
