#include <iostream>

#include "webvfx/effects_impl.h"
#include "webvfx/image.h"
#include "webvfx/parameters.h"
#include "webvfx/webvfx.h"


namespace WebVfx
{

EffectsImpl::EffectsImpl() { }

EffectsImpl::~EffectsImpl() { }

bool EffectsImpl::initialize(const std::string& fileName, int width, int height, Parameters* parameters, bool isTransparent) {
  std::cout << "DEBUG: initialize" << std::endl;
  return true;
}

void EffectsImpl::destroy() { }

bool EffectsImpl::render(double time, Image* renderImage) {
  std::cout << "DEBUG: render " << time << std::endl;
  return true;
}

void EffectsImpl::reload() {
  std::cout << "DEBUG: reload" << std::endl;
}

}
