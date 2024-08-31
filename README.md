# Godot Line3D

A 3D line renderer for Godot built using GDExtension.

Targets Godot version 4.3.

## Demo

A demo project is provided in the `line3d-demo` folder that showcases some basic functionality.

> **_NOTE:_** You are required to build the binaries for your target platforms for the demo project to work.

## Build

See the [Godot building from source docs](https://docs.godotengine.org/en/stable/contributing/development/compiling/index.html#toc-devel-compiling) for prerequisites.

```bash
# init godot-cpp submodule
git submodule update --init

# generate and compile the bindings (replacing <platform> with windows, linux or macos depending on your target OS)
scons platform=<platform>
```

## Usage

After compiling the binaries, copy the `line3d-demo/addons/line3d` folder into your project's `addons` folder.
