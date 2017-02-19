#version 330 core 
out vec4 color;   
in vec3 keyring_vertex; 
in vec2 keyring_uv; 
uniform sampler2D texture0;

void main(void)
{
    color = texture(texture0, keyring_uv);
    // color = vec4(keyring_uv,1.0,0.0);
}
