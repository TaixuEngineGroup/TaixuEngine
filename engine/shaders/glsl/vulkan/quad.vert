#version 450

layout(location = 0) out vec2 v2fTexcoord;

// index0
// *-*** index1
// | |*
// *-*
// *
// index2
// from: https://www.saschawillems.de/blog/2016/08/13/vulkan-tutorial-on-rendering-a-fullscreen-quad-without-buffers/
void main() {
    v2fTexcoord = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);
    gl_Position = vec4(v2fTexcoord * 2.0f - 1.0f, 0.0f, 1.0f);
}
