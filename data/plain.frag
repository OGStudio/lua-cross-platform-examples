
// Define floating point precision for GLES.
#ifdef GL_ES
    precision highp float;
#endif

uniform vec3 color;

void main()
{
    // Paint everything with single color.
    gl_FragColor = vec4(color, 1.0);
}

