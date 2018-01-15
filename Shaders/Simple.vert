#version 120
attribute vec4 Position;
attribute vec4 SourceColor;
varying vec4 DestinationColor;
uniform mat4 Projection;
uniform mat4 Camera;
uniform mat4 Modelview;
uniform mat4 Device;

void main(void)
{
    DestinationColor = SourceColor;
    gl_Position = Projection * Device * Camera * Modelview  * Position;
}
