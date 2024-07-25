using Godot;

public partial class Rotate : Node3D
{
    [Export] private float _degPerSecond = 10f;

    public override void _Process(double delta)
    {
        // Rotate on y axis over time...
        var rot = GlobalRotation;
        rot.Y += Mathf.DegToRad(_degPerSecond) * (float)delta;
        GlobalRotation = rot;
    }
}
