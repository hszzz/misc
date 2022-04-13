#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <vector>

const size_t kBufferSize = 4096;

class RingBuffer {
 public:
  RingBuffer() : buffer_(kBufferSize) {}

 private:
  std::vector<char> buffer_;
};

#endif  // RING_BUFFER_H
