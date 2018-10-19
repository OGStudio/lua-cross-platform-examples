
void main()
{
    // Pass vertex.
    // Convert from Model/Object space to Screen one.
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

