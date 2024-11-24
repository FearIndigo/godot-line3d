#include "trail3d.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Trail3D::_bind_methods() {
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

Trail3D::Trail3D() {
	// Initialize any variables here.
}

Trail3D::~Trail3D() {
	// Add your cleanup here.
}

#pragma region m_lifetime

double Trail3D::get_lifetime() const {
	return m_lifetime;
}

void Trail3D::set_lifetime(double p_lifetime) {
	m_lifetime = p_lifetime;
	_is_dirty = true;
}

#pragma endregion

#pragma region m_min_vertex_distance

double Trail3D::get_min_vertex_distance() const {
	return m_min_vertex_distance;
}

void Trail3D::set_min_vertex_distance(double p_min_vertex_distance) {
	m_min_vertex_distance = p_min_vertex_distance;
	_is_dirty = true;
}

#pragma endregion

#pragma region m_emitting

bool Trail3D::get_emitting() const {
	return m_emmitting;
}

void Trail3D::set_emitting(bool p_emitting) {
	m_emmitting = p_emitting;
	_is_dirty = true;
}

#pragma endregion

void Trail3D::_notification(int p_what) {
	if(p_what == NOTIFICATION_PROCESS) {
	}
}
