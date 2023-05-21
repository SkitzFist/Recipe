#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D screenTexture;
uniform float blurAmount;

void main() {
    vec2 tex_offset = 1.0 / textureSize(screenTexture, 0); // gets size of single texel
    vec4 result = vec4(0.0); // initialize to 0
    for(int j = -1; j <= 1; ++j) {
        for(int i = -1; i <= 1; ++i) {
            result += texture(screenTexture, TexCoord + vec2(tex_offset.x * i, tex_offset.y * j)) / 9.0;
        }
    }
    FragColor = mix(texture(screenTexture, TexCoord), result, blurAmount);
}