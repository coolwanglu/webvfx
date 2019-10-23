// Copyright (c) 2010 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string>
#include "webvfx/logger.h"
#include "webvfx/webvfx.h"
#include "webvfx/effects_impl.h"

namespace WebVfx
{

static bool s_initialized = false;

static Logger* s_logger = 0;
static bool s_ownApp = false;

void setLogger(Logger* logger)
{
    s_logger = logger;
}

bool initialize()
{
  // TODO: mutex
    s_initialized = true;
    return true;
}

Effects* createEffects(const std::string& fileName, int width, int height, Parameters* parameters, bool isTransparent)
{
    EffectsImpl* effects = new EffectsImpl();
    if (!effects->initialize(fileName, width, height, parameters, isTransparent)) {
        effects->destroy();
        return 0;
    }
    return effects;
}

void shutdown()
{
    // Delete the s_logger even if not initialized
    delete s_logger; s_logger = 0;

    if (!s_initialized)
        return;
}

void log(const QString& msg)
{
    if (s_logger)
        s_logger->log(msg);
}

}
