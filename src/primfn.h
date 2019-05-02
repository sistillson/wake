/*
 * Copyright 2019 SiFive, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PRIMFN_H
#define PRIMFN_H

#include <memory>
#include <vector>

struct Binding;
struct Receiver;
struct Value;
struct WorkQueue;
struct TypeVar;

typedef bool (*PrimType)(const std::vector<TypeVar*> &args, TypeVar *out);
typedef void (*PrimFn)(void *data, WorkQueue &queue, std::unique_ptr<Receiver> completion, std::shared_ptr<Binding> &&binding, std::vector<std::shared_ptr<Value> > &&args);
#define PRIMTYPE(name) bool name(const std::vector<TypeVar*> &args, TypeVar *out)
#define PRIMFN(name) void name(void *data, WorkQueue &queue, std::unique_ptr<Receiver> completion, std::shared_ptr<Binding> &&binding, std::vector<std::shared_ptr<Value> > &&args)

#endif
