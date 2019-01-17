#include "napi.h"

using namespace Napi;

#if (NAPI_VERSION > 2)

class TestCleanupHook : public EnvCleanup {
  public:
    static void DoCleanup(const CallbackInfo& info) {
	  static int secret = 42;
	  static int wrongSecret = 17;
	  TestCleanupHook* cleanupHook = new TestCleanupHook(info);
	  cleanupHook->AddHook(Cleanup, &secret);
	  cleanupHook->RemoveHook(Cleanup, &secret);
	  cleanupHook->AddHook(Cleanup, &wrongSecret);
	  delete cleanupHook;

	  TestCleanupHook* cleanupHook2 = new TestCleanupHook(info, Cleanup, &secret);
	  cleanupHook2->AddHook(Cleanup, &wrongSecret);
	  cleanupHook2->RemoveHook(Cleanup, &wrongSecret);
	}
  private:
    TestCleanupHook(const CallbackInfo& info) : EnvCleanup(info.Env()) {}
    TestCleanupHook(const CallbackInfo& info, void (*fun)(void* arg), void* arg)
	  : EnvCleanup(info.Env(), fun, arg) {}
	static void Cleanup(void* arg) {
	  printf("cleanup(%d)\n", *static_cast<int*>(arg));
	};
};

Object InitCleanup(Env env) {
  Object exports = Object::New(env);
  exports["doCleanup"] = Function::New(env, TestCleanupHook::DoCleanup);
  return exports;
}

#endif
