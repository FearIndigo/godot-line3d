class_name LineMeshDemo

extends MeshInstance3D

@export var speed: float = 2.0
@export var num_points: int = 20
@export var line_length: float = 10.0
@export var frequency: float = 5.0
var time: float = 0.0

func _init() -> void:
	mesh.clear_points()
	for i in range(num_points):
		mesh.add_point(Vector3(0, float(i) / num_points * line_length, 0))

func _process(delta: float) -> void:
	for i in range(mesh.points.size()):
		var point = mesh.get_point_position(i)
		point.x = sin(time + float(i) / num_points * frequency)
		mesh.set_point_position(i, point)
	
	time += delta * speed
	# Call redraw() to apply changes to the LineMesh.
	mesh.redraw()
