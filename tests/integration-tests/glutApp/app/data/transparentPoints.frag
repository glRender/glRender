#version 330 core 
out vec4 color;
in float keyring_index;
in float keyring_r;
in float keyring_g;
in float keyring_b;

void main(void)
{
    vec4 a;
    a.x = 1.0;
    a.y = 0.0;
    a.z = 0.0;
    
    vec4 b;
    b.x = 0.0;
    b.y = 0.0;
    b.z = 1.0;

    vec4 result;
    result.x = keyring_r;
    result.y = keyring_g;
    result.z = keyring_b;

    result = result * keyring_index + b * (1.0 - keyring_index);

    result.a = keyring_index;
    color = result;
}