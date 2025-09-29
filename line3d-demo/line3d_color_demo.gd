class_name Line3DColorDemo

extends Line3D

@export var speed: float = 0.5;
@export var color_1: Color = Color.GREEN
@export var color_2: Color = Color.RED
var time: float = 0.0

func _process(delta: float) -> void:
	# Incremenet time
	time += delta * speed
	# Update color
	color = color_1.lerp(color_2, abs(1.0 - (fmod(time, 2.0))))
