#include "Animator.h"

using namespace Renderer;

Animator::Animator(Animation* pAnimation)
{
    mCurrentTime = 0.0;
    mCurrentAnimation = pAnimation;

    mFinalBoneMatrices.reserve(MAX_BONE);
    for (int i = 0; i < MAX_BONE; i++)
        mFinalBoneMatrices.push_back(Maths::FMatrix4(1.0f));
}

void Animator::updateAnimation(float pDeltaTime)
{
    if (mCurrentAnimation)
    {
        mCurrentTime += mCurrentAnimation->mTicksPerSecond * pDeltaTime;
        mCurrentTime = std::fmod(mCurrentTime, mCurrentAnimation->mDuration);
        calculateBoneTransform(&mCurrentAnimation->mRootNode, Maths::FMatrix4(1.0f));
    }
}
void Animator::calculateBoneTransform(const AssimpNodeData* pNode, Maths::FMatrix4 pParentTransform)
{
    std::string nodeName = pNode->mName;
    Maths::FMatrix4 nodeTransform = pNode->mTransformation;

    Bone* Bone = mCurrentAnimation->findBone(nodeName);

    if (Bone)
    {
        Bone->update(mCurrentTime);
        nodeTransform = Bone->mLocalTransform;
    }

    Maths::FMatrix4 globalTransformation = pParentTransform * nodeTransform;

    std::map<std::string, BoneInfo>& boneInfoMap = mCurrentAnimation->mBoneInfoMap;
    if (boneInfoMap.find(nodeName) != boneInfoMap.end())
    {
        int index = boneInfoMap[nodeName].mId;
        Maths::FMatrix4 offset = boneInfoMap[nodeName].mOffset;
        mFinalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < pNode->mChildrenCount; i++)
        calculateBoneTransform(&pNode->mChildren[i], globalTransformation);
}