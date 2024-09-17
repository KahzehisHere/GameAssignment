#include "GameObject.h"

// Constructor
GameObject::GameObject(LPDIRECT3DTEXTURE9 tex, int w, int h, D3DXVECTOR3 pos)
    : texture(tex), width(w), height(h), position(pos) {
    // Initialize bounding box based on position and size
    updateBoundingBox();
}

// Destructor
GameObject::~GameObject() {
    // If texture management is handled elsewhere (e.g., ResourceManager), don't delete it here
}

// Getters
D3DXVECTOR3 GameObject::GetPosition() const {
    return position;
}

int GameObject::GetWidth() const {
    return width;
}

int GameObject::GetHeight() const {
    return height;
}

RECT GameObject::GetBoundingBox() const {
    return boundingBox;
}

// Setters
void GameObject::SetPosition(float x, float y) {
    position.x = x;
    position.y = y;
    updateBoundingBox();
}

// Bounding box update
void GameObject::updateBoundingBox() {
    boundingBox.left = (LONG)position.x;
    boundingBox.top = (LONG)position.y;
    boundingBox.right = boundingBox.left + width;
    boundingBox.bottom = boundingBox.top + height;
}

// Collision detection (Axis-Aligned Bounding Box - AABB)
bool GameObject::checkCollision(const GameObject* other) const {
    RECT otherBoundingBox = other->GetBoundingBox();
    return (boundingBox.left < otherBoundingBox.right &&
        boundingBox.right > otherBoundingBox.left &&
        boundingBox.top < otherBoundingBox.bottom &&
        boundingBox.bottom > otherBoundingBox.top);
}
