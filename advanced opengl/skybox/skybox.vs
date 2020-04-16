#version 330 core
layout (location = 0) in vec3 aPos;


out vec3 TexCoords;


uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * view  * vec4(aPos, 1.0);
    gl_Position = pos.xyww; //如果没有这句 天空盒的深度测试无法通过，片段被丢弃，就无法渲染
}  