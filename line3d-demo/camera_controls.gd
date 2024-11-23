class_name CameraControls

extends Camera3D

@export var move_speed: float = 5.0;
@export var boost_percent: float = 2.0;
@export var look_sensitivity: float = 0.005;
@export var look_smoothing: float = 0.2;
@export var max_look_angles: Vector2 = Vector2(-80, 80);
var look_rot: Vector3

func _ready() -> void:
	look_rot = rotation

func _input(event) -> void:
	if event is InputEventMouseMotion and Input.is_mouse_button_pressed(MOUSE_BUTTON_RIGHT):
		look_rot.y -= event.relative.x * look_sensitivity
		look_rot.x -= event.relative.y * look_sensitivity
		look_rot.x = clampf(look_rot.x, max_look_angles.x, max_look_angles.y)

func _process(delta: float) -> void:
	# Rotation
	rotation = rotation.slerp(look_rot, look_smoothing)
	
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
	
	# Speed
	var speed: float = move_speed
	if(Input.is_key_pressed(KEY_SHIFT)):
		speed *= boost_percent
	
	translate_object_local(speed * delta * move_dir)
