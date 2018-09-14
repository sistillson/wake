#ifndef THUNK_H
#define THUNK_H

#include <queue>
#include <memory>
#include <atomic>

// We need ~Receiver
#include "heap.h"

struct Binding;
struct Expr;

struct Thunk {
  Expr *expr;
  long serial;
  std::shared_ptr<Binding> binding;
  std::unique_ptr<Receiver> receiver;

  Thunk() { }
  Thunk(Expr *expr_, long serial_, std::shared_ptr<Binding> &&binding_, std::unique_ptr<Receiver> receiver_) : expr(expr_), serial(serial_), binding(std::move(binding_)), receiver(std::move(receiver_)) { }

  void eval(ThunkQueue &queue);
};

// min serial first
static inline bool operator < (const Thunk &a, const Thunk &b) { return a.serial > b.serial; }

struct ThunkQueue {
  std::atomic<long> serial;
  bool stack_trace;
  std::vector<Thunk> queue;

  ThunkQueue() : serial(0) { }
  void run();

  void emplace(Expr *expr, std::shared_ptr<Binding> &&binding, std::unique_ptr<Receiver> receiver);
  void emplace(Expr *expr, const std::shared_ptr<Binding> &binding, std::unique_ptr<Receiver> receiver);
};

#endif
