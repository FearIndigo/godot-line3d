class_name Line3DDemo

extends Line3D

@export_range(0.01, 10) var speed: float = 1.0
var time: float = 0.0

func _process(delta: float) -> void:
	var point = get_point_position(1)
	point.x = sin(time)
	set_point_position(1, point)
	time += delta * speed
