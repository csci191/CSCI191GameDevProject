uniform float scale;
void main()
{
    vec4 a = GL_VERTEX; // "a" will get the verticies values from cpu
    a.x = a.x * scale;
    a.y = a.y * scale;

    GL_POSITION = gl_ModelViewProjectionMatrix * a;
}
