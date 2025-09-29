class_name LineMeshDemo

extends MeshInstance3D

@export var speed: float = 3.0
@export var num_points: int = 20
@export var line_length: float = 10.0
@export var frequency: float = 5.0
@export var magnitude: float = 0.5
var time: float = 0.0
var temp_points: PackedVector3Array

func _ready() -> void:
	# Initialise points array
	temp_points.resize(num_points);
	for i in range(num_points):
		temp_points[i] = Vector3(0, float(i) / (num_points - 1) * line_length, 0)
	mesh.set_points(temp_points);

func _process(delta: float) -> void:
	# Increment time
	time += delta * speed
	# Update point positions
	for i in range(num_points):
		var t: float = float(i) / (num_points - 1)
		temp_points[i].x = sin(time + t * frequency) * magnitude
	mesh.set_points(temp_points);
	# Redraw the line with updated values.
	mesh.redraw()
