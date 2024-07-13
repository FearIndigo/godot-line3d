#if TOOLS
using Godot;

namespace FearIndigo.Line3D;

[Tool]
public partial class Plugin : EditorPlugin
{
	public override void _EnterTree()
	{
		var script = GD.Load<Script>("res://addons/godot_line3d/Line3D.cs");
		var texture = GD.Load<CompressedTexture2D>("res://addons/godot_line3d/icon.svg");
		AddCustomType("Line3D", "Node3D", script, texture);
	}

	public override void _ExitTree()
	{
		RemoveCustomType("Line3D");
	}
}
#endif
