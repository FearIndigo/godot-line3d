#ifndef TRAIL3D_H
#define TRAIL3D_H

#include "line3d.h"

namespace godot {

class Trail3D : public Line3D {
	GDCLASS(Trail3D, Line3D)

public:

private:

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	Trail3D();
	~Trail3D();

	void _process(double delta) override {};
};

} // namespace godot

#endif // TRAIL3D_H
