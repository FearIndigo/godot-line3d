#include "line3d.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Line3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_mesh"), &Line3D::get_mesh);

	ClassDB::bind_method(D_METHOD("add_point", "position", "index"), &Line3D::add_point, DEFVAL(-1));
	ClassDB::bind_method(D_METHOD("clear_points"), &Line3D::clear_points);
	ClassDB::bind_method(D_METHOD("get_point_position", "index"), &Line3D::get_point_position);
	ClassDB::bind_method(D_METHOD("get_points"), &Line3D::get_points);
	ClassDB::bind_method(D_METHOD("remove_point", "index"), &Line3D::remove_point);
	ClassDB::bind_method(D_METHOD("set_point_position", "index", "position"), &Line3D::set_point_position);
	ClassDB::bind_method(D_METHOD("set_points", "points"), &Line3D::set_points);
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_VECTOR3_ARRAY, "points"), "set_points", "get_points");

	ClassDB::bind_method(D_METHOD("set_closed", "closed"), &Line3D::set_closed);
	ClassDB::bind_method(D_METHOD("get_closed"), &Line3D::get_closed);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "closed"), "set_closed", "get_closed");

	ClassDB::bind_method(D_METHOD("set_width", "width"), &Line3D::set_width);
	ClassDB::bind_method(D_METHOD("get_width"), &Line3D::get_width);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "width", PROPERTY_HINT_RANGE, "0,10,,or_greater"), "set_width", "get_width");
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

Ref<Line3DMesh> Line3D::get_mesh() const {
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

void Line3D::_notification(int p_what) {
	if(p_what == NOTIFICATION_PROCESS) {
		if(!m_is_dirty) return;
		m_mesh->redraw();
		m_is_dirty = false;
	}
}