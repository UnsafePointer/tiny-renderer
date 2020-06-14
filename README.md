# tiny-renderer

A (tiny) LCD "framebuffer" OpenGL renderer.

```C++
std::vector<Vertex> pixels = {
    Vertex(0, 0,  255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f),
    Vertex(0, 1,  170.0f / 255.0f, 170.0f / 255.0f, 170.0f / 255.0f),
    Vertex(1, 0,  85.0f / 255.0f, 85.0f / 255.0f, 85.0f / 255.0f),
    Vertex(1, 1,  0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f),
};
uint32_t width = 2;
uint32_t height = 2;
uint32_t scale = 300;
Renderer renderer = Renderer(width, height, scale);
```

![tiny-renderer.png](/images/tiny-renderer.png)
