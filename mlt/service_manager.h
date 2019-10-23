// Copyright (c) 2010 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MLTWEBVFX_SERVICE_MANAGER_H_
#define MLTWEBVFX_SERVICE_MANAGER_H_

extern "C" {
    #include <mlt/framework/mlt_service.h>
}
#include <vector>


namespace WebVfx
{
    class Effects;
    class Image;
}

namespace MLTWebVfx
{
class ImageProducer;
class ServiceLocker;
class ServiceParameters;

class ServiceManager
{
public:
    int render(WebVfx::Image* outputImage, mlt_position position, mlt_position length, bool hasAlpha = false);
    void setupConsumerListener(mlt_frame frame);
    void onConsumerStopping();

private:
    friend class ServiceLocker;
    ServiceManager(mlt_service service);
    ~ServiceManager();
    bool initialize(int width, int height);

    mlt_service service;
    mlt_properties event;
    WebVfx::Effects* effects;
    ServiceParameters* parameters;

    std::vector<ImageProducer*>* imageProducers;
};

}

#endif
