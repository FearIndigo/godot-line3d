#ifndef LINE3D_H
#define LINE3D_H

#include <godot_cpp/classes/geometry_instance3d.hpp>

namespace godot {

class Line3D : public GeometryInstance3D {
	GDCLASS(Line3D, GeometryInstance3D)

private:

protected:
	static void _bind_methods();

public:
	Line3D();
	~Line3D();

	void _process(double delta) override;
};

}

#endif // LINE3D_H