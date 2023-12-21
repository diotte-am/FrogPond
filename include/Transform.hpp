
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glad/glad.h>
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>

// The purpose of this class is to store
// transformations of 3D entities (cameras, objects, etc.)
class Transform{
public:

    // Constructor for a new transform
    Transform();
    // Destructor for the transform
    ~Transform();

    // Resets matrix transformations to the identity matrix
    void LoadIdentity();

    // Perform a translation of an object
    void Translate(float x, float y, float z);
    // Perform a translation of an object
    void Translate();
    void setPosition(float x, float y, float z);
    void updatePosition(float dx, float dy, float dz);


    // Perform rotation about an axis
    void Rotate(float radians, float x, float y, float z);
    void Rotate();
    void setRotation(float radians, float x, float y, float z);
    void setRotationIncrement(float increment);

    // Perform rotation about an axis
    void Scale(float x, float y, float z);
    void Scale();
    void setScale(float x, float y, float z);

    void updateLocal();


    // Returns the transformation matrix
    GLfloat* GetTransformMatrix();
    // Apply Transform
    // Takes in a transform and sets internal
    // matrix.
    void ApplyTransform(Transform t);
    // Returns the transformation matrix
    glm::mat4 GetInternalMatrix() const;
    float getRadians(){
        return m_radians;};
    void incrementRadians(){m_radians += m_angle_increment;};

    glm::vec3 getRotationAxis(){ return m_rotAxis; };

    // Transform multiplication t1 *= t2 (t1 is multiplied and a new result stored)
	Transform& operator*=(const Transform& t);
	// Transform addition
	Transform& operator+=(const Transform& t);
	// Transform =
	Transform& operator=(const Transform& t);
    // Multiplication operator overload
    // Returns a new copy of the result of 
    // t3 = t1 * t2. (Returned value is stored in 't3' which is returned)
    friend Transform operator*(const Transform& lhs, const Transform& rhs);
    // Addition operator overload
    // Returns a new copy of the result of 
    // t3 = t1 + t2. (Returned value is stored in 't3' which is returned)
    friend Transform operator+(const Transform& lhs, const Transform& rhs);

    

private:
    // Stores the actual transformation matrix
    glm::mat4 m_modelTransformMatrix;

    std::string m_name;

    float m_angle_increment = 0;
    float m_radians = 0;
    float PI = 3.14159;
    glm::vec3 m_pos = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_scale = {1.0f, 1.0f, 1.0f};
    glm::vec3 m_rotAxis = {0.0f, 0.0f, 0.0f};

};


#endif
