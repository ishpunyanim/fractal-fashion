# fractal-fashion

Perfect — here’s a **concise, honest, and technically clear** `README.md` draft for your **Fractal Fashion (Julia Set Renderer)** project. It’s written in a professional but minimal tone — something that looks genuine on GitHub or a portfolio link.

---

# Fractal Fashion — Julia Set Renderer in C

### Overview

**Fractal Fashion** is a simple exploration of fractal geometry, implemented from scratch in **C** using the **SDL2** library for visualization.
It renders the **Julia set** — a complex mathematical structure defined by iterative functions over the complex plane.

The goal of this project was to learn:

* How floating-point math and complex number operations translate into pixel rendering.
* How graphical output pipelines work at a low level using software rendering.
* How color mapping (via HSL to RGB conversion) affects visual clarity and gradient smoothness.

---

### Features

* **Pure C implementation** (no external math or graphics engines).
* **Software-based pixel plotting** using SDL2.
* **Configurable constants** for different Julia set variations.
* **Smooth color gradients** via HSL → RGB conversion.
* **Simple keyboard/mouse zoom controls** (optional, if you’ve added them).

---

### Technical Notes

* Each pixel represents a complex coordinate `(x + yi)` mapped from screen space.
* Iteration limit and escape radius determine convergence and visual density.
* HSL-based coloring ensures smoother hue transitions compared to raw RGB mapping.
* The renderer runs entirely on CPU — no GPU acceleration or SIMD optimizations (yet).

---

### Build & Run

```bash
gcc fractal_fashion.c -lSDL2 -lm -o fractal_fashion
./fractal_fashion
```

Requires:

* **SDL2 development libraries**
* **GCC/Clang** on Linux or MinGW on Windows

---

### Learning Outcome

This project helped me understand:

* The numerical precision issues in iterative rendering.
* How to handle performance trade-offs in software-based visualization.
* How to build a simple rendering pipeline using SDL.

---

### Future Improvements

* Add SIMD acceleration (SSE/AVX) for faster iteration loops.
* Implement smooth zoom transitions and parameter morphing.
* Port to Vulkan or DirectX for GPU-based fractal exploration.

---

Would you like me to make a **matching GitHub description + tags section** (short one-liner and keywords for the repo metadata)? It helps your project get picked up by recruiters searching terms like *C, graphics, renderer, fractal, performance*.
