#version 330 core 
out vec4 color;   
in vec3 keyring_position; 
in vec2 keyring_uv; 
in float keyring_r; 
in float keyring_g; 
in float keyring_b; 

void main(void)
{
    color = vec4(keyring_r, keyring_g, keyring_b, 1.0);
}