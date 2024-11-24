#ifndef TRAIL3D_H
#define TRAIL3D_H

#include "line3d.h"

namespace godot {

class Trail3D : public Line3D {
	GDCLASS(Trail3D, Line3D)

public:

private:
	double m_lifetime = 1.0;
	double m_min_vertex_distance = 0.1;
	bool m_emmitting = true;

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	Trail3D();
	~Trail3D();

	void _process(double delta) override {};

	double get_lifetime() const;
	void set_lifetime(double p_lifetime);

	double get_min_vertex_distance() const;
	void set_min_vertex_distance(double p_min_vertex_distance);

	bool get_emitting() const;
	void set_emitting(bool p_emitting);
};

} // namespace godot

#endif // TRAIL3D_H
