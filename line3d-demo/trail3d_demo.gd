class_name Trail3DDemo

extends Trail3D

@export var speed: float = 3.0
@export var size: float = 3.0
var position_offset: Vector3 = Vector3.ZERO
var time: float = 0.0

func _ready() -> void:
	# Set position offset to inital position
	position_offset = position

func _process(delta: float) -> void:
	# Increment time
	time += delta * speed
	# Update node position
	position = position_offset + Vector3(
		size * sqrt(2)*cos(time) * sin(time) / (1 + sin(time)*sin(time)),
		size * sqrt(2)*cos(time) / (1 + sin(time)*sin(time)),
		0)
