#ifndef LINE3D_MESH_H
#define LINE3D_MESH_H

#include <godot_cpp/classes/immediate_mesh.hpp>

namespace godot {

class Line3DMesh : public ImmediateMesh {
	GDCLASS(Line3DMesh, ImmediateMesh)

private:
	PackedVector3Array m_points;
	bool m_closed = false;

protected:
	static void _bind_methods();
	double _get_line_length() const;
	int64_t _get_num_segments() const;

public:
	Line3DMesh();
	~Line3DMesh();

	void add_point(const Vector3 &p_position, int64_t p_index = -1);
	void clear_points();
	Vector3 get_point_position(int64_t p_index) const;
	PackedVector3Array get_points() const;
	void remove_point(int64_t p_index);
	void set_point_position(int64_t p_index, const Vector3 &p_position);
	void set_points(const PackedVector3Array &p_points);

	bool get_closed() const;
	void set_closed(bool p_closed);

	void redraw();
};

}

#endif // LINE3D_MESH_H