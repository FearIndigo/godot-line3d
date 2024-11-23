#include "line_mesh.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void LineMesh::_bind_methods() {
	BIND_ENUM_CONSTANT(FACE_TOWARD_POSITION);
	BIND_ENUM_CONSTANT(ALIGN_TO_NORMAL);

	ClassDB::bind_method(D_METHOD("add_point", "position", "index"), &LineMesh::add_point, DEFVAL(-1));
	ClassDB::bind_method(D_METHOD("clear_points"), &LineMesh::clear_points);
	ClassDB::bind_method(D_METHOD("get_point_position", "index"), &LineMesh::get_point_position);
	ClassDB::bind_method(D_METHOD("get_points"), &LineMesh::get_points);
	ClassDB::bind_method(D_METHOD("remove_point", "index"), &LineMesh::remove_point);
	ClassDB::bind_method(D_METHOD("set_point_position", "index", "position"), &LineMesh::set_point_position);
	ClassDB::bind_method(D_METHOD("set_points", "points"), &LineMesh::set_points);
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_VECTOR3_ARRAY, "points"), "set_points", "get_points");

	ClassDB::bind_method(D_METHOD("set_simplify", "simplify"), &LineMesh::set_simplify);
	ClassDB::bind_method(D_METHOD("get_simplify"), &LineMesh::get_simplify);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "simplify"), "set_simplify", "get_simplify");

	ClassDB::bind_method(D_METHOD("set_tolerance", "tolerance"), &LineMesh::set_tolerance);
	ClassDB::bind_method(D_METHOD("get_tolerance"), &LineMesh::get_tolerance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tolerance", PROPERTY_HINT_RANGE, "0,10,,or_greater"), "set_tolerance", "get_tolerance");

	ClassDB::bind_method(D_METHOD("set_closed", "closed"), &LineMesh::set_closed);
	ClassDB::bind_method(D_METHOD("get_closed"), &LineMesh::get_closed);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "closed"), "set_closed", "get_closed");

	ClassDB::bind_method(D_METHOD("set_width", "width"), &LineMesh::set_width);
	ClassDB::bind_method(D_METHOD("get_width"), &LineMesh::get_width);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "width", PROPERTY_HINT_RANGE, "0,10,,or_greater"), "set_width", "get_width");

	ClassDB::bind_method(D_METHOD("set_width_curve", "curve"), &LineMesh::set_width_curve);
	ClassDB::bind_method(D_METHOD("get_width_curve"), &LineMesh::get_width_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "width_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_width_curve", "get_width_curve");

	ClassDB::bind_method(D_METHOD("set_color", "color"), &LineMesh::set_color);
	ClassDB::bind_method(D_METHOD("get_color"), &LineMesh::get_color);
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");

	ClassDB::bind_method(D_METHOD("set_gradient", "gradient"), &LineMesh::set_gradient);
	ClassDB::bind_method(D_METHOD("get_gradient"), &LineMesh::get_gradient);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "gradient", PROPERTY_HINT_RESOURCE_TYPE, "Gradient"), "set_gradient", "get_gradient");

	ClassDB::bind_method(D_METHOD("set_alignment", "alignment"), &LineMesh::set_alignment);
	ClassDB::bind_method(D_METHOD("get_alignment"), &LineMesh::get_alignment);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "alignment", PROPERTY_HINT_ENUM, "Face Toward Position,Align To Normal"), "set_alignment", "get_alignment");

	ClassDB::bind_method(D_METHOD("set_normal", "normal"), &LineMesh::set_normal);
	ClassDB::bind_method(D_METHOD("get_normal"), &LineMesh::get_normal);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "normal"), "set_normal", "get_normal");

	ClassDB::bind_method(D_METHOD("set_use_transform", "use_transform"), &LineMesh::set_use_transform);
	ClassDB::bind_method(D_METHOD("get_use_transform"), &LineMesh::get_use_transform);

	ClassDB::bind_method(D_METHOD("set_transform", "transform"), &LineMesh::set_transform);
	ClassDB::bind_method(D_METHOD("get_transform"), &LineMesh::get_transform);

	ClassDB::bind_method(D_METHOD("redraw"), &LineMesh::redraw);
}

LineMesh::LineMesh() {
	// Initialize any variables here.
	redraw();
}

LineMesh::~LineMesh() {
	// Add your cleanup here.
}

#pragma region m_points

