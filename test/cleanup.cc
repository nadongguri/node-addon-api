#include "napi.h"
#include "stdlib.h"

using namespace Napi;

#if (NAPI_VERSION > 2)
static void CleanupFunc(void* data) {
  if (data == NULL) {
    abort();
  } else {
    int* arg = static_cast<int*>(data);
	delete arg;
  }
  return;
}

void AddCleanupHook(const CallbackInfo& info) {
  Napi::Env env = info.Env();
  int* arg = new int;
  Cleanup::AddCleanupHook(env, CleanupFunc, static_cast<void*>(arg));
  return;
}

void AddCleanupHookWithNullArg(const CallbackInfo& info) {
  Napi::Env env = info.Env();
  Cleanup::AddCleanupHook(env, CleanupFunc, NULL);
  return;
}

void RemoveCleanupHookWithNullArg(const CallbackInfo& info) {
  Napi::Env env = info.Env();
  Cleanup::RemoveCleanupHook(env, CleanupFunc, NULL);
  return;
}

Object InitCleanup(Env env) {
  Object exports = Object::New(env);
  exports["addCleanupHook"] = Function::New(env, AddCleanupHook);
  exports["addCleanupHookWithNullArg"] = Function::New(env, AddCleanupHookWithNullArg);
  exports["removeCleanupHookWithNullArg"] = Function::New(env, RemoveCleanupHookWithNullArg);
  return exports;
}
#endif
