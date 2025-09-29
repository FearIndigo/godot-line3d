#include "trail3d.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

void Trail3D::_bind_methods()
{
	BIND_ENUM_CONSTANT(ALIGN_TO_VIEW);
	BIND_ENUM_CONSTANT(FACE_TOWARD_POSITION);
	BIND_ENUM_CONSTANT(ALIGN_TO_NORMAL);

	ClassDB::bind_method(D_METHOD("set_dirty"), &Trail3D::set_dirty);

	ClassDB::bind_method(D_METHOD("set_simplify", "simplify"), &Trail3D::set_simplify);
	ClassDB::bind_method(D_METHOD("get_simplify"), &Trail3D::get_simplify);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "simplify"), "set_simplify", "get_simplify");

	ClassDB::bind_method(D_METHOD("set_tolerance", "tolerance"), &Trail3D::set_tolerance);
	ClassDB::bind_method(D_METHOD("get_tolerance"), &Trail3D::get_tolerance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tolerance", PROPERTY_HINT_RANGE, "0,2,,or_greater"), "set_tolerance", "get_tolerance");

	ClassDB::bind_method(D_METHOD("set_width", "width"), &Trail3D::set_width);
	ClassDB::bind_method(D_METHOD("get_width"), &Trail3D::get_width);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "width", PROPERTY_HINT_RANGE, "0,10,,or_greater"), "set_width", "get_width");

	ClassDB::bind_method(D_METHOD("set_width_curve", "curve"), &Trail3D::set_width_curve);
	ClassDB::bind_method(D_METHOD("get_width_curve"), &Trail3D::get_width_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "width_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_width_curve", "get_width_curve");

	ClassDB::bind_method(D_METHOD("set_color", "color"), &Trail3D::set_color);
	ClassDB::bind_method(D_METHOD("get_color"), &Trail3D::get_color);
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");

	ClassDB::bind_method(D_METHOD("set_gradient", "gradient"), &Trail3D::set_gradient);
	ClassDB::bind_method(D_METHOD("get_gradient"), &Trail3D::get_gradient);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "gradient", PROPERTY_HINT_RESOURCE_TYPE, "Gradient"), "set_gradient", "get_gradient");

	ClassDB::bind_method(D_METHOD("set_alignment", "alignment"), &Trail3D::set_alignment);
	ClassDB::bind_method(D_METHOD("get_alignment"), &Trail3D::get_alignment);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "alignment", PROPERTY_HINT_ENUM, "Align To View,Face Toward Position,Align To Normal"), "set_alignment", "get_alignment");

	ClassDB::bind_method(D_METHOD("set_normal", "normal"), &Trail3D::set_normal);
	ClassDB::bind_method(D_METHOD("get_normal"), &Trail3D::get_normal);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "normal"), "set_normal", "get_normal");

	ClassDB::bind_method(D_METHOD("set_lifetime", "lifetime"), &Trail3D::set_lifetime);
	ClassDB::bind_method(D_METHOD("get_lifetime"), &Trail3D::get_lifetime);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "lifetime", PROPERTY_HINT_RANGE, "0,10000,,or_greater"), "set_lifetime", "get_lifetime");

	ClassDB::bind_method(D_METHOD("set_min_vertex_distance", "min_vertex_distance"), &Trail3D::set_min_vertex_distance);
	ClassDB::bind_method(D_METHOD("get_min_vertex_distance"), &Trail3D::get_min_vertex_distance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_vertex_distance", PROPERTY_HINT_RANGE, "0,5,,or_greater"), "set_min_vertex_distance", "get_min_vertex_distance");

	ClassDB::bind_method(D_METHOD("set_emitting", "emitting"), &Trail3D::set_emitting);
	ClassDB::bind_method(D_METHOD("get_emitting"), &Trail3D::get_emitting);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "emitting"), "set_emitting", "get_emitting");

	ClassDB::bind_method(D_METHOD("set_draw_caps", "draw_caps"), &Trail3D::set_draw_caps);
	ClassDB::bind_method(D_METHOD("get_draw_caps"), &Trail3D::get_draw_caps);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "draw_caps"), "set_draw_caps", "get_draw_caps");

	ClassDB::bind_method(D_METHOD("set_cap_smooth", "cap_smooth"), &Trail3D::set_cap_smooth);
	ClassDB::bind_method(D_METHOD("get_cap_smooth"), &Trail3D::get_cap_smooth);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cap_smooth"), "set_cap_smooth", "get_cap_smooth");

	ClassDB::bind_method(D_METHOD("set_draw_corners", "draw_corners"), &Trail3D::set_draw_corners);
	ClassDB::bind_method(D_METHOD("get_draw_corners"), &Trail3D::get_draw_corners);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "draw_corners"), "set_draw_corners", "get_draw_corners");

	ClassDB::bind_method(D_METHOD("set_corner_smooth", "corner_smooth"), &Trail3D::set_corner_smooth);
	ClassDB::bind_method(D_METHOD("get_corner_smooth"), &Trail3D::get_corner_smooth);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "corner_smooth"), "set_corner_smooth", "get_corner_smooth");
}

Trail3D::Trail3D()
{
	// Initialize any variables here.
	m_mesh.instantiate();
	m_mesh->set_use_transform(true);
	set_base(m_mesh->get_rid());
}

Trail3D::~Trail3D()
{
	// Add your cleanup here.
}

#pragma region _is_dirty

void Trail3D::set_dirty()
{
	_is_dirty = true;
}

#pragma endregion

#pragma region m_simplify

bool Trail3D::get_simplify() const
{
	return m_mesh->get_simplify();
}

void Trail3D::set_simplify(bool p_simplify)
{
	m_mesh->set_simplify(p_simplify);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_tolerance

double Trail3D::get_tolerance() const
{
	return m_mesh->get_tolerance();
}

void Trail3D::set_tolerance(double p_tolerance)
{
	m_mesh->set_tolerance(p_tolerance);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_width

double Trail3D::get_width() const
{
	return m_mesh->get_width();
}

void Trail3D::set_width(double p_width)
{
	m_mesh->set_width(p_width);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_width_curve

Ref<Curve> Trail3D::get_width_curve() const
{
	return m_mesh->get_width_curve();
}

void Trail3D::set_width_curve(const Ref<Curve> &p_width_curve)
{
	m_mesh->set_width_curve(p_width_curve);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_color

Color Trail3D::get_color() const
{
	return m_mesh->get_color();
}

void Trail3D::set_color(const Color &p_color)
{
	m_mesh->set_color(p_color);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_gradient

Ref<Gradient> Trail3D::get_gradient() const
{
	return m_mesh->get_gradient();
}

void Trail3D::set_gradient(const Ref<Gradient> &p_gradient)
{
	m_mesh->set_gradient(p_gradient);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_alignment

Trail3D::TrailAlignment Trail3D::get_alignment() const
{
	return m_alignment;
}

void Trail3D::set_alignment(Trail3D::TrailAlignment p_alignment)
{
	m_alignment = p_alignment;
	switch (m_alignment)
	{
	case ALIGN_TO_VIEW:
	case FACE_TOWARD_POSITION:
		m_mesh->set_alignment(LineMesh::FaceAlignment::FACE_TOWARD_POSITION);
		break;
	case ALIGN_TO_NORMAL:
		m_mesh->set_alignment(LineMesh::FaceAlignment::ALIGN_TO_NORMAL);
	}
	_is_dirty = true;
}

#pragma endregion

#pragma region m_normal

Vector3 Trail3D::get_normal() const
{
	return m_mesh->get_normal();
}
void Trail3D::set_normal(const Vector3 &p_normal)
{
	m_mesh->set_normal(p_normal);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_lifetime

uint64_t Trail3D::get_lifetime() const
{
	return m_lifetime;
}

void Trail3D::set_lifetime(uint64_t p_lifetime)
{
	m_lifetime = p_lifetime;
}

#pragma endregion

#pragma region m_min_vertex_distance

double Trail3D::get_min_vertex_distance() const
{
	return m_min_vertex_distance;
}

void Trail3D::set_min_vertex_distance(double p_min_vertex_distance)
{
	m_min_vertex_distance = p_min_vertex_distance;
	_is_dirty = true;
}

#pragma endregion

#pragma region m_emitting

bool Trail3D::get_emitting() const
{
	return m_emmitting;
}

void Trail3D::set_emitting(bool p_emitting)
{
	m_emmitting = p_emitting;
	_is_dirty = true;
}

#pragma endregion

#pragma region m_draw_caps

bool Trail3D::get_draw_caps() const
{
	return m_mesh->get_draw_caps();
}

void Trail3D::set_draw_caps(bool p_draw_caps)
{
	m_mesh->set_draw_caps(p_draw_caps);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_cap_smooth

int Trail3D::get_cap_smooth() const
{
	return m_mesh->get_cap_smooth();
}

void Trail3D::set_cap_smooth(int p_cap_smooth)
{
	m_mesh->set_cap_smooth(p_cap_smooth);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_draw_corners

bool Trail3D::get_draw_corners() const
{
	return m_mesh->get_draw_corners();
}

void Trail3D::set_draw_corners(bool p_draw_corners)
{
	m_mesh->set_draw_corners(p_draw_corners);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_corner_smooth

int Trail3D::get_corner_smooth() const
{
	return m_mesh->get_corner_smooth();
}

void Trail3D::set_corner_smooth(int p_corner_smooth)
{
	m_mesh->set_corner_smooth(p_corner_smooth);
	_is_dirty = true;
}

#pragma endregion

void Trail3D::_notification(int p_what)
{
	if (p_what == NOTIFICATION_PROCESS)
	{
		// Update transform
		Transform3D global_transform = get_global_transform();
		if (global_transform != m_mesh->get_transform())
		{
			m_mesh->set_transform(global_transform);
			_is_dirty = true;
		}

		// Update view alignment.
		if (m_alignment == ALIGN_TO_VIEW)
		{
			Camera3D *camera = get_viewport()->get_camera_3d();
			if (camera != nullptr)
			{
				Vector3 camera_position = camera->get_global_position();
				if (!camera_position.is_equal_approx(get_normal()))
				{
					set_normal(camera_position);
				}
			}
		}

		uint64_t time = Time::get_singleton()->get_ticks_msec();

		// Emit new points when moving.
		Vector3 current_position = m_mesh->get_transform().origin;
		if (m_emmitting && current_position.is_equal_approx(m_previous_position) == false)
		{
			if (m_spawn_times.empty() || m_last_emmited_position.distance_to(current_position) >= m_min_vertex_distance)
			{
				// No points or far enough from last point.
				if (m_leading_point)
				{
					// Use leading point as new point.
					m_leading_point = false;
					m_mesh->set_point_position(0, current_position);
					m_spawn_times.back() = time;
				}
				else
				{
					// Add new point.
					m_mesh->add_point(current_position, 0);
					m_spawn_times.push_back(time);
				}
				m_last_emmited_position = current_position;
				_is_dirty = true;
			}
			else
			{
				// Not far enough from last spawned point, update leading point position.
				if (m_leading_point)
				{
					// Update leading point.
					m_mesh->set_point_position(0, current_position);
					m_spawn_times.back() = time;
				}
				else
				{
					// Add leading point.
					m_leading_point = true;
					m_mesh->add_point(current_position, 0);
					m_spawn_times.push_back(time);
				}
				_is_dirty = true;
			}
			m_previous_position = current_position;
		}

		// Remove old points and update trailing point.
		while (!m_spawn_times.empty())
		{
			uint64_t current_expire_time = m_spawn_times[0] + m_lifetime;
			if (current_expire_time < time)
			{
				int64_t num_points = m_mesh->get_points().size();
				uint64_t next_expire_time = m_spawn_times.size() > 1 ? m_spawn_times[1] + m_lifetime : 0;
				if (next_expire_time > time)
				{
					// Lerp trailing point to next point.
					uint32_t diff = next_expire_time - current_expire_time;
					float t = 1.0 - float(next_expire_time - time) / diff;
					m_spawn_times[0] += diff * t;
					m_mesh->set_point_position(num_points - 1, m_mesh->get_point_position(num_points - 1).lerp(m_mesh->get_point_position(num_points - 2), t));
					_is_dirty = true;
					// Next point not old enough to remove.
					break;
				}
				else
				{
					// Remove trailing point.
					m_spawn_times.pop_front();
					m_mesh->remove_point(num_points - 1);
					_is_dirty = true;
					if (m_leading_point && num_points == 1)
					{
						// Leading point was removed.
						m_leading_point = false;
					}
				}
			}
			else
			{
				// Last point not old enough to remove.
				break;
			}
		}

		// Redraw mesh.
		if (_is_dirty)
		{
			m_mesh->redraw();
			_is_dirty = false;
		}
	}
}
