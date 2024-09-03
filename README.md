# Godot Line3D

A 3D line renderer for Godot built using GDExtension.

Targets Godot version 4.3.

## Features

- **Line3D:** A new node to render a line in 3D space with a similar interface to the built-in Line2D node.
- **LineMesh:** A new mesh resource which is used by Line3D under the hood. It features a similar interface but is a bit more involved to use.
- **Trail3D:** A new node to render a trail in 3D space similar to unity's trail renderer component.

## Demo

A demo project is provided in the `line3d-demo` folder that showcases some basic functionality.

> [!NOTE]
> You are required to build the binaries for your target platforms for the demo project to work.

## Build

See the [Godot building from source docs](https://docs.godotengine.org/en/stable/contributing/development/compiling/index.html#toc-devel-compiling) for prerequisites.

```bash
# init godot-cpp submodule
git submodule update --init

# generate and compile the bindings (replacing <platform> with windows, linux or macos depending on your target OS)
scons platform=<platform>
```

## Installation

After compiling the binaries, copy the `line3d-demo/addons/line3d` folder into your project's `addons` folder.
