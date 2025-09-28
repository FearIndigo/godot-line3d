class_name CameraControls

extends Camera3D

@export var move_speed: float = 10.0;
@export var boost_percent: float = 2.0;
@export var look_sensitivity: float = 0.004;
@export var look_smoothing: float = 30.0;
@export var max_look_angles: Vector2 = Vector2(-90, 90);
var look_rot: Vector3
var target_rot: Quaternion

func _ready() -> void:
	look_rot = rotation
	target_rot = Quaternion.from_euler(look_rot)

func _input(event) -> void:
	if event is InputEventMouseMotion and Input.is_mouse_button_pressed(MOUSE_BUTTON_RIGHT):
		look_rot.y -= event.relative.x * look_sensitivity
		look_rot.x -= event.relative.y * look_sensitivity
		look_rot.x = clampf(look_rot.x, deg_to_rad(max_look_angles.x), deg_to_rad(max_look_angles.y))
		target_rot = Quaternion.from_euler(look_rot)

func _process(delta: float) -> void:
	# Rotation
	transform.basis = Basis(transform.basis.get_rotation_quaternion().slerp(target_rot, look_smoothing * delta))
	
	# Translation
	var move_dir: Vector3
	if(Input.is_key_pressed(KEY_Q)):
		move_dir.y += 1
	if(Input.is_key_pressed(KEY_E)):
		move_dir.y -= 1
	if(Input.is_key_pressed(KEY_W)):
		move_dir.z -= 1
	if(Input.is_key_pressed(KEY_S)):
		move_dir.z += 1
	if(Input.is_key_pressed(KEY_A)):
		move_dir.x -= 1
	if(Input.is_key_pressed(KEY_D)):
		move_dir.x += 1
	move_dir = move_dir.normalized()
	
	# Speed
	var speed: float = move_speed
	if(Input.is_key_pressed(KEY_SHIFT)):
		speed *= boost_percent
	
	translate_object_local(speed * delta * move_dir)
