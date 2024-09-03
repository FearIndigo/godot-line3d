class_name CameraControls

extends Camera3D

@export var move_speed: float = 5.0;
@export var look_speed: float = 0.5;
@export var max_look_angles: Vector2 = Vector2(-80, 80);
var look_dir: Vector3

func _input(event) -> void:
	look_dir = Vector3.ZERO
	if event is InputEventMouseMotion and Input.is_mouse_button_pressed(MOUSE_BUTTON_RIGHT):
		look_dir.y = -event.relative.x
		look_dir.x = -event.relative.y

func _process(delta: float) -> void:
	# Rotation
	var rot: Vector3 = rotation + look_speed * delta * look_dir
	rot.x = clampf(rot.x, max_look_angles.x, max_look_angles.y)
	rotation = rot
	look_dir = Vector3.ZERO
	
	# Translation
	var move_dir: Vector3
	if(Input.is_key_pressed(KEY_W)):
		move_dir.z -= 1
	if(Input.is_key_pressed(KEY_S)):
		move_dir.z += 1
	if(Input.is_key_pressed(KEY_A)):
		move_dir.x -= 1
	if(Input.is_key_pressed(KEY_D)):
		move_dir.x += 1
	translate_object_local(move_speed * delta * move_dir)
