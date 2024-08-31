#include "line3d_mesh.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Line3DMesh::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add_point", "position", "index"), &Line3DMesh::add_point, DEFVAL(-1));
	ClassDB::bind_method(D_METHOD("clear_points"), &Line3DMesh::clear_points);
	ClassDB::bind_method(D_METHOD("get_point_position", "index"), &Line3DMesh::get_point_position);
	ClassDB::bind_method(D_METHOD("get_points"), &Line3DMesh::get_points);
	ClassDB::bind_method(D_METHOD("remove_point", "index"), &Line3DMesh::remove_point);
	ClassDB::bind_method(D_METHOD("set_point_position", "index", "position"), &Line3DMesh::set_point_position);
	ClassDB::bind_method(D_METHOD("set_points", "points"), &Line3DMesh::set_points);
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_VECTOR3_ARRAY, "points"), "set_points", "get_points");

	ClassDB::bind_method(D_METHOD("set_closed", "closed"), &Line3DMesh::set_closed);
	ClassDB::bind_method(D_METHOD("get_closed"), &Line3DMesh::get_closed);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "closed"), "set_closed", "get_closed");

	ClassDB::bind_method(D_METHOD("redraw"), &Line3DMesh::redraw);
}

Line3DMesh::Line3DMesh() {
	// Initialize any variables here.
}

Line3DMesh::~Line3DMesh() {
	// Add your cleanup here.
}

#pragma region m_points

void Line3DMesh::add_point(const Vector3 &p_position, int64_t p_index) {
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

#pragma endregion

#pragma region m_closed

bool Line3DMesh::get_closed() const {
	return m_closed;
}

void Line3DMesh::set_closed(bool p_closed) {
	m_closed = p_closed;
}

#pragma endregion

#pragma region helper_methods

double Line3DMesh::_get_line_length() const {
	double length = 0.0;
	int64_t size = m_points.size();
	for (int i = 0; i < _get_num_segments(); i++) {
		length += m_points[i].distance_to(m_points[(i + 1) % size]);
	}
	return length;
}

int64_t Line3DMesh::_get_num_segments() const {
	int64_t size = m_points.size();
	return (m_closed && size > 2) ? size : size - 1;
}

#pragma endregion

void Line3DMesh::redraw() {
	// Clear mesh.
	clear_surfaces();

	// Return if no segments to draw.
	int64_t num_segments = _get_num_segments();
	if(num_segments <= 0) return;

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
