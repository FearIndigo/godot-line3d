#include "line3d_mesh.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Line3DMesh::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_points", "p_points"), &Line3DMesh::set_points);
	ClassDB::bind_method(D_METHOD("get_points"), &Line3DMesh::get_points);
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_VECTOR3_ARRAY, "points"), "set_points", "get_points");
}

Line3DMesh::Line3DMesh() {
	// Initialize any variables here.
}

Line3DMesh::~Line3DMesh() {
	// Add your cleanup here.
}

void Line3DMesh::add_point(const Vector3 &p_position, int64_t p_index = -1) {
	if(p_index == -1) p_index = m_points.size();
	m_points.insert(p_index, p_position);
}

void Line3DMesh::clear_points() {
	m_points.clear();
}

Vector3 Line3DMesh::get_point_position(int64_t p_index) const {
	return m_points[p_index];
}

PackedVector3Array Line3DMesh::get_points() const {
	return m_points;
}

void Line3DMesh::remove_point(int64_t p_index) {
	m_points.remove_at(p_index);
}

void Line3DMesh::set_point_position(int64_t p_index, const Vector3 &p_position) {
	m_points.set(p_index, p_position);
}

void Line3DMesh::set_points(const PackedVector3Array &p_points) {
	m_points = p_points;
}

void Line3DMesh::redraw() {
	// Clear mesh.
	clear_surfaces();

	if(m_points.is_empty()) return;

	// Begin draw.
	surface_begin(PRIMITIVE_TRIANGLES);

	// Prepare attributes for add_vertex.
	surface_set_normal(Vector3(0, 0, 1));
	surface_set_uv(Vector2(0, 0));
	// Call last for each vertex, adds the above attributes.
	surface_add_vertex(Vector3(-1, -1, 0));

	surface_set_normal(Vector3(0, 0, 1));
	surface_set_uv(Vector2(0, 1));
	surface_add_vertex(Vector3(-1, 1, 0));

	surface_set_normal(Vector3(0, 0, 1));
	surface_set_uv(Vector2(1, 1));
	surface_add_vertex(Vector3(1, 1, 0));

	// End drawing.
	surface_end();
}