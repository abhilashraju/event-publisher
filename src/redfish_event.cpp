#include "bmcwebhook.h"

#include <boost/dll/alias.hpp> // for BOOST_DLL_ALIAS

#include <iostream>
#include <memory>
namespace BmcWeb {

class MyBmcHook : public BmcWebHooks {
  MyBmcHook() {}

public:
  std::string name() const { return "aggregator"; }
  std::string registerRoutes(crow::App &app) {
    BMCWEB_ROUTE(app, "/redfish/v2/Chassis/")
        .methods(boost::beast::http::verb::get)(
            std::bind_front(handleChassisCollectionGet, std::ref(app)));
    return "Registering aggregator routes";
  }
  static inline void handleChassisCollectionGet(
      App &app, const crow::Request &req,
      const std::shared_ptr<bmcweb::AsyncResp> &asyncResp) {

    asyncResp->res.jsonValue["@odata.type"] =
        "#ChassisCollection.ChassisCollection";
    asyncResp->res.jsonValue["@odata.id"] = "/redfish/v2/Chassis";
    asyncResp->res.jsonValue["Name"] = "Chassis Collection";
    std::cout << "Hello from aggregator" << std::endl;
  }
  // Factory method
  static std::shared_ptr<BmcWebHooks> create() {
    return std::shared_ptr<BmcWebHooks>(new MyBmcHook());
  }
};

BMCWEB_SYMBOL_EXPORT std::shared_ptr<BmcWebHooks> create_object() {
  return BmcWeb::MyBmcHook::create();
}

} // namespace BmcWeb
