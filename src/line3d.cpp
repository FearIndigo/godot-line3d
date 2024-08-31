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

#pragma endregion

#pragma region m_closed

bool Line3D::get_closed() const {
	return m_mesh->get_closed();
}

void Line3D::set_closed(bool p_closed) {
	m_mesh->set_closed(p_closed);
	_is_dirty = true;
}

#pragma endregion

void Line3D::_process(double delta) {
  if(!_is_dirty) return;
	m_mesh->redraw();
	_is_dirty = false;
}