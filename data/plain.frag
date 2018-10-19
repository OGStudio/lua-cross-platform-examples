
// Define floating point precision for GLES.
#ifdef GL_ES
    precision highp float;
#endif

void main()
{
    // Paint everything with single color.
    gl_FragColor = vec4(1.0, 0.5, 0.5, 1.0);
}

