class_name LineMeshDemo

extends MeshInstance3D

@export_range(0.01, 10) var speed: float = 1.0
var time: float = 0.0

func _init() -> void:
	mesh = LineMesh.new()
	mesh.points = [Vector3(0,0,0), Vector3(0,1,0)]

func _process(delta: float) -> void:
	var point = mesh.get_point_position(1)
	point.x = sin(time)
	mesh.set_point_position(1, point)
	time += delta * speed
	# Call redraw() to apply changes to the LineMesh.
	mesh.redraw()
