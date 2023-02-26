#pragma once
#include "Animation.h"

#define MAX_BONE 100

namespace Renderer
{
    class Animator
    {
        public:
            std::vector<Maths::FMatrix4> mFinalBoneMatrices;
            Animation* mCurrentAnimation = nullptr;
            float mCurrentTime = 0;

            Animator(Animation* pAnimation);

            void updateAnimation(float pDeltaTime);
            void Animator::calculateBoneTransform(const AssimpNodeData* pNode, Maths::FMatrix4 pParentTransform);
    };
}