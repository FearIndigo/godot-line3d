#include "line3d.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/camera3d.hpp>

using namespace godot;

void Line3D::_bind_methods() {
	BIND_ENUM_CONSTANT(ALIGN_TO_VIEW);
	BIND_ENUM_CONSTANT(FACE_TOWARD_POSITION);
	BIND_ENUM_CONSTANT(ALIGN_TO_NORMAL);

	ClassDB::bind_method(D_METHOD("get_mesh"), &Line3D::get_mesh);

	ClassDB::bind_method(D_METHOD("add_point", "position", "index"), &Line3D::add_point, DEFVAL(-1));
	ClassDB::bind_method(D_METHOD("clear_points"), &Line3D::clear_points);
	ClassDB::bind_method(D_METHOD("get_point_position", "index"), &Line3D::get_point_position);
	ClassDB::bind_method(D_METHOD("get_points"), &Line3D::get_points);
	ClassDB::bind_method(D_METHOD("remove_point", "index"), &Line3D::remove_point);
	ClassDB::bind_method(D_METHOD("set_point_position", "index", "position"), &Line3D::set_point_position);
	ClassDB::bind_method(D_METHOD("set_points", "points"), &Line3D::set_points);
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_VECTOR3_ARRAY, "points"), "set_points", "get_points");

	ClassDB::bind_method(D_METHOD("set_simplify", "simplify"), &Line3D::set_simplify);
	ClassDB::bind_method(D_METHOD("get_simplify"), &Line3D::get_simplify);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "simplify"), "set_simplify", "get_simplify");

	ClassDB::bind_method(D_METHOD("set_tolerance", "tolerance"), &Line3D::set_tolerance);
	ClassDB::bind_method(D_METHOD("get_tolerance"), &Line3D::get_tolerance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tolerance", PROPERTY_HINT_RANGE, "0,5,,or_greater"), "set_tolerance", "get_tolerance");

	ClassDB::bind_method(D_METHOD("set_closed", "closed"), &Line3D::set_closed);
	ClassDB::bind_method(D_METHOD("get_closed"), &Line3D::get_closed);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "closed"), "set_closed", "get_closed");

	ClassDB::bind_method(D_METHOD("set_width", "width"), &Line3D::set_width);
	ClassDB::bind_method(D_METHOD("get_width"), &Line3D::get_width);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "width", PROPERTY_HINT_RANGE, "0,10,,or_greater"), "set_width", "get_width");

	ClassDB::bind_method(D_METHOD("set_width_curve", "curve"), &Line3D::set_width_curve);
	ClassDB::bind_method(D_METHOD("get_width_curve"), &Line3D::get_width_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "width_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_width_curve", "get_width_curve");

	ClassDB::bind_method(D_METHOD("set_color", "color"), &Line3D::set_color);
	ClassDB::bind_method(D_METHOD("get_color"), &Line3D::get_color);
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");

	ClassDB::bind_method(D_METHOD("set_gradient", "gradient"), &Line3D::set_gradient);
	ClassDB::bind_method(D_METHOD("get_gradient"), &Line3D::get_gradient);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "gradient", PROPERTY_HINT_RESOURCE_TYPE, "Gradient"), "set_gradient", "get_gradient");

	ClassDB::bind_method(D_METHOD("set_alignment", "alignment"), &Line3D::set_alignment);
	ClassDB::bind_method(D_METHOD("get_alignment"), &Line3D::get_alignment);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "alignment", PROPERTY_HINT_ENUM, "Align To View,Face Toward Position,Align To Normal"), "set_alignment", "get_alignment");

	ClassDB::bind_method(D_METHOD("set_normal", "normal"), &Line3D::set_normal);
	ClassDB::bind_method(D_METHOD("get_normal"), &Line3D::get_normal);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "normal"), "set_normal", "get_normal");

	ClassDB::bind_method(D_METHOD("set_use_global_space", "use_global_space"), &Line3D::set_use_global_space);
	ClassDB::bind_method(D_METHOD("get_use_global_space"), &Line3D::get_use_global_space);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_global_space"), "set_use_global_space", "get_use_global_space");
}

Line3D::Line3D() {
	// Initialize any variables here.
	m_mesh.instantiate();
	set_base(m_mesh->get_rid());
}

Line3D::~Line3D() {
	// Add your cleanup here.
}

#pragma region m_mesh

Ref<LineMesh> Line3D::get_mesh() const {
	return m_mesh;
}

#pragma endregion

#pragma region m_points

void Line3D::add_point(const Vector3 &p_position, int64_t p_index) {
	m_mesh->add_point(p_position, p_index);
	m_is_dirty = true;
}

void Line3D::clear_points() {
	m_mesh->clear_points();
	m_is_dirty = true;
}

Vector3 Line3D::get_point_position(int64_t p_index) const {
	return m_mesh->get_point_position(p_index);
}

PackedVector3Array Line3D::get_points() const {
	return m_mesh->get_points();
}

void Line3D::remove_point(int64_t p_index) {
	m_mesh->remove_point(p_index);
	m_is_dirty = true;
}

void Line3D::set_point_position(int64_t p_index, const Vector3 &p_position) {
	m_mesh->set_point_position(p_index, p_position);
	m_is_dirty = true;
}

void Line3D::set_points(const PackedVector3Array &p_points) {
	m_mesh->set_points(p_points);
	m_is_dirty = true;
}

#pragma endregion

#pragma region m_simplify

bool Line3D::get_simplify() const {
	return m_mesh->get_simplify();
}

void Line3D::set_simplify(bool p_simplify) {
	m_mesh->set_simplify(p_simplify);
	m_is_dirty = true;
}

#pragma endregion

#pragma region m_tolerance

double Line3D::get_tolerance() const {
	return m_mesh->get_tolerance();
}

void Line3D::set_tolerance(double p_tolerance) {
	m_mesh->set_tolerance(p_tolerance);
	m_is_dirty = true;
}

#pragma endregion

#pragma region m_closed

bool Line3D::get_closed() const {
	return m_mesh->get_closed();
}

void Line3D::set_closed(bool p_closed) {
	m_mesh->set_closed(p_closed);
	m_is_dirty = true;
}

#pragma endregion

#pragma region m_width

double Line3D::get_width() const {
	return m_mesh->get_width();
}

void Line3D::set_width(double p_width) {
	m_mesh->set_width(p_width);
	m_is_dirty = true;
}

#pragma endregion

#pragma region m_width_curve

Ref<Curve> Line3D::get_width_curve() const {
	return m_mesh->get_width_curve();
}

void Line3D::set_width_curve(const Ref<Curve> &p_width_curve) {
	m_mesh->set_width_curve(p_width_curve);
	m_is_dirty = true;
}

#pragma endregion

#pragma region m_color

Color Line3D::get_color() const {
	return m_mesh->get_color();
}

void Line3D::set_color(const Color &p_color) {
	m_mesh->set_color(p_color);
	m_is_dirty = true;
}

#pragma endregion

#pragma region m_gradient

Ref<Gradient> Line3D::get_gradient() const {
	return m_mesh->get_gradient();
}

void Line3D::set_gradient(const Ref<Gradient> &p_gradient) {
	m_mesh->set_gradient(p_gradient);
	m_is_dirty = true;
}

#pragma endregion

#pragma region m_alignment

Line3D::LineAlignment Line3D::get_alignment() const {
	return m_alignment;
}

void Line3D::set_alignment(Line3D::LineAlignment p_alignment) {
	m_alignment = p_alignment;
	switch(m_alignment) {
  	case ALIGN_TO_VIEW:
  	case FACE_TOWARD_POSITION:
    	m_mesh->set_alignment(LineMesh::LineAlignment::FACE_TOWARD_POSITION);
    	break;
  	case ALIGN_TO_NORMAL:
    	m_mesh->set_alignment(LineMesh::LineAlignment::ALIGN_TO_NORMAL);
	}
	m_is_dirty = true;
}

#pragma endregion

#pragma region m_normal

Vector3 Line3D::get_normal() const {
	return m_mesh->get_normal();
}
void Line3D::set_normal(const Vector3 &p_normal) {
	m_mesh->set_normal(p_normal);
	m_is_dirty = true;
}

#pragma endregion

#pragma region m_use_global_space

bool Line3D::get_use_global_space() const {
	return m_mesh->get_use_transform();
}

void Line3D::set_use_global_space(bool p_use_global_space) {
	m_mesh->set_use_transform(p_use_global_space);
	m_is_dirty = true;
}

#pragma endregion

#pragma region m_transform

Transform3D Line3D::get_mesh_transform() const {
	return m_mesh->get_transform();
}

void Line3D::set_mesh_transform(const Transform3D &p_transform) {
	m_mesh->set_transform(p_transform);
	m_is_dirty = true;
}

#pragma endregion

void Line3D::_notification(int p_what) {
	if(p_what == NOTIFICATION_PROCESS) {
		// Update transform
		bool use_global_space = get_use_global_space();
		if(use_global_space) {
			Transform3D global_transform = get_global_transform();
			if(global_transform != get_mesh_transform()) {
				set_mesh_transform(global_transform);
			}
		}

		// Update view alignment.
		if(m_alignment == ALIGN_TO_VIEW) {
			Camera3D *camera = get_viewport()->get_camera_3d();
			if(camera != nullptr) {
				Vector3 camera_position = use_global_space ? camera->get_global_position() : to_local(camera->get_global_position());
				if(!camera_position.is_equal_approx(get_normal())) {
					set_normal(camera_position);
				}
			}
		}

		// Redraw mesh.
		if(m_is_dirty) {
			m_mesh->redraw();
			m_is_dirty = false;
		}
	}
}
