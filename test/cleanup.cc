#include "napi.h"
//#include "stdlib.h"

using namespace Napi;

#if (NAPI_VERSION > 2)

class TestCleanupHook : public EnvCleanup {
  public:
    static void DoCleanup(const CallbackInfo& info) {
	  int secret = 42;
	  int wrongSecret = 17;
	  TestCleanupHook* cleanupHook = new TestCleanupHook(info.Env(), Cleanup, &wrongSecret);
	}
  private:
    TestCleanupHook(Env env, void (*fun)(void* arg), void* arg)
	  : EnvCleanup(env, fun, arg) {}
	static Cleanup(void* arg) {
	  printf("cleanup(%d)\n", *static_cast<int*>(arg));
	}
};

Object InitAsyncWorker(Env env) {
  Object exports = Object::New(env);
  exports["doCleanup"] = Function::New(env, TestCleanupHook::DoCleanup);
  return exports;
}

#if 0
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
  int *a = NULL;
   *a= 1;
  Napi::Env env = info.Env();
  int* arg = new int;
  fprintf(stderr, "[%s][%d] +_+\n", __func__, __LINE__);
  Cleanup::AddCleanupHook(env, CleanupFunc, static_cast<void*>(arg));
  return;
}

void AddCleanupHookWithNullArg(const CallbackInfo& info) {
  Napi::Env env = info.Env();
  fprintf(stderr, "[%s][%d] +_+\n", __func__, __LINE__);
  Cleanup::AddCleanupHook(env, CleanupFunc, NULL);
  return;
}

void RemoveCleanupHookWithNullArg(const CallbackInfo& info) {
  Napi::Env env = info.Env();
  fprintf(stderr, "[%s][%d] +_+\n", __func__, __LINE__);
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
#endif
