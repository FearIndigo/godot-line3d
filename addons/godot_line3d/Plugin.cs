#if TOOLS
using Godot;

namespace FearIndigo.Line3D;

[Tool]
public partial class Plugin : EditorPlugin
{
	public override void _EnterTree()
	{
		
		var line3DScript = GD.Load<Script>("res://addons/godot_line3d/Line3D.cs");
		var line3DIcon = GD.Load<CompressedTexture2D>("res://addons/godot_line3d/icon_line3d.svg");
		AddCustomType("Line3D", "Node3D", line3DScript, line3DIcon);
		
		var lineMeshScript = GD.Load<Script>("res://addons/godot_line3d/LineMesh.cs");
		var lineMeshIcon = GD.Load<CompressedTexture2D>("res://addons/godot_line3d/icon_linemesh.svg");
		AddCustomType("LineMesh", "ImmediateMesh", lineMeshScript, lineMeshIcon);
	}

	public override void _ExitTree()
	{
		RemoveCustomType("Line3D");
		RemoveCustomType("LineMesh");
	}
}
#endif
