#ifndef LINE3D_MESH_H
#define LINE3D_MESH_H

#include <godot_cpp/classes/immediate_mesh.hpp>
#include <godot_cpp/classes/curve.hpp>
#include <godot_cpp/classes/gradient.hpp>

namespace godot {

class LineMesh : public ImmediateMesh {
	GDCLASS(LineMesh, ImmediateMesh)

private:
	PackedVector3Array m_points;
	bool m_closed = false;
	double m_width = 1.0;
	Ref<Curve> m_width_curve;
	Color m_color = Color(1, 1, 1, 1);
	Ref<Gradient> m_gradient;

protected:
	static void _bind_methods();
	double _get_line_length() const;
	int64_t _get_num_segments() const;

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

	void redraw();
};

} // namespace godot

#endif // LINE3D_MESH_H
