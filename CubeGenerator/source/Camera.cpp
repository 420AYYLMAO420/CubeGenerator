#include "Camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up, const float& speed)
	:View(glm::mat4(0.f)), Position(position), Direction(direction), Up(up), Speed(speed)
{}

Camera::~Camera() {}

void Camera::Move(CameraDirection direction)
{
	
	if (direction == CameraDirection::IN) //zoom in
		Position += Speed * Direction; 
	if (direction == CameraDirection::OUT) //zoom out
		Position -= Speed * Direction; 
	if (direction == CameraDirection::LEFT)//move left
		Position -= glm::normalize(glm::cross(Direction, Up)) * Speed;
	if (direction == CameraDirection::RIGHT) //move right
		Position += glm::normalize(glm::cross(Direction, Up)) * Speed;
	if (direction == CameraDirection::UP) //move up
		Position += Up * Speed;
	if (direction == CameraDirection::DOWN) //move down
		Position -= Up * Speed;

	//create a look-at matrix using the new value of Position
	View = glm::lookAt(Position, Position + Direction, Up);

	
}
