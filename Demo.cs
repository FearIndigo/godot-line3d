using Godot;
using FearIndigo.GodotLine3D;

public partial class Demo : Node3D
{
    [Export] private Vector3 _maxOffset = new (1f, 0, 0);
    [Export] private Vector3 _startPos = Vector3.Zero;
    [Export] private float _interval = 1f;
    [Export] private Line3D _line3D;

    private float _time;

    public override void _Process(double delta)
    {
        // Move point position over time...
        _time = (_time + (float)delta) % _interval;
        var anim = Mathf.Abs(_time / _interval * 2f - 1f) * 2f - 1f;
        _line3D?.SetPointPosition(0, _startPos + _maxOffset * anim);
    }
}
