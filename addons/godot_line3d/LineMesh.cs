using Godot;
using Godot.Collections;

namespace FearIndigo.GodotLine3D;

[Icon("res://addons/godot_line3d/icon_linemesh.svg")]
public partial class LineMesh: ImmediateMesh
{
    /// <summary>
    /// Different modes for calculating normals and alignment of line.
    /// </summary>
    public enum NormalCalculationMode
    {
        /// <summary>
        /// Vertex normals will face towards NormalTarget.
        /// </summary>
        Target,
        /// <summary>
        /// Vertex normals will be set to the value of NormalTarget.
        /// </summary>
        Normal,
    }

    public NormalCalculationMode NormalMode;
    public Vector3 NormalTarget;
    public int CornerVertices;
    public int CapVertices;
    public Array<Vector3> Points;
    public float Width;
    
    /// <summary>
    /// Create line mesh.
    /// </summary>
    public void Update()
    {
        // Clear current line mesh
        ClearSurfaces();
        
        // Need at least 2 points to draw line mesh
        if (Points.Count < 2) return;
        
        // Begin line mesh creation
        SurfaceBegin(PrimitiveType.Triangles);
        
        // Add first segment
        AddLineSegment(Points[0], Points[1], Points.Count > 2 ? Points[2] : null);
        
        // Add remaining line segments
        for (var i = 1; i < Points.Count - 1; i++)
        {
            AddLineSegment(Points[i], Points[i + 1], i + 2 < Points.Count ? Points[i + 2] : null, Points[i - 1]);
        }
        
        // Finish line mesh creation
        SurfaceEnd();
    }

    private void AddLineSegment(Vector3 startPoint, Vector3 endPoint, Vector3? nextPoint = null, Vector3? previousPoint = null)
    {
        var inDir = (startPoint - previousPoint)?.Normalized();
        var outDir = (endPoint - startPoint).Normalized();
        var nextDir = (nextPoint - endPoint)?.Normalized();
        var startCross = ((outDir + inDir.GetValueOrDefault(outDir)) / 2f).Cross(CalculateNormal(startPoint)).Normalized();
        var endCross = ((outDir + nextDir.GetValueOrDefault(outDir)) / 2f).Cross(CalculateNormal(endPoint)).Normalized();
        
        var vertices = new[]
        {
            startPoint + startCross * Width / 2f,
            startPoint - startCross * Width / 2f,
            endPoint + endCross * Width / 2f,
            endPoint - endCross * Width / 2f,
        };

        // First triangle
        AddSegmentVertex(vertices[0]);
        AddSegmentVertex(vertices[1]);
        AddSegmentVertex(vertices[3]);
        
        // Second triangle
        AddSegmentVertex(vertices[0]);
        AddSegmentVertex(vertices[3]);
        AddSegmentVertex(vertices[2]);
    }

    private void AddSegmentVertex(Vector3 vertex)
    {
        SurfaceSetNormal(Vector3.Up);
        SurfaceAddVertex(vertex);
    }

    private Vector3 CalculateNormal(Vector3 vertex)
    {
        switch (NormalMode)
        {
            case NormalCalculationMode.Target:
                return NormalTarget - vertex;
            case NormalCalculationMode.Normal:
            default:
                return NormalTarget;
        }
    }
}