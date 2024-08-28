#ifndef LINE3D_MESH_H
#define LINE3D_MESH_H

#include <godot_cpp/classes/immediate_mesh.hpp>
#include <godot_cpp/variant/packed_vector3_array.hpp>

namespace godot {

class Line3DMesh : public ImmediateMesh {
	GDCLASS(Line3DMesh, ImmediateMesh)

private:
	PackedVector3Array m_points;

protected:
	static void _bind_methods();

public:
	Line3DMesh();
	~Line3DMesh();

	void set_points(const PackedVector3Array &p_points);
	PackedVector3Array get_points() const;

	void redraw();
};

}

#endif // LINE3D_MESH_H