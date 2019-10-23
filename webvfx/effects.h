// Copyright (c) 2011 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEBVFX_EFFECTS_H_
#define WEBVFX_EFFECTS_H_

#include <webvfx/image.h>

namespace WebVfx
{

/*!
 * @brief An effects implementation that can consume video frame images and
 *   render output.
 *
 * Instances of this class are created with WebVfx::createEffects()
 * and can be accessed from any thread, but the class is not threadsafe
 * so access should be synchronized.
 */
class Effects
{
public:
    /*!
     * @brief Renders the effect for the given @c time.
     *
     * Prior to calling render() each time, all named images must
     * be set via setImage().
     * @param time Time to render image for, must be from 0 to 1.0.
     * @param renderImage Image buffer to render into.
     */
    virtual bool render(double time, Image* renderImage) = 0;

    /*!
     * @brief Destroy the effect
     */
    virtual void destroy() = 0;

    virtual void reload() = 0;

protected:
    Effects() {};
    virtual ~Effects() = 0;
};

}

#endif
