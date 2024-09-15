#pragma once
#include <d3dx9.h>

class GameObject {
protected:
    D3DXVECTOR3 position;
    LPDIRECT3DTEXTURE9 texture;
    int width;
    int height;

public:
    GameObject(LPDIRECT3DTEXTURE9 tex, int w, int h, D3DXVECTOR3 pos)
        : texture(tex), width(w), height(h), position(pos) {}

    virtual void Update(float deltaTime) = 0;  // Pure virtual method for updating logic
    virtual void Render(LPD3DXSPRITE sprite) = 0;  // Pure virtual method for rendering logic

    D3DXVECTOR3 GetPosition() const { return position; }
    void SetPosition(float x, float y) { position = D3DXVECTOR3(x, y, 0); }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
};
