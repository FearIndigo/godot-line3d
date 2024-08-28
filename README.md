# Godot Line3D

A 3D line renderer for Godot built using GDExtension.

Targets Godot version 4.3.

## Demo

A demo project is provided in the `line3d-demo` folder that showcases basic functionality.

## Build

See [Godot building from source docs](https://docs.godotengine.org/en/stable/contributing/development/compiling/index.html#toc-devel-compiling) for prerequisites.

```bash
# init godot-cpp submodule
git submodule update --init

# generate and compile the bindings (replacing <platform> with windows, linux or macos depending on your OS)
scons platform=<platform>
```
