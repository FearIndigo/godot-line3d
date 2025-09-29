#ifndef LINE_MESH_H
#define LINE_MESH_H

#include <godot_cpp/classes/immediate_mesh.hpp>
#include <godot_cpp/classes/curve.hpp>
#include <godot_cpp/classes/gradient.hpp>

namespace godot
{

	class LineMesh : public ImmediateMesh
	{
		GDCLASS(LineMesh, ImmediateMesh)

	public:
		enum FaceAlignment
		{
			FACE_TOWARD_POSITION,
			ALIGN_TO_NORMAL,
		};

	private:
		PackedVector3Array m_points;
		bool m_simplify = true;
		double m_tolerance = 0.02;
		bool m_closed = false;
		double m_width = 0.2;
		Ref<Curve> m_width_curve;
		Color m_color = Color(1, 1, 1, 1);
		Ref<Gradient> m_gradient;
		LineMesh::FaceAlignment m_alignment = ALIGN_TO_NORMAL;
		Vector3 m_normal = Vector3(0, 0, 1);
		bool m_use_transform = false;
		Transform3D m_transform;
		Transform3D m_inverse_transform;
		bool m_draw_caps = true;
		int m_cap_smooth = 5;
		bool m_draw_corners = true;
		int m_corner_smooth = 5;
		bool m_update_length = false;
		float m_length = 0.0;

	protected:
		static void _bind_methods();

		PackedVector3Array _douglas_peucker(const PackedVector3Array &p_points, double p_epsilon) const;
		Vector3 _get_position_alignment(const Vector3 &p_position) const;
		PackedVector3Array _get_simplified_points() const;
		Vector3 _transform_direction(const Vector3 &p_local_direction) const;
		Vector3 _transform_position(const Vector3 &p_local_position) const;

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

		bool get_simplify() const;
		void set_simplify(bool p_simplify);

		double get_tolerance() const;
		void set_tolerance(double p_tolerance);

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

		LineMesh::FaceAlignment get_alignment() const;
		void set_alignment(LineMesh::FaceAlignment p_alignment);

		Vector3 get_normal() const;
		void set_normal(const Vector3 &p_normal);

		bool get_use_transform() const;
		void set_use_transform(bool p_use_transform);

		Transform3D get_transform() const;
		void set_transform(const Transform3D &p_transform);

		bool get_draw_caps() const;
		void set_draw_caps(bool p_draw_caps);

		int get_cap_smooth() const;
		void set_cap_smooth(int p_cap_smooth);

		bool get_draw_corners() const;
		void set_draw_corners(bool p_draw_corners);

		int get_corner_smooth() const;
		void set_corner_smooth(int p_corner_smooth);

		double get_length();
		void update_length();

		void redraw();
	};

} // namespace godot

VARIANT_ENUM_CAST(LineMesh::FaceAlignment);

#endif // LINE_MESH_H
