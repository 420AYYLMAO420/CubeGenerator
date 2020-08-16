#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//enum used to move the camera in a direction
//each element's value is equal to a macro for a key in GLFW
//ex. GLFW_KEY_E = 69, value of OUT = 69
enum class CameraDirection : unsigned int {
	IN = 81, OUT = 69, LEFT = 65, RIGHT = 68, UP = 87, DOWN = 83
};

class Camera {
public:
	Camera(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up, const float& speed);
	~Camera();

	void Move(CameraDirection direction); //move the camera using the desired direction
	inline glm::mat4 GetView() const { return View; } //returns the look-at matrix 

	float Speed; //base speed of moving the camera
private:
	glm::mat4 View; //look-at matrix
	glm::vec3 Position; //position vector
	glm::vec3 Direction; //vector that points to where the camera is looking at
	glm::vec3 Up; //the vector pointing upwards from the camera

};