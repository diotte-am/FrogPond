#include "Transform.hpp"

// By default, all transform matrices
// are also identity matrices
Transform::Transform(){
    LoadIdentity();
}

Transform::~Transform(){

}

// Resets the model transform as the identity matrix.
void Transform::LoadIdentity(){
    m_modelTransformMatrix = glm::mat4(1.0f);
}

void Transform::Translate(float x, float y, float z){
        m_modelTransformMatrix = glm::translate(m_modelTransformMatrix,glm::vec3(x,y,z));                            
}
void Transform::Translate(){
    m_modelTransformMatrix = glm::translate(m_modelTransformMatrix, m_pos);
}
void Transform::setPosition(float x, float y, float z){
    m_pos.x = x;
    m_pos.y = y;
    m_pos.z = z;
};

void Transform::updatePosition(float dx, float dy, float dz){
    m_pos.x += dx;
    m_pos.y += dy;
    m_pos.z += dz;
};

void Transform::Rotate(float radians, float x, float y, float z){
    m_modelTransformMatrix = glm::rotate(m_modelTransformMatrix, radians,glm::vec3(x,y,z));        
}
void Transform::Rotate(){
    m_modelTransformMatrix = glm::rotate(m_modelTransformMatrix, m_radians,m_rotAxis);        
}
void Transform::setRotation(float radians, float x, float y, float z){
    m_radians = radians;
    m_rotAxis.x = x;
    m_rotAxis.y = y;
    m_rotAxis.z = z;
}

void Transform::setRotationIncrement(float increment){
    m_angle_increment = increment;
}

void Transform::Scale(float x, float y, float z){
    m_modelTransformMatrix = glm::scale(m_modelTransformMatrix,glm::vec3(x,y,z));        
}
void Transform::Scale(){
    m_modelTransformMatrix = glm::scale(m_modelTransformMatrix,m_scale);        
}
void Transform::setScale(float x, float y, float z){
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;

}

void Transform::updateLocal(){
    Translate();
    Scale();
    Rotate();
}

// Returns the actual transform matrix
// Useful for sending 
GLfloat* Transform::GetTransformMatrix(){
    return &m_modelTransformMatrix[0][0];
}


// Get the raw internal matrix from the class
glm::mat4 Transform::GetInternalMatrix() const{
    return m_modelTransformMatrix;
}

void Transform::ApplyTransform(Transform t){
    m_modelTransformMatrix = t.GetInternalMatrix();
}


// Perform a matrix multiplication with our Transform
Transform& Transform::operator*=(const Transform& t) {
    m_modelTransformMatrix =  m_modelTransformMatrix * t.GetInternalMatrix();
    return *this;
}

// Perform a matrix addition with our Transform
Transform& Transform::operator+=(const Transform& t) {
    m_modelTransformMatrix =  m_modelTransformMatrix + t.GetInternalMatrix();
    return *this;
}

// Matrix assignment
Transform& Transform::operator=(const Transform& t) {
    m_modelTransformMatrix =  t.GetInternalMatrix();
    return *this;
}

// Perform a matrix multiplication with our Transform
//       x * y should return a copy, rather than a reference
//       need to be very careful when operator overloading.
//       See operator*= for an example of returning the reference
//       and avoiding the copy.
// This code probably needs optimized (lots of new objects on the stack!)
Transform operator*(const Transform& lhs, const Transform& rhs){
    Transform result;

    result.m_modelTransformMatrix = lhs.GetInternalMatrix() * rhs.GetInternalMatrix();

    return result;
}

// Transform Addition
Transform operator+(const Transform& lhs, const Transform& rhs){
    Transform result;

    result.m_modelTransformMatrix = lhs.GetInternalMatrix() + rhs.GetInternalMatrix();

    return result;
}
