#ifndef TRAIL3D_H
#define TRAIL3D_H

#include <queue>

#include <godot_cpp/classes/geometry_instance3d.hpp>

#include "line_mesh.h"

namespace godot
{

	class Trail3D : public GeometryInstance3D
	{
		GDCLASS(Trail3D, GeometryInstance3D)

	public:
		enum TrailAlignment
		{
			ALIGN_TO_VIEW,
			FACE_TOWARD_POSITION,
			ALIGN_TO_NORMAL,
		};

	private:
		Ref<LineMesh> m_mesh;
		TrailAlignment m_alignment = ALIGN_TO_NORMAL;
		uint64_t m_lifetime = 1000;
		double m_min_vertex_distance = 0.2;
		bool m_emmitting = true;
		std::queue<uint16_t> m_spawn_times;
		Vector3 m_last_emmited_position = Vector3(0, 0, 0);

	protected:
		static void _bind_methods();
		void _notification(int p_what);

		bool _is_dirty = false;

	public:
		Trail3D();
		~Trail3D();

		void _process(double delta) override {};

		void set_dirty();

		void clear_trail();

		bool get_simplify() const;
		void set_simplify(bool p_simplify);

		double get_tolerance() const;
		void set_tolerance(double p_tolerance);

		double get_width() const;
		void set_width(double p_width);

		Ref<Curve> get_width_curve() const;
		void set_width_curve(const Ref<Curve> &p_width_curve);

		Color get_color() const;
		void set_color(const Color &p_color);

		Ref<Gradient> get_gradient() const;
		void set_gradient(const Ref<Gradient> &p_gradient);

		TrailAlignment get_alignment() const;
		void set_alignment(TrailAlignment p_alignment);

		Vector3 get_normal() const;
		void set_normal(const Vector3 &p_normal);

		uint64_t get_lifetime() const;
		void set_lifetime(uint64_t p_lifetime);

		double get_min_vertex_distance() const;
		void set_min_vertex_distance(double p_min_vertex_distance);

		bool get_emitting() const;
		void set_emitting(bool p_emitting);
	};

} // namespace godot

VARIANT_ENUM_CAST(Trail3D::TrailAlignment);

#endif // TRAIL3D_H
