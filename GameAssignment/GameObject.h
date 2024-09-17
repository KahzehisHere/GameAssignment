#pragma once
#include <d3dx9.h>

class GameObject {
protected:
    D3DXVECTOR3 position;           // Object position in the world
    LPDIRECT3DTEXTURE9 texture;     // Object texture
    int width, height;              // Object dimensions
    RECT boundingBox;               // Bounding box for collision detection

public:
    GameObject(LPDIRECT3DTEXTURE9 tex, int w, int h, D3DXVECTOR3 pos);
    virtual ~GameObject();

    // Pure virtual methods for derived classes
    virtual void Update(float deltaTime) = 0;
    virtual void Render(LPD3DXSPRITE sprite) = 0;

    // Getters and Setters
    D3DXVECTOR3 GetPosition() const;
    void SetPosition(float x, float y);
    int GetWidth() const;
    int GetHeight() const;
    RECT GetBoundingBox() const;

protected:
    void updateBoundingBox();  // Helper function to update bounding box
    bool checkCollision(const GameObject* other) const;  // Collision detection
};
