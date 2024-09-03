class_name Line3DDemo

extends Line3D

@export var speed: float = 2.0
@export var num_points: int = 20
@export var line_length: float = 10.0
@export var frequency: float = 5.0
var time: float = 0.0

func _init() -> void:
	clear_points()
	for i in range(num_points):
		add_point(Vector3(0, float(i) / num_points * line_length, 0))

func _process(delta: float) -> void:
	for i in range(points.size()):
		var point = get_point_position(i)
		point.x = sin(time + float(i) / num_points * frequency)
		set_point_position(i, point)
	
	time += delta * speed