void LineMesh::add_point(const Vector3 &p_position, int64_t p_index) {
	if(p_index == -1) m_points.push_back(p_position);
	else m_points.insert(p_index, p_position);
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

#pragma region m_simplify

bool LineMesh::get_simplify() const {
	return m_simplify;
}

void LineMesh::set_simplify(bool p_simplify) {
	m_simplify = p_simplify;
}

#pragma endregion

#pragma region m_tolerance

double LineMesh::get_tolerance() const {
	return m_tolerance;
}

void LineMesh::set_tolerance(double p_tolerance) {
	m_tolerance = p_tolerance;
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

#pragma region m_color

Color LineMesh::get_color() const {
	return m_color;
}

void LineMesh::set_color(const Color &p_color) {
	m_color = p_color;
}

#pragma endregion

#pragma region m_gradient

Ref<Gradient> LineMesh::get_gradient() const {
	return m_gradient;
}

void LineMesh::set_gradient(const Ref<Gradient> &p_gradient) {
	m_gradient = p_gradient;
}

#pragma endregion

#pragma region m_alignment

LineMesh::LineAlignment LineMesh::get_alignment() const {
	return m_alignment;
}

void LineMesh::set_alignment(LineMesh::LineAlignment p_alignment) {
	m_alignment = p_alignment;
}

#pragma endregion

#pragma region m_normal

Vector3 LineMesh::get_normal() const {
	return m_normal;
}
void LineMesh::set_normal(const Vector3 &p_normal) {
	m_normal = p_normal;
}

#pragma endregion

#pragma region m_use_transform

bool LineMesh::get_use_transform() const {
	return m_use_transform;
}

void LineMesh::set_use_transform(bool p_use_transform) {
	m_use_transform = p_use_transform;
}

#pragma endregion

#pragma region m_transform

Transform3D LineMesh::get_transform() const {
	return m_transform;
}

void LineMesh::set_transform(const Transform3D &p_transform) {
	m_transform = p_transform;
	m_inverse_transform = m_transform.inverse();
}

#pragma endregion

#pragma region helper_methods

PackedVector3Array LineMesh::_douglas_peucker(const PackedVector3Array &p_points, double p_epsilon) const {
	return p_points;
}

Vector3 LineMesh::_get_position_alignment(const Vector3 &p_position) const {
	return m_alignment == ALIGN_TO_NORMAL ?
		_transform_direction(m_normal).normalized() :
		p_position.direction_to(_transform_position(m_normal));
}

PackedVector3Array LineMesh::_get_simplified_points() const {
	// Only perform simplification if tolerance is greater than 0.
	if (!m_simplify || m_tolerance <= 0) return m_points;
	return _douglas_peucker(m_points, m_tolerance);
}

Vector3 LineMesh::_transform_direction(const Vector3 &p_local_direction) const {
	return m_use_transform ?
		m_inverse_transform.basis.xform(p_local_direction) :
		p_local_direction;
}

Vector3 LineMesh::_transform_position(const Vector3 &p_local_position) const {
	return m_use_transform ?
		m_inverse_transform.xform(p_local_position) :
		p_local_position;
}

#pragma endregion

void LineMesh::redraw() {
	// Clear mesh.
	clear_surfaces();

	// Return if line has no width.
	if(m_width <= 0.0) return;

	// Get simplified points.
	PackedVector3Array points = _get_simplified_points();

	// Return if line doesn't have 2 or more points (3 or more if line is closed).
	int64_t num_points = points.size();
	if(num_points < 2 || (m_closed && num_points < 3)) return;

	// Begin draw.
	surface_begin(PRIMITIVE_TRIANGLE_STRIP);

	// Get number of segments
	int64_t num_segments = m_closed ? num_points : num_points - 1;

	// Draw segments
	for (int64_t i = 0; i < num_points; i++) {
		Vector3 p_current = _transform_position(points[i % num_points]);
		Vector3 p_next = m_closed || i < num_points - 1 ?
			_transform_position(points[(i + 1) % num_points]) :
			p_current;
		Vector3 p_prev = m_closed || i != 0 ?
			_transform_position(points[(num_points + i - 1) % num_points]) :
			p_current;

		Vector3 alignment = _get_position_alignment(p_current);

		Vector3 dir_in = p_prev.direction_to(p_current);
		Vector3 dir_in_tangent = dir_in.slide(alignment);
		Vector3 dir_out = p_current.direction_to(p_next);
		Vector3 dir_out_tangent = dir_out.slide(alignment);
		Vector3 dir_avg = dir_in + dir_out;
		Vector3 dir_avg_tangent = dir_in_tangent + dir_out_tangent;
		double tangent_angle = dir_in_tangent.angle_to(dir_out_tangent);

		Vector3 tangent = dir_avg_tangent.normalized();
		Vector3 bitangent = alignment.cross(tangent).normalized();
		Vector3 normal = dir_avg.cross(bitangent).normalized();

		bitangent *= m_width / 2.0 + m_width / 10.0 * (tangent_angle * tangent_angle);

		surface_set_normal(normal);
		surface_set_uv(Vector2(0, 1));
		surface_set_color(m_color);
		surface_add_vertex(p_current - bitangent);

		surface_set_normal(normal);
		surface_set_uv(Vector2(1, 1));
		surface_set_color(m_color);
		surface_add_vertex(p_current + bitangent);
	}

	// End drawing.
	surface_end();
}
