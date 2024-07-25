using System.Linq;
using Godot;
using Godot.Collections;

namespace FearIndigo.GodotLine3D;

[Tool, Icon("res://addons/godot_line3d/icon_line3d.svg")]
public partial class Line3D : Node3D
{
    /// <summary>
    /// Different modes for calculating line normals and alignment.
    /// </summary>
    public enum AlignmentMode
    {
        /// <summary>
        /// Line will face towards the currently active camera.
        /// </summary>
        View,
        /// <summary>
        /// Line will be set to transformZ.
        /// </summary>
        TransformZ,
        /// <summary>
        /// Line normals will be set to NormalTarget.
        /// </summary>
        /// <note>Coordinate space is determined by UseWorldSpace value.</note>
        Custom,
        /// <summary>
        /// Line normals will face towards NormalTarget.
        /// </summary>
        /// <note>Coordinate space is determined by UseWorldSpace value.</note>
        CustomTarget
    }
    
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
            Mesh.Points = value;
            MeshNeedsUpdate = true;
            UpdateConfigurationWarnings();
        }
    }
    private Array<Vector3> _points = new (){Vector3.Zero, Vector3.Up};
    
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
            Mesh.Width = value;
            MeshNeedsUpdate = true;
            UpdateConfigurationWarnings();
        }
    }
    private float _width = 0.2f;

    /// <summary>
    /// The number of vertices used to draw a cap at the ends of the line.
    /// </summary>
    [Export(PropertyHint.Range, "0,16,,or_greater")]
    public virtual int CapVertices
    {
        get => _capVertices;
        set
        {
            _capVertices = value;
            Mesh.CapVertices = value;
            MeshNeedsUpdate = true;
        }
    }
    private int _capVertices;
    
    /// <summary>
    /// The number of vertices used to draw a curve at the corners within the line.
    /// </summary>
    [Export(PropertyHint.Range, "0,16,,or_greater")]
    public virtual int CornerVertices
    {
        get => _cornerVertices;
        set
        {
            _cornerVertices = value;
            Mesh.CornerVertices = value;
            MeshNeedsUpdate = true;
        }
    }
    private int _cornerVertices;
    
    /// <summary>
    /// When true points are in world space coordinates. When false points are in local coordinates.
    /// </summary>
    [Export]
    public bool UseWorldSpace
    {
        get => _useWorldSpace;
        set
        {
            _useWorldSpace = value;
            SetNotifyTransform(!value);
            MeshNeedsUpdate = true;
            TransformNeedsUpdate = true;
        }
    }
    private bool _useWorldSpace;
    
    /// <summary>
    /// Defines how vertex normals/faces are calculated and aligned.
    /// </summary>
    [Export]
    public virtual AlignmentMode Alignment
    {
        get => _alignment;
        set
        {
            _alignment = value;
            SetMeshNormalModeFromAlignment();
            MeshNeedsUpdate = true;
        }
    }
    private AlignmentMode _alignment = AlignmentMode.View;
    
    [Export]
    protected virtual Vector3 NormalTarget
    {
        get => _normalTarget;
        set
        {
            _normalTarget = value;
            Mesh.NormalTarget = value;
            MeshNeedsUpdate = true;
            UpdateConfigurationWarnings();
        }
    }
    private Vector3 _normalTarget = Vector3.Back;
    
    [Export]
    public virtual RenderingServer.ShadowCastingSetting ShadowMode
    {
        get => _shadowMode;
        set
        {
            _shadowMode = value;
            CastShadowSettingNeedsUpdate = true;
        }
    }
    private RenderingServer.ShadowCastingSetting _shadowMode = RenderingServer.ShadowCastingSetting.Off;
    
    [Export]
    public virtual Material MaterialOverride
    {
        get
        {
            if(_materialOverride != null) return _materialOverride;
            MaterialOverride = new StandardMaterial3D();
            return _materialOverride;
        }
        set
        {
            _materialOverride = value;
            MaterialNeedsUpdate = true;
            UpdateConfigurationWarnings();
        }
    }
    private Material _materialOverride = new StandardMaterial3D();
    
    protected virtual LineMesh Mesh
    {
        get
        {
            if (_mesh != null) return _mesh;
            Mesh = new();
            return _mesh;
        }
        set
        {
            _mesh = value;
            _mesh.Points = Points;
            _mesh.Width = Width;
            _mesh.CapVertices = CapVertices;
            _mesh.CornerVertices = CornerVertices;
            _mesh.NormalTarget = NormalTarget;
            SetMeshNormalModeFromAlignment();
        }
    }
    private LineMesh _mesh;
    
    protected bool MeshNeedsUpdate;
    protected bool TransformNeedsUpdate;
    protected bool MaterialNeedsUpdate;
    protected bool CastShadowSettingNeedsUpdate;
    
    private Rid _rid;

    public override void _Ready()
    {
        SetNotifyTransform(!UseWorldSpace);
    }

    public override void _EnterTree()
    {
        // Create a visual instance
        _rid = RenderingServer.InstanceCreate();
        
        // Set the scenario from the world, this ensures it appears with the same objects as the scene
        var scenario = GetWorld3D().Scenario;
        RenderingServer.InstanceSetScenario(GetRid(), scenario);
        
        // Add the mesh to the visual instance
        RenderingServer.InstanceSetBase(GetRid(), Mesh.GetRid());
        
        // Update line
        UpdateNormalTarget();
        UpdateMesh();
        UpdateInstanceTransform();
        UpdateInstanceMaterial();
        UpdateInstanceCastShadowsSetting();
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

        if(NormalTarget.IsEqualApprox(Vector3.Zero))
            warnings.Add("NormalTarget must be non-zero.");
        
        return warnings.ToArray();
    }

    public override void _Notification(int what)
    {
        switch ((long)what)
        {
            case NotificationTransformChanged:
                TransformNeedsUpdate = true;
                break;
        }
    }

    public override void _Process(double delta)
    {
        UpdateNormalTarget();
        
        if (MeshNeedsUpdate) UpdateMesh();
        if (TransformNeedsUpdate) UpdateInstanceTransform();
        if (MaterialNeedsUpdate) UpdateInstanceMaterial();
        if (CastShadowSettingNeedsUpdate) UpdateInstanceCastShadowsSetting();
    }

    public void SetMeshNormalModeFromAlignment()
    {
        switch (Alignment)
        {
            case AlignmentMode.View:
            case AlignmentMode.CustomTarget:
                Mesh.NormalMode = LineMesh.NormalCalculationMode.Target;
                break;
            case AlignmentMode.TransformZ:
            case AlignmentMode.Custom:
            default:
                Mesh.NormalMode = LineMesh.NormalCalculationMode.Normal;
                break;
        }
    }
    
    /// <summary>
    /// Update normal target. If target changed then queue mesh update.
    /// </summary>
    public virtual void UpdateNormalTarget()
    {
        switch (Alignment)
        {
            // Update mesh if camera position or transform has changed
            case AlignmentMode.View:
                var cameraPosition = GetActiveCamera3D().GlobalPosition;
                var relativeCameraPosition =
                    UseWorldSpace ? cameraPosition : GlobalTransform.Inverse() * cameraPosition;
                if (!NormalTarget.IsEqualApprox(relativeCameraPosition) || TransformNeedsUpdate)
                {
                    NormalTarget = relativeCameraPosition;
                }
                break;
            // Update mesh if transformZ has changed
            case AlignmentMode.TransformZ:
                var transformZ = UseWorldSpace ? GlobalTransform.Basis.Z : Vector3.Back;
                if (!NormalTarget.IsEqualApprox(transformZ))
                {
                    NormalTarget = transformZ;
                }
                break;
        }
    }

    /// <summary>
    /// Get the currently active Camera3D.
    /// </summary>
    /// <note>In the editor this will return the currently active editor Camera3D.</note>
    protected virtual Camera3D GetActiveCamera3D()
    {
        return Engine.IsEditorHint() ? EditorInterface.Singleton.GetEditorViewport3D().GetCamera3D() : GetViewport().GetCamera3D();
    }
    
    public virtual void UpdateMesh()
    {
        Mesh.Update();
        MeshNeedsUpdate = false;
    }

    public virtual void UpdateInstanceTransform()
    {
        RenderingServer.InstanceSetTransform(GetRid(), UseWorldSpace ? Transform3D.Identity : GlobalTransform);
        TransformNeedsUpdate = false;
    }
    
    public virtual void UpdateInstanceMaterial()
    {
        RenderingServer.InstanceGeometrySetMaterialOverride(GetRid(), MaterialOverride.GetRid());
        MaterialNeedsUpdate = false;
    }

    public virtual void UpdateInstanceCastShadowsSetting()
    {
        RenderingServer.InstanceGeometrySetCastShadowsSetting(GetRid(), ShadowMode);
        CastShadowSettingNeedsUpdate = false;
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
        
        MeshNeedsUpdate = true;
        UpdateConfigurationWarnings();
    }

    /// <summary>
    /// Removes all points from the polyline, making it empty.
    /// </summary>
    public void ClearPoints()
    {
        Points.Clear();

        MeshNeedsUpdate = true;
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
        
        MeshNeedsUpdate = true;
        UpdateConfigurationWarnings();
    }

    /// <summary>
    /// Overwrites the position of the point at the given index with the supplied position.
    /// </summary>
    public void SetPointPosition(int index, Vector3 position)
    {
        Points[index] = position;
        
        MeshNeedsUpdate = true;
    }

    /// <summary>
    /// Set the whole points array to the provided points.
    /// </summary>
    public void SetPoints(Array<Vector3> points)
    {
        Points = points.Duplicate();

        MeshNeedsUpdate = true;
        UpdateConfigurationWarnings();
    }

    public Rid GetRid()
    {
        return _rid;
    }
}