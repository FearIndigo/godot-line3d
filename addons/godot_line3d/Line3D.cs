using System.Linq;
using Godot;
using Godot.Collections;

namespace FearIndigo.Line3D;

[Tool, Icon("res://addons/godot_line3d/icon_line3d.svg")]
public partial class Line3D : Node3D
{
    /// <summary>
    /// The points of the polyline, interpreted in local 3D coordinates. Segments are drawn between the adjacent points
    /// in this array.
    /// </summary>
    /// <note>
    /// Set TopLevel to true for points to be interpreted in global space.
    /// </note>
    [Export]
    protected virtual Array<Vector3> Points
    {
        get => _points;
        set
        {
            _points = value;
            QueueUpdate();
            UpdateConfigurationWarnings();
        }
    }
    private Array<Vector3> _points = new (){Vector3.Zero, Vector3.Back};
    
    /// <summary>
    /// The polyline's width.
    /// </summary>
    [Export(PropertyHint.Range, "0,5,,or_greater")]
    public virtual float Width
    {
        get => _width;
        set
        {
            _width = value;
            QueueUpdate();
            UpdateConfigurationWarnings();
        }
    }
    private float _width = 0.2f;

    [Export]
    public virtual Material MaterialOverride
    {
        get => _materialOverride;
        set
        {
            _materialOverride = value;
            QueueUpdate();
            UpdateConfigurationWarnings();
        }
    }
    private Material _materialOverride = new StandardMaterial3D();
    
    protected bool NeedsUpdate;

    private LineMesh _lineMesh = new();
    private Rid _rid;

    public override void _Ready()
    {
        SetNotifyTransform(true);
    }

    public override void _EnterTree()
    {
        // Create a visual instance
        _rid = RenderingServer.InstanceCreate();
        
        // Set the scenario from the world, this ensures it appears with the same objects as the scene
        var scenario = GetWorld3D().Scenario;
        RenderingServer.InstanceSetScenario(_rid, scenario);
        
        // Add the mesh to the visual instance
        RenderingServer.InstanceSetBase(_rid, _lineMesh.GetRid());
        
        // Update mesh
        Update();
    }

    public override void _ExitTree()
    {
        RenderingServer.FreeRid(_rid);
    }

    public override string[] _GetConfigurationWarnings()
    {
        var warnings = new Array<string>();
        
        if (Points.Count < 2)
            warnings.Add("Line requires at least 2 points.");
        
        if (Width <= 0)
            warnings.Add("Line width must be greater than 0.");
        
        if (MaterialOverride == null)
            warnings.Add("Line requires a material.");

        return warnings.ToArray();
    }

    public override void _Notification(int what)
    {
        switch ((long)what)
        {
            case NotificationTransformChanged:
                QueueUpdate();
                break;
        }
    }

    public override void _Process(double delta)
    {
        // Ignore if nothing changed
        if (!NeedsUpdate) return;
        Update();
    }
    
    public virtual void Update()
    {
        // Update vertices
        _lineMesh.Update(Points, Width);
        
        // Update transform
        RenderingServer.InstanceSetTransform(_rid, GlobalTransform);
        
        // Update material
        RenderingServer.InstanceGeometrySetMaterialOverride(_rid, MaterialOverride.GetRid());
        
        // Finished updating
        NeedsUpdate = false;
    }
    
    /// <summary>
    /// Adds a point with the specified position relative to the polyline's own position. If no index is provided, the
    /// new point will be added to the end of the points array.<br/>
    /// <br/>
    /// If index is given, the new point is inserted before the existing point identified by the given index. The
    /// indices of the points after the new point get increased by 1. The provided index must not exceed the number of
    /// existing points in the polyline.
    /// </summary>
    public void AddPoint(Vector3 position, int index = -1)
    {
        if(index == -1) Points.Add(position);
        else Points.Insert(index, position);
        
        QueueUpdate();
        UpdateConfigurationWarnings();
    }

    /// <summary>
    /// Removes all points from the polyline, making it empty.
    /// </summary>
    public void ClearPoints()
    {
        Points.Clear();

        QueueUpdate();
        UpdateConfigurationWarnings();
    }

    /// <summary>
    /// Returns the number of points in the polyline.
    /// </summary>
    public int GetPointCount()
    {
        return Points.Count;
    }

    /// <summary>
    /// Returns the position of the point at the given index.
    /// </summary>
    public Vector3 GetPointPosition(int index)
    {
        return Points[index];
    }

    /// <summary>
    /// Removes the point at the given index from the polyline.
    /// </summary>
    public void RemovePoint(int index)
    {
        Points.RemoveAt(index);
        
        QueueUpdate();
        UpdateConfigurationWarnings();
    }

    /// <summary>
    /// Overwrites the position of the point at the given index with the supplied position.
    /// </summary>
    public void SetPointPosition(int index, Vector3 position)
    {
        Points[index] = position;
        
        QueueUpdate();
        UpdateConfigurationWarnings();
    }

    /// <summary>
    /// Set the whole points array to the provided points.
    /// </summary>
    public void SetPoints(Array<Vector3> points)
    {
        Points = points.Duplicate();
        
        QueueUpdate();
        UpdateConfigurationWarnings();
    }

    public void QueueUpdate()
    {
        NeedsUpdate = true;
    }

    public Rid GetRid()
    {
        return _rid;
    }
}