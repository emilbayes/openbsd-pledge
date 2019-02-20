#include <string.h>
#include <node_api.h>
#include <assert.h>
#include <napi-macros.h>
#include <unistd.h>

#define NAPI_UTF8_AUTO_LENGTH(name, val) \
  size_t name##_size = 0; \
  NAPI_STATUS_THROWS(napi_get_value_string_utf8(env, val, NULL, 0, &name##_size)) \
  char name[name##_size]; \
  size_t name##_len; \
  NAPI_STATUS_THROWS(napi_get_value_string_utf8(env, val, name, name##_size + 1, &name##_len)) \
  name[name##_size] = '\0';


NAPI_METHOD(napi_openbsd_pledge) {
  NAPI_ARGV(2);

  napi_valuetype arg_type;

  void* promise_ptr = NULL;
  if (argc > 0) {
    NAPI_STATUS_THROWS(napi_typeof(env, argv[0], &arg_type))

    if (arg_type == napi_string) {
      NAPI_UTF8_AUTO_LENGTH(promise, argv[0]);
      promise_ptr = &promise;
    }
    else if (arg_type != napi_null) {
      napi_throw_error(env, "EINVAL", "Invalid argument type for promise");
      return NULL;
    }
  }

  void* execpromise_ptr = NULL;
  if (argc > 1) {
    NAPI_STATUS_THROWS(napi_typeof(env, argv[1], &arg_type))

    if (arg_type == napi_string) {
      NAPI_UTF8_AUTO_LENGTH(execpromise, argv[1]);
      execpromise_ptr = &execpromise;
    }
    else if (arg_type != napi_null) {
      napi_throw_error(env, "EINVAL", "Invalid argument type for promise");
      return NULL;
    }
  }

  int err = pledge((const char*) promise_ptr, (const char*) execpromise_ptr);
  if (err < 0) {
    napi_throw_error(env, strerror(err), strerror(err));
    return NULL;
  }

  return NULL;
}

NAPI_INIT() {
  NAPI_EXPORT_FUNCTION(napi_openbsd_pledge)
}
