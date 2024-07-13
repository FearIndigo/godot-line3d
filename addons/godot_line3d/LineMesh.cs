using Godot;
using Godot.Collections;

namespace FearIndigo.Line3D;

[Icon("res://addons/godot_line3d/icon_linemesh.svg")]
public partial class LineMesh: ImmediateMesh
{
    /// <summary>
    /// Recreate the line mesh from the provided points array and width.
    /// </summary>
    public void Update(Array<Vector3> points, float width)
    {
        // Clear current line mesh
        ClearSurfaces();
        
        // Need at least 2 points to draw line mesh
        if (points.Count < 2) return;
        
        // Begin line mesh creation
        SurfaceBegin(PrimitiveType.Triangles);
        
        // Add first segment
        AddLineSegment(width, points[0], points[1], points.Count > 2 ? points[2] : null);
        
        // Add remaining line segments
        for (var i = 1; i < points.Count - 1; i++)
        {
            AddLineSegment(width, points[i], points[i + 1], i + 2 < points.Count ? points[i + 2] : null, points[i - 1]);
        }
        
        // Finish line mesh creation
        SurfaceEnd();
    }

    private void AddLineSegment(float width, Vector3 startPoint, Vector3 endPoint, Vector3? nextPoint = null, Vector3? previousPoint = null)
    {
        var inDir = (startPoint - previousPoint)?.Normalized();
        var outDir = (endPoint - startPoint).Normalized();
        var nextDir = (nextPoint - endPoint)?.Normalized();
        var startCross = ((outDir + inDir.GetValueOrDefault(outDir)) / 2f).Cross(Vector3.Up).Normalized();
        var endCross = ((outDir + nextDir.GetValueOrDefault(outDir)) / 2f).Cross(Vector3.Up).Normalized();
        
        var vertices = new[]
        {
            startPoint + startCross * width / 2f,
            startPoint - startCross * width / 2f,
            endPoint + endCross * width / 2f,
            endPoint - endCross * width / 2f,
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
}