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

void Line3DMesh::set_points(const PackedVector3Array &p_points) {
	m_points = p_points;
}

PackedVector3Array Line3DMesh::get_points() const {
	return m_points;
}

void Line3DMesh::redraw() {
	// Redraw mesh here.
}