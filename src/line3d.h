#ifndef LINE3D_H
#define LINE3D_H

#include <godot_cpp/classes/geometry_instance3d.hpp>

#include "line3d_mesh.h"

namespace godot {

class Line3D : public GeometryInstance3D {
	GDCLASS(Line3D, GeometryInstance3D)

private:
	Ref<Line3DMesh> m_mesh;
	bool m_is_dirty = false;

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	Line3D();
	~Line3D();

	Ref<Line3DMesh> get_mesh() const;

	void add_point(const Vector3 &p_position, int64_t p_index = -1);
	void clear_points();
	Vector3 get_point_position(int64_t p_index) const;
	PackedVector3Array get_points() const;
	void remove_point(int64_t p_index);
	void set_point_position(int64_t p_index, const Vector3 &p_position);
	void set_points(const PackedVector3Array &p_points);

	bool get_closed() const;
	void set_closed(bool p_closed);

	double get_width() const;
	void set_width(double p_width);
};

}

#endif // LINE3D_H