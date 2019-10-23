// Copyright (c) 2011 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEBVFX_EFFECTS_IMPL_H_
#define WEBVFX_EFFECTS_IMPL_H_

#include <string>
#include "webvfx/effects.h"

namespace WebVfx
{

class Content;
class Image;
class Parameters;

class EffectsImpl : public Effects
{
public:
    EffectsImpl();

    // EffectsImpl will take ownership of Parameters
    bool initialize(const std::string& fileName, int width, int height, Parameters* parameters = 0, bool isTransparent = false);
    bool render(double time, Image* renderImage);
    void destroy();
    void reload();

private:
    ~EffectsImpl();
};

}

#endif
