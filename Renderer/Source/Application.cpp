#include "Application.h"

using namespace Renderer;

Application::Application(const char* pTitle, const unsigned int& pWidth, const unsigned int& pHeight) : 
    mWindow(pTitle, pWidth, pHeight),
    mRenderer(mWindow),
    mCamera(pWidth, pHeight, Maths::FMatrix4::createPerspective(-45, float(pWidth) / float(pHeight), 0.01f, 500.f), Maths::FVector3(0, 2, 4)),
    mScene(mRenderer, mCamera)
{
    mWindow.setWindowUserPointer(this);
    mRenderer.init();
    mScene.init();
}

void Application::keyCallback(int pKey, int pScancode, int pAction, int pMods)
{
    if (mWindow.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        mWindow.close();
}

void Application::processInput(const float& pDeltaTime)
{
    mCamera.mIsRun = mWindow.getKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

    if (mWindow.getKey(GLFW_KEY_A) == GLFW_PRESS)
        mCamera.processKeyboard(Renderer::CameraMovement::LEFT, pDeltaTime);
    else if (mWindow.getKey(GLFW_KEY_D) == GLFW_PRESS)
        mCamera.processKeyboard(Renderer::CameraMovement::RIGHT, pDeltaTime);

    if (mWindow.getKey(GLFW_KEY_W) == GLFW_PRESS)
        mCamera.processKeyboard(Renderer::CameraMovement::FORWARD, pDeltaTime);
    else if (mWindow.getKey(GLFW_KEY_S) == GLFW_PRESS)
        mCamera.processKeyboard(Renderer::CameraMovement::BACKWARD, pDeltaTime);
}

void Application::initScene()
{
    mLightShader = mResources.create<Shader>("shader", mRenderer, "Shader/vertex.vert.spv", "Shader/frag.frag.spv");

    Model** model = mResources.create<Model>("Vempire", mRenderer, "Assets/dancing_vampire.dae");
    Texture** texture = mResources.create<Texture>("texture", mRenderer, "Assets/Vampire_diffuse.png");
    GameObject* obj = new GameObject(mRenderer, mCamera, model, mLightShader, texture, Maths::FVector3(0, 0, 0), Maths::FVector3(0, 180, 0), Maths::FVector3(1, 1, 1));
    mScene.addNode(obj);


    Model** model2 = mResources.create<Model>("plane", mRenderer, "Assets/quad.obj");
    GameObject* obj2 = new GameObject(mRenderer, mCamera, model2, mLightShader, nullptr, Maths::FVector3(0, 0, 0), Maths::FVector3(180, 0, 0), Maths::FVector3(20, 1, 20));
    mScene.addNode(obj2);

    time.updateDeltaTime();
}

void Application::updateDemo(float pDeltaTime)
{

}

void Application::run()
{
    initScene();
    
    while (!mWindow.shouldClose())
    {
        update();

        updateDemo(time.mDeltaTime);

        draw();
    }

    cleanUp();
}

void Application::update()
{
    mRenderer.finishSetup();

    mWindow.pollEvents();
    time.updateDeltaTime();

    processInput(time.mDeltaTime);
    mCamera.updatePos();
    mScene.update(time.mDeltaTime);
}

void Application::cleanUp()
{
    mRenderer.waitForCleanUp();
    mWindow.shutDown();
    mResources.mPool.stop();
    mRenderer.finishSetup();
    mResources.clear();
    mScene.clear();
    delete lineDrawer;
}

void Application::draw()
{
    mRenderer.beginDraw();

    if (mLightShader != nullptr && *mLightShader != nullptr)
        mScene.sendLight(*(*mLightShader));

    mScene.draw();
    mRenderer.endDraw();
}

void Application::DeltaTime::updateDeltaTime()
{
    float currentFrame = glfwGetTime();
    mDeltaTime = currentFrame - mLastFrame;
    mLastFrame = currentFrame;
}