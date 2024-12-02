#include "napi/native_api.h"
#include "sqlite3.h"
#include <hilog/log.h>

#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0x3200
#define LOG_TAG "SQLITE3_NATIVE_EXAMPLE"

void handle_rc(sqlite3 *db, int rc) {
  if (rc != SQLITE_OK) {
        OH_LOG_ERROR(LOG_APP, "sqlite3 rc: %{public}d, error: %{public}s\n", rc, sqlite3_errmsg(db));
  }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  for (int i = 0; i < argc; i++) {
    OH_LOG_INFO(LOG_APP, "%{public}s: %{public}s\n", azColName[i], argv[i]);
  }
  return 0;
}


static void sqlite3_test() {
    sqlite3 *db;
    char *errorMessage;
    int rc = sqlite3_open(":memory:", &db);
    handle_rc(db, rc);
    const char *sql = "SELECT sqlite_version()";
    rc = sqlite3_exec(db, sql, callback, 0, &errorMessage);
    handle_rc(db, rc);
}


static napi_value Add(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value sum;
    napi_create_double(env, value0 + value1, &sum);
    
    sqlite3_test();
    
    return sum;

}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "sqlite3_native_example",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterSqlite3_native_exampleModule(void)
{
    napi_module_register(&demoModule);
}
