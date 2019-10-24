// Copyright (c) 2011 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEBVFX_EFFECTS_IMPL_H_
#define WEBVFX_EFFECTS_IMPL_H_

#include <string>
#include <vector>

#include <boost/interprocess/ipc/message_queue.hpp>

#include "webvfx/effects.h"

namespace WebVfx
{

class Content;
class Image;
class Parameters;

class EffectsImpl : public Effects
{
public:
    EffectsImpl() = default;

    // EffectsImpl will take ownership of Parameters
    bool initialize(const std::string& fileName, int width, int height, Parameters* parameters = 0, bool isTransparent = false);
    bool render(double time, Image* renderImage);
    void destroy();
    void reload();

private:
    ~EffectsImpl() = default;
    boost::interprocess::message_queue *message_queue_request_ = nullptr;
    boost::interprocess::message_queue *message_queue_response_ = nullptr;
    boost::interprocess::shared_memory_object *shared_memory_object_ = nullptr;
    boost::interprocess::mapped_region *mapped_region_ = nullptr;
    std::vector<char> png_buffer_;
};

}

#endif
