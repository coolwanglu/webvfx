#include <iostream>
#include <cstring>

#include <boost/interprocess/ipc/message_queue.hpp>

#include <node.h>
#include <node_buffer.h>


namespace ipc {

using v8::FunctionCallbackInfo;
using v8::Int32;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

static boost::interprocess::message_queue *message_queue_request_ = nullptr;
static boost::interprocess::message_queue *message_queue_response_ = nullptr;
static boost::interprocess::shared_memory_object *shared_memory_object_ = nullptr;
static boost::interprocess::mapped_region *mapped_region_ = nullptr;
constexpr int SHARED_MEMORY_OBJECT_SIZE = 1024 * 1024 * 16; // 16MB

void init(const FunctionCallbackInfo<Value>& args) {
  if (message_queue_request_ == nullptr) {
    boost::interprocess::message_queue::remove("chromevfx_message_queue_request");
    message_queue_request_ = new boost::interprocess::message_queue(
        boost::interprocess::open_or_create,
        "chromevfx_message_queue_request",
        128,
        sizeof(double));
  }
  if (message_queue_response_ == nullptr) {
    boost::interprocess::message_queue::remove("chromevfx_message_queue_response");
    message_queue_response_ = new boost::interprocess::message_queue(
        boost::interprocess::open_or_create,
        "chromevfx_message_queue_response",
        128,
        sizeof(int));
  }
  if (shared_memory_object_ == nullptr) {
    boost::interprocess::shared_memory_object::remove("chromevfx_shared_memory");
    shared_memory_object_ = new boost::interprocess::shared_memory_object(
        boost::interprocess::open_or_create,
        "chromevfx_shared_memory",
        boost::interprocess::read_write);
    shared_memory_object_->truncate(SHARED_MEMORY_OBJECT_SIZE);
    mapped_region_ = new boost::interprocess::mapped_region(
        *shared_memory_object_,
        boost::interprocess::read_write,
        0,
        SHARED_MEMORY_OBJECT_SIZE);
  }
  std::cout << "IPC init" << std::endl;
}

void receive_request(const FunctionCallbackInfo<Value>& args) {
  //std::cout << "IPC receive" << std::endl;
  unsigned int priority;
  double msg;
  boost::interprocess::message_queue::size_type recvd_size;
  message_queue_request_->receive(&msg, sizeof(msg), recvd_size, priority);

  auto* isolate = args.GetIsolate();
  args.GetReturnValue().Set(Number::New(isolate, msg));
}

void send_response(const FunctionCallbackInfo<Value>& args) {
 // std::cout << "IPC receive" << std::endl;
  int msg = args[0].As<Int32>()->Value();
  message_queue_response_->send(&msg, sizeof(msg), 0);
}

void save_screenshot(const FunctionCallbackInfo<Value>& args) {
  Local<Object> buffer_obj = args[0]->ToObject();
  const char* png_data = node::Buffer::Data(buffer_obj);
  const size_t png_data_size = node::Buffer::Length(buffer_obj);
  // std::cout << "PNG size " << png_data_size << std::endl;
  if (png_data_size > mapped_region_->get_size()) {
    std::cout << "WARNING: png data too large " << png_data_size << std::endl;
  } else {
    std::memcpy(mapped_region_->get_address(), png_data, png_data_size);
  }
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "init", init);
  NODE_SET_METHOD(exports, "receive_request", receive_request);
  NODE_SET_METHOD(exports, "send_response", send_response);
  NODE_SET_METHOD(exports, "save_screenshot", save_screenshot);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace ipc
