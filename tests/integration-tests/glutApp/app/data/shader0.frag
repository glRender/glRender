#version 330 core 
out vec4 color;   
in vec3 keyring_position; 
in vec2 keyring_uv; 
uniform sampler2D texture0;
// uniform sampler2D texture1;

void main(void)
{
    // vec4 c = vec4(keyring_uv, 1.0, 1.0);
    vec4 t0 = 0.9 * texture(texture0, keyring_uv);
    // vec4 t1 = texture(texture1, keyring_uv);
    color = t0;
    // color = vec4(1.0, 0.0, 0.0, 1.0);

}