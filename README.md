# Godot Line3D

A 3D line renderer for Godot built using GDExtension.

Targets Godot version 4.5.

## Features

- **LineMesh:** A new mesh resource used to draw a 3D line mesh.
- **Line3D:** A new node to render a line in 3D space.
- **Trail3D:** A new node to render a trail in 3D space.

## TODO

- LineMesh
  - Corners and caps
  - UV mapping
- Trail3D
  - Distance mode

## Demo

A demo project is provided in the `line3d-demo` folder that showcases some basic functionality.

Use W, A, S, D, Q, E keys to move. Hold shift to increase speed. Click and drag with the right mouse button to look.

> [!NOTE]
> You are required to build the binaries for your target platforms for the demo project to work.

## Build

See the [Godot building from source docs](https://docs.godotengine.org/en/stable/contributing/development/compiling/index.html#toc-devel-compiling) for prerequisites.

```bash
# init godot-cpp submodule
git submodule update --init

# generate and compile the bindings
# (replacing <platform> with windows, linux or macos depending on your target platform)
scons platform=<platform>
```

## Build Docs

Navigate to the demo folder after builing the library. `cd ./line3d-demo`

Run the command bellow to generate the xml files in `/doc_clases` folder.

```bash
# If godot is not part of you PATH then use the path to the godot executable instead
godot --doctool ../ --gdextension-docs
```

Edit the generated doc files in `/doc_classes`.

## Installation

First you need to compile the binaries for your target platforms (see build section above for more info). Once you have done that, copy the `line3d-demo/addons/line3d` folder into your project's `addons` folder.
