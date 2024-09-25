#define DIRECTINPUT_VERSION 0x0800
#include "GraphicDevice.h"
#include "GameObject.h"
#include "GameState.h"
#include "GameCharacter.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "AudioManager.h"
#include "GameStateManager.h"

class Game : public GameState {
public:
    Game();
    ~Game();

    void Enter() override;  // Called when the loading screen is entered
    void Exit() override;   // Called when the loading screen is exited
    void Update() override; // Update the loading state logic
    void Render() override; // Render the loading screen

	void update();
    void updateAnimation();
    bool isOnLadder();
    void Logic();
    void updateBoundingBox();
    bool checkCollision(D3DXVECTOR3 obj1, D3DXVECTOR3 obj2, float range);
    bool checkCollisionWithPlatform(D3DXVECTOR3 applePos);
    void randomizeApplePositions();
    void updateGorkAnimation(float deltaTime1);
    void updateMilitiaAnimation(float deltaTime);
    void render(HRESULT hr);
	void cleanup();

private:
    InputManager& inputManager = InputManager::getInstance();
    LPD3DXSPRITE sprite;
    LPD3DXFONT font;
    LPD3DXLINE line;
    LPDIRECT3DTEXTURE9 backgroundTexture;
    AudioManager* audioManager;
    LPDIRECT3DDEVICE9 d3dDevice =nullptr;
    D3DXVECTOR3 obj1;
    D3DXVECTOR3 obj2;

    float clamp(float value, float min, float max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    float range;
    float countdownTime = 60.0f;
    bool HitSide = false;
    bool HitTop = false;

    struct Animation {
        int militia_startFrame;
        int militia_endFrame;
    };

    Animation militia_walkLeft = { 4,7 };
    Animation militia_walkRight = { 8,11 };
    Animation militia_idle = { 0,0 };

    enum MovementStateMilitia { MILITIA_IDLE, MILITIA_WALK_LEFT, MILITIA_WALK_RIGHT };
    MovementStateMilitia currentState = MILITIA_IDLE;
    MovementStateMilitia previousState = MILITIA_IDLE;

    struct gorkanimmation {
        int gork_startFrame;
        int gork_endFrame;
    };
    gorkanimmation gork_idle = { 0, 3 };
    gorkanimmation gork_jump = { 4, 7 };
    gorkanimmation gork_walkRight = { 8, 11 };
    gorkanimmation gork_walkLeft = { 12, 15 };

    enum MovementStateGork { GORK_IDLE, GORK_WALK_LEFT, GORK_WALK_RIGHT, GORK_JUMP };
    MovementStateGork gorkCurrentState = GORK_IDLE;
    MovementStateGork gorkPreviousState = GORK_IDLE;

    float frameTime1 = 0.1f;       
    float frameTime2 = 0.05f;
    float frameTime = 0.1f;
    float frameTimer = 0.0f;
    const float gravity = 1000.0f;
    bool gorkOnPlatform = false;
    bool militiaOnPlatform = false;

    float gorkMoveSpeed = 300.0f;
    bool gorkIsJumping = false;
    float gorkJumpVelocity = 0.0f;
    const float gorkjumpForce = 800.0f;

    float militiamoveSpeed = 300.0f;
    bool isJumping = false;
    float jumpVelocity = 0.0f;
    const float jumpForce = 600.0f;

    float deltaTime;

    int min = 100;
    int max = 100;

    //Game Character
    LPDIRECT3DTEXTURE9 militiaTexture;
    LPDIRECT3DTEXTURE9 gorkTexture;
    LPD3DXFONT militiafont;
    LPD3DXFONT gorkfont;
    GraphicDevice& device = GraphicDevice::getInstance();
    WindowManager& windowManager = WindowManager::getWindowManager();
    int windowScreenWidth = windowManager.getWidth();
    int windowScreenHeight = windowManager.getHeight();

    float gorkPosX = static_cast<float>(windowScreenWidth / 2 - gorkWidth / 2);
    float gorkPosY = static_cast<float>(windowScreenHeight / 2 - gorkHeight / 2);

    float militiaPosX = static_cast<float>(windowScreenWidth / 2 - militiaWidth / 2);
    float militiaPosY = static_cast<float>(windowScreenHeight / 2 - militiaHeight / 2);

    int gorksheetWidth = 128;
    int gorksheetHeight = 128;
    int gorkColumn = 4;
    int gorkRow = 4;
    const int gorkWidth = gorksheetWidth / gorkColumn;
    const int gorkHeight = gorksheetHeight / gorkRow;
    int gorkFrames = 0;
    int maxgorkFrame = 16;
    int gorkcRow = gorkFrames / gorkColumn;
    int gorkcCol = gorkFrames % gorkColumn;

    int militiasheetWidth = 128;
    int militiasheetHeight = 255;
    int militiaColumn = 4;
    int militiaRow = 4;
    const int militiaWidth = militiasheetWidth / militiaColumn;
    const int militiaHeight = militiasheetHeight / militiaRow;
    int militiaFrames = 0;
    int maxmilitiaFrame = 16;
    int militiacRow = militiaFrames / militiaColumn;
    int militiacCol = militiaFrames % militiaColumn;

    //Game Object
    LPDIRECT3DTEXTURE9 platformTexture = nullptr;
    RECT platformBoundingBoxes[4];
    D3DXVECTOR3 platformPositions[4];

    LPDIRECT3DTEXTURE9 ladderTexture = nullptr;
    RECT ladderBoundingBox;
    RECT ladderBoundingBoxRight;

    LPDIRECT3DTEXTURE9 appleTexture = nullptr;
    D3DXVECTOR3 applePositions[3];
    D3DXVECTOR3 applePos;
    bool applesCollected[3] = { false, false, false };  // Tracks whether each apple has been collected
    int collectedApples = 0;  // Number of apples collected by the player
};
