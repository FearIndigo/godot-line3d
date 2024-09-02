#ifndef LINE3D_MESH_H
#define LINE3D_MESH_H

#include <godot_cpp/classes/immediate_mesh.hpp>
#include <godot_cpp/classes/curve.hpp>
#include <godot_cpp/classes/gradient.hpp>

namespace godot {

class LineMesh : public ImmediateMesh {
	GDCLASS(LineMesh, ImmediateMesh)

public:
	enum LineAlignment {
		FACE_TOWARD_POSITION,
		ALIGN_TO_NORMAL,
	};

private:
	PackedVector3Array m_points = {Vector3(0, 0, 0), Vector3(0, 1, 0)};
	bool m_closed = false;
	double m_width = 1.0;
	Ref<Curve> m_width_curve;
	Color m_color = Color(1, 1, 1, 1);
	Ref<Gradient> m_gradient;
	LineMesh::LineAlignment m_alignment = ALIGN_TO_NORMAL;
	Vector3 m_normal = Vector3(0, 0, 1);
	bool m_use_transform = false;
	Transform3D m_transform;
	Transform3D m_inverse_transform;

protected:
	static void _bind_methods();

	Vector3 _transform_position(const Vector3 &p_local_position) const;
	Vector3 _transform_direction(const Vector3 &p_local_direction) const;
	Vector3 _get_position_normal(const Vector3 &p_position) const;

public:
	LineMesh();
	~LineMesh();

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

	LineMesh::LineAlignment get_alignment() const;
	void set_alignment(LineMesh::LineAlignment p_alignment);

	Vector3 get_normal() const;
	void set_normal(const Vector3 &p_normal);

	bool get_use_transform() const;
	void set_use_transform(bool p_use_transform);

	Transform3D get_transform() const;
	void set_transform(const Transform3D &p_transform);

	void redraw();
};

} // namespace godot

VARIANT_ENUM_CAST(LineMesh::LineAlignment);

#endif // LINE3D_MESH_H
