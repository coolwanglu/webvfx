#include <iostream>

#include <png.h>

#include "webvfx/effects_impl.h"
#include "webvfx/image.h"
#include "webvfx/parameters.h"
#include "webvfx/webvfx.h"


namespace WebVfx
{

bool EffectsImpl::initialize(const std::string& fileName, int width, int height, Parameters* parameters, bool isTransparent) {
  std::cout << "DEBUG: initialize" << std::endl;

  message_queue_request_ = new boost::interprocess::message_queue(
      boost::interprocess::open_only,
      "chromevfx_message_queue_request");

  message_queue_response_ = new boost::interprocess::message_queue(
      boost::interprocess::open_only,
      "chromevfx_message_queue_response");

  shared_memory_object_ = new boost::interprocess::shared_memory_object(
      boost::interprocess::open_only,
      "chromevfx_shared_memory",
      boost::interprocess::read_only);

  mapped_region_ = new boost::interprocess::mapped_region(
      *shared_memory_object_,
      boost::interprocess::read_only,
      0, 1024 * 1024 * 16);

  return true;
}

void EffectsImpl::destroy() { }

bool read_png(void *data, size_t size, png_image *image, std::vector<char> *png_buffer) {
  memset(image, 0, sizeof(png_image));
  image->version = PNG_IMAGE_VERSION;
  if(png_image_begin_read_from_memory(image, data, size) == 0) {
    return false;
  }
  image->format = PNG_FORMAT_RGB;
  const size_t input_data_length = PNG_IMAGE_SIZE(*image);
  png_buffer->resize(input_data_length);
  png_bytep buffer = (png_bytep)png_buffer->data();
  memset(buffer, 0, input_data_length);
  if (png_image_finish_read(image, NULL, buffer, 0, NULL) == 0) {
    return false;
  }

  //std::cout << "png size " << input_data_length << std::endl;

  return true;
}

bool EffectsImpl::render(double time, Image* renderImage) {
  message_queue_request_->send(&time, sizeof(double), 0);

  std::cout << "send " << time << std::endl;

  int image_size;
  unsigned int priority;
  boost::interprocess::message_queue::size_type recvd_size;
  message_queue_response_->receive(&image_size, sizeof(image_size), recvd_size, priority);

  if (image_size > mapped_region_->get_size()) {
    return false;
  }

  std::cout << "recv " << image_size << std::endl;

  png_image image;
  if (!read_png(mapped_region_->get_address(), image_size, &image, &png_buffer_)) {
    return false;
  }
  if (image.width != renderImage->width() || image.height != renderImage->height() || png_buffer_.size() != renderImage->byteCount()) {
    std::cout << "wrong dimention "
      << image.width << " " << image.height << " " << png_buffer_.size() << " - "
      << renderImage->width() << " " << renderImage->height() << " " << renderImage->byteCount() << std::endl;
    return false;
  }
  std::memcpy(renderImage->pixels(), png_buffer_.data(), png_buffer_.size());

  //png_image_write_to_file(&image, "debug.png", 0, png_buffer_.data(), 0, NULL);
  
  png_image_free(&image);

  return true;
}

void EffectsImpl::reload() {
  std::cout << "DEBUG: reload" << std::endl;
}

}
