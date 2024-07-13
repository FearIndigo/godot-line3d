using Godot;

namespace FearIndigo.Line3D;

[Tool]
[Icon("res://addons/godot-line3d/icon.svg")]
public partial class Line3D : Node3D
{
    private LineMesh _lm = new LineMesh();
    
    public override void _EnterTree()
    {
    }
}