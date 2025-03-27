//
// dpw
//

#include <spdlog/spdlog.h>

#include <gitrepo/tools.hpp>
#include <domainkeys/keys.hpp>
#include <quickkv/quickkv.hpp>

int main() {
    constexpr auto lang = "c++";
    spdlog::info("Hello and welcome to {} tiny application, version: {}", lang, gitrepo::tools::VERSION);

    // create the k/v store
    quickkv::KVStore store;

    // create a unique timestamp key
    auto key = domainkeys::keys::create_timestamp_key();
    spdlog::info("key: {}", key.to_string());

    // write to the store
    store.set(key.to_string(), "hello tiny kv store.");

    // show the store size
    spdlog::info("store size: {}", store.size());

    return 0;
}
