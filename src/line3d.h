#ifndef LINE3D_H
#define LINE3D_H

#include <godot_cpp/classes/geometry_instance3d.hpp>

#include "line_mesh.h"

namespace godot {

class Line3D : public GeometryInstance3D {
	GDCLASS(Line3D, GeometryInstance3D)

public:
	enum LineAlignment {
		ALIGN_TO_VIEW,
		FACE_TOWARD_POSITION,
		ALIGN_TO_NORMAL,
	};

private:
	Ref<LineMesh> m_mesh;
	bool m_is_dirty = false;
	Line3D::LineAlignment m_alignment = ALIGN_TO_NORMAL;

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	Line3D();
	~Line3D();

	Ref<LineMesh> get_mesh() const;

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

	Ref<Curve> get_width_curve() const;
	void set_width_curve(const Ref<Curve> &p_width_curve);

	Color get_color() const;
	void set_color(const Color &p_color);

	Ref<Gradient> get_gradient() const;
	void set_gradient(const Ref<Gradient> &p_gradient);

	Line3D::LineAlignment get_alignment() const;
	void set_alignment(Line3D::LineAlignment p_alignment);

	Vector3 get_normal() const;
	void set_normal(const Vector3 &p_normal);

	bool get_use_global_space() const;
	void set_use_global_space(bool p_use_global_space);

	Transform3D get_mesh_transform() const;
	void set_mesh_transform(const Transform3D &p_transform);
};

} // namespace godot

VARIANT_ENUM_CAST(Line3D::LineAlignment);

#endif // LINE3D_H
