#include <errno.h>
#include <string.h>
#include <node_api.h>
#include <assert.h>
#include <napi-macros.h>
#include <unistd.h>

#define NAPI_UTF8_GET_LENGTH(name, val) \
  NAPI_STATUS_THROWS(napi_get_value_string_utf8(env, val, NULL, 0, &name));

const char* err_name(int status) {
  switch (status) {
    case EFAULT: return "EFAULT";
    case EINVAL: return "EINVAL";
    case EPERM: return "EPERM";
    default: return "UNKNOWN";
  }
}

#define MAX_STR_LEN 1023

NAPI_METHOD(napi_openbsd_pledge) {
  NAPI_ARGV(2);

  napi_valuetype arg_type = napi_undefined;

  size_t promise_len = 0;
  char promise[MAX_STR_LEN + 1];
  if (argc > 0) {
    NAPI_STATUS_THROWS(napi_typeof(env, argv[0], &arg_type));

    switch (arg_type) {
      case napi_null:
      case napi_undefined:
      case napi_string:
        break;
      default:
        napi_throw_error(env, "EINVAL", "promise must be string or null");
        return NULL;
    }

    if (arg_type == napi_string) {
      NAPI_UTF8_GET_LENGTH(promise_len, argv[0]);

      if (promise_len > MAX_STR_LEN) {
        napi_throw_error(env, "EINVAL", "promise string too long");
        return NULL;
      }

      NAPI_STATUS_THROWS(napi_get_value_string_utf8(env, argv[0], promise, MAX_STR_LEN + 1, &promise_len));
    }
  }

  size_t execpromise_len = 0;
  char execpromise[MAX_STR_LEN + 1];
  if (argc > 1) {
    NAPI_STATUS_THROWS(napi_typeof(env, argv[1], &arg_type));

    switch (arg_type) {
      case napi_null:
      case napi_undefined:
      case napi_string:
        break;
      default:
        napi_throw_error(env, "EINVAL", "execpromise must be string or null");
        return NULL;
    }

    if (arg_type == napi_string) {
      NAPI_UTF8_GET_LENGTH(execpromise_len, argv[1]);

      if (execpromise_len > MAX_STR_LEN) {
        napi_throw_error(env, "EINVAL", "execpromise string too long");
        return NULL;
      }

      NAPI_STATUS_THROWS(napi_get_value_string_utf8(env, argv[1], execpromise, MAX_STR_LEN + 1, &execpromise_len));
    }
  }

  int err = pledge(promise_len > 0 ? promise : NULL, execpromise_len > 0 ? execpromise : NULL);
  if (err < 0) {
    napi_throw_error(env, err_name(errno), strerror(errno));
    return NULL;
  }

  return NULL;
}

NAPI_INIT() {
  NAPI_EXPORT_FUNCTION(napi_openbsd_pledge)
}
