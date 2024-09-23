#include "Frametime.h"

void Frametime::init(int fps) {
    QueryPerformanceFrequency(&timerFreq);
    QueryPerformanceCounter(&timeNow);
    QueryPerformanceCounter(&timePrevious);

    requestedFPS = fps;
    intervalsPerFrame = static_cast<float>(timerFreq.QuadPart) / static_cast<float>(requestedFPS);  // Ensure accurate division
}

int Frametime::FramesToUpdate() {
    int framesToUpdate = 0;
    QueryPerformanceCounter(&timeNow);

    intervalsSinceLastUpdate = static_cast<float>(timeNow.QuadPart - timePrevious.QuadPart);
    framesToUpdate = static_cast<int>(intervalsSinceLastUpdate / intervalsPerFrame);

    if (framesToUpdate != 0) {
        QueryPerformanceCounter(&timePrevious);
    }
    return framesToUpdate;
}
