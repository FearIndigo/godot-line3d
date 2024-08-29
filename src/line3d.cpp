#include "line3d.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Line3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_points", "p_points"), &Line3D::set_points);
	ClassDB::bind_method(D_METHOD("get_points"), &Line3D::get_points);
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_VECTOR3_ARRAY, "points"), "set_points", "get_points");
}

Line3D::Line3D() {
	// Initialize any variables here.
	m_mesh.instantiate();
	set_base(m_mesh->get_rid());
}

Line3D::~Line3D() {
	// Add your cleanup here.
}

void Line3D::add_point(const Vector3 &p_position, int64_t p_index = -1) {
	m_mesh->add_point(p_position, p_index);
	_is_dirty = true;
}

void Line3D::clear_points() {
	m_mesh->clear_points();
	_is_dirty = true;
}

Vector3 Line3D::get_point_position(int64_t p_index) const {
	return m_mesh->get_point_position(p_index);
}

PackedVector3Array Line3D::get_points() const {
	return m_mesh->get_points();
}

void Line3D::remove_point(int64_t p_index) {
	m_mesh->remove_point(p_index);
	_is_dirty = true;
}

void Line3D::set_point_position(int64_t p_index, const Vector3 &p_position) {
	m_mesh->set_point_position(p_index, p_position);
	_is_dirty = true;
}

void Line3D::set_points(const PackedVector3Array &p_points) {
	m_mesh->set_points(p_points);
	_is_dirty = true;
}

void Line3D::_process(double delta) {
  if(!_is_dirty) return;
	m_mesh->redraw();
	_is_dirty = false;
}