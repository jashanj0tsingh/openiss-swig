//
// Created by jash on 25/01/19.
//

#ifndef RT_SKEL_ROS_GESTURE_OINITEGESTURETRACKER_H
#define RT_SKEL_ROS_GESTURE_OINITEGESTURETRACKER_H

#include <NiTE.h>
#include <iostream>
#include "OIGestureTracker.hpp"

namespace openiss
{
    class OINiTEGestureTracker : public OIGestureTracker
    {
    public:
        OINiTEGestureTracker();
        ~OINiTEGestureTracker() override;
        /**/
        OIStatusType init() override;
        OIStatusType update() override;
        OIStatusType stop() override;
        /**/
        OIStatusType startGestureDetection() override;
        OIStatusType stopGestureDetection() override;
        /**/
        OIStatusType startHandTracking() override;
        OIStatusType stopHandTracking() override;
        /**/
        std::vector<OIGestureData> getGestures() override;
        std::vector<OIHandData> getHands() override;
        /**/
        GFrame* getDepthFrame() override;
        /**/
        void convertHandCoordinatesToDepth(float p_x, float p_y, float p_z, float* p_OutX, float* p_OutY) override;
        void convertDepthCoordinatesToHand(int p_x, int p_y, int p_z, float* p_OutX, float* p_OutY) override;

    private:
        /**/
        class FrameListener : public nite::HandTracker::NewFrameListener
        {
        public:
            explicit FrameListener(OINiTEGestureTracker* p_OINiTEGestureTracker)
            {
                this->m_OINiTEGestureTracker = p_OINiTEGestureTracker;
            }
            ~FrameListener()
            {
                delete m_OINiTEGestureTracker;
            }
            GFrame m_GFrame;
            void onNewFrame(nite::HandTracker &p_HandTracker) override;

        private:
            OINiTEGestureTracker* m_OINiTEGestureTracker;

        };
        /**/
        FrameListener* m_listener;
        nite::Status m_eNiTEStatus;
        nite::HandId m_iHandID;
        nite::HandTracker m_oHandTracker;
        nite::HandTrackerFrameRef m_oHandTrackerFrame;
        nite::Point3f m_GesturePosition;
        openni::VideoFrameRef m_DepthFrame;
        /**/
        OIStatus m_eStatus;
        OIGestureData m_eGesture;
        OIHandData m_eHand;
        std::vector<OIGestureData> m_eGestureData;
        std::vector<OIHandData> m_eHandData;
    };
}
#endif //RT_SKEL_ROS_GESTURE_OINITEGESTURETRACKER_H