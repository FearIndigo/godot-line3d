#include "line_mesh.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void LineMesh::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add_point", "position", "index"), &LineMesh::add_point, DEFVAL(-1));
	ClassDB::bind_method(D_METHOD("clear_points"), &LineMesh::clear_points);
	ClassDB::bind_method(D_METHOD("get_point_position", "index"), &LineMesh::get_point_position);
	ClassDB::bind_method(D_METHOD("get_points"), &LineMesh::get_points);
	ClassDB::bind_method(D_METHOD("remove_point", "index"), &LineMesh::remove_point);
	ClassDB::bind_method(D_METHOD("set_point_position", "index", "position"), &LineMesh::set_point_position);
	ClassDB::bind_method(D_METHOD("set_points", "points"), &LineMesh::set_points);
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_VECTOR3_ARRAY, "points"), "set_points", "get_points");

	ClassDB::bind_method(D_METHOD("set_closed", "closed"), &LineMesh::set_closed);
	ClassDB::bind_method(D_METHOD("get_closed"), &LineMesh::get_closed);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "closed"), "set_closed", "get_closed");

	ClassDB::bind_method(D_METHOD("set_width", "width"), &LineMesh::set_width);
	ClassDB::bind_method(D_METHOD("get_width"), &LineMesh::get_width);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "width", PROPERTY_HINT_RANGE, "0,10,,or_greater"), "set_width", "get_width");

	ClassDB::bind_method(D_METHOD("set_width_curve", "curve"), &LineMesh::set_width_curve);
	ClassDB::bind_method(D_METHOD("get_width_curve"), &LineMesh::get_width_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "width_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_width_curve", "get_width_curve");

	ClassDB::bind_method(D_METHOD("redraw"), &LineMesh::redraw);
}

LineMesh::LineMesh() {
	// Initialize any variables here.
}

LineMesh::~LineMesh() {
	// Add your cleanup here.
}

#pragma region m_points

void LineMesh::add_point(const Vector3 &p_position, int64_t p_index) {
	if(p_index == -1) p_index = m_points.size();
	m_points.insert(p_index, p_position);
}

void LineMesh::clear_points() {
	m_points.clear();
}

Vector3 LineMesh::get_point_position(int64_t p_index) const {
	return m_points[p_index];
}

PackedVector3Array LineMesh::get_points() const {
	return m_points;
}

void LineMesh::remove_point(int64_t p_index) {
	m_points.remove_at(p_index);
}

void LineMesh::set_point_position(int64_t p_index, const Vector3 &p_position) {
	m_points.set(p_index, p_position);
}

void LineMesh::set_points(const PackedVector3Array &p_points) {
	m_points = p_points;
}

#pragma endregion

#pragma region m_closed

bool LineMesh::get_closed() const {
	return m_closed;
}

void LineMesh::set_closed(bool p_closed) {
	m_closed = p_closed;
}

#pragma endregion

#pragma region m_width

double LineMesh::get_width() const {
	return m_width;
}

void LineMesh::set_width(double p_width) {
	m_width = p_width;
}

#pragma endregion

#pragma region m_width_curve

Ref<Curve> LineMesh::get_width_curve() const {
	return m_width_curve;
}

void LineMesh::set_width_curve(const Ref<Curve> &p_width_curve) {
	m_width_curve = p_width_curve;
}

#pragma endregion

#pragma region helper_methods

double LineMesh::_get_line_length() const {
	double line_length = 0.0;
	int64_t num_points = m_points.size();
	for (int i = 0; i < _get_num_segments(); i++) {
		line_length += m_points[i].distance_to(m_points[(i + 1) % num_points]);
	}
	return line_length;
}

int64_t LineMesh::_get_num_segments() const {
	int64_t num_points = m_points.size();
	return (m_closed && num_points > 2) ? num_points : num_points - 1;
}

#pragma endregion

void LineMesh::redraw() {
	// Clear mesh.
	clear_surfaces();

	// Return if line has no width. If there is a width curve, assume it has some thickness.
	if(m_width <= 0.0 && m_width_curve.is_null()) return;

	// Return if no segments to draw.
	int64_t num_segments = _get_num_segments();
	if(num_segments <= 0) return;

	// Return if line has no length.
	double line_length = _get_line_length();
	if(line_length <= 0.0) return;

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
