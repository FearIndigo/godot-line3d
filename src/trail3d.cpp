#include "trail3d.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/camera3d.hpp>

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
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tolerance", PROPERTY_HINT_RANGE, "0,5,,or_greater"), "set_tolerance", "get_tolerance");

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

	ClassDB::bind_method(D_METHOD("set_use_global_space", "use_global_space"), &Trail3D::set_use_global_space);
	ClassDB::bind_method(D_METHOD("get_use_global_space"), &Trail3D::get_use_global_space);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_global_space"), "set_use_global_space", "get_use_global_space");

	ClassDB::bind_method(D_METHOD("set_lifetime", "lifetime"), &Trail3D::set_lifetime);
	ClassDB::bind_method(D_METHOD("get_lifetime"), &Trail3D::get_lifetime);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lifetime", PROPERTY_HINT_RANGE, "0,10,,or_greater"), "set_lifetime", "get_lifetime");

	ClassDB::bind_method(D_METHOD("set_min_vertex_distance", "min_vertex_distance"), &Trail3D::set_min_vertex_distance);
	ClassDB::bind_method(D_METHOD("get_min_vertex_distance"), &Trail3D::get_min_vertex_distance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_vertex_distance", PROPERTY_HINT_RANGE, "0,5,,or_greater"), "set_min_vertex_distance", "get_min_vertex_distance");

	ClassDB::bind_method(D_METHOD("set_emitting", "emitting"), &Trail3D::set_emitting);
	ClassDB::bind_method(D_METHOD("get_emitting"), &Trail3D::get_emitting);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "emitting"), "set_emitting", "get_emitting");
}

Trail3D::Trail3D()
{
	// Initialize any variables here.
	m_mesh.instantiate();
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

#pragma region m_use_global_space

bool Trail3D::get_use_global_space() const
{
	return m_mesh->get_use_transform();
}

void Trail3D::set_use_global_space(bool p_use_global_space)
{
	m_mesh->set_use_transform(p_use_global_space);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_transform

Transform3D Trail3D::get_mesh_transform() const
{
	return m_mesh->get_transform();
}

void Trail3D::set_mesh_transform(const Transform3D &p_transform)
{
	m_mesh->set_transform(p_transform);
	_is_dirty = true;
}

#pragma endregion

#pragma region m_lifetime

double Trail3D::get_lifetime() const
{
	return m_lifetime;
}

void Trail3D::set_lifetime(double p_lifetime)
{
	m_lifetime = p_lifetime;
	_is_dirty = true;
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

void Trail3D::_notification(int p_what)
{
	if (p_what == NOTIFICATION_PROCESS)
	{
		// Update transform
		bool use_global_space = get_use_global_space();
		if (use_global_space)
		{
			Transform3D global_transform = get_global_transform();
			if (global_transform != get_mesh_transform())
			{
				set_mesh_transform(global_transform);
			}
		}

		// Update view alignment.
		if (m_alignment == ALIGN_TO_VIEW)
		{
			Camera3D *camera = get_viewport()->get_camera_3d();
			if (camera != nullptr)
			{
				Vector3 camera_position = use_global_space ? camera->get_global_position() : to_local(camera->get_global_position());
				if (!camera_position.is_equal_approx(get_normal()))
				{
					set_normal(camera_position);
				}
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
