// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "../gen-cpp/HjyService.h"
#include "../include/data_define.h"
#include "../include/service_handle.h"
#include "../include/global_config.h"
#include "../include/util.h"
#include <iostream>
#include <glog/logging.h>
#include <string>
#include<stdio.h>
#include<stdlib.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class HjyServiceHandler : virtual public HjyServiceIf {
 public:
  HjyServiceHandler() {
     GlobalConfig::InitLog(); 
     LOG(INFO) << "start to create a new instance";
    // global config initialization goed here
     std::string conf_path = "conf/simdb.ini";
     int ret = GlobalConfig::Init(conf_path);
     if (ret != 0) {
         LOG(WARNING) << "global config read conf fail, " << conf_path.c_str();
     }
     LOG(INFO) << "db user: " << GlobalConfig::g_db_user.c_str();
     LOG(INFO) << "db user: " << GlobalConfig::g_db_password.c_str();
     LOG(INFO) << "db user: " << GlobalConfig::g_db_host.c_str();
     LOG(INFO) << "db user: " << GlobalConfig::g_db_name.c_str();
     LOG(INFO) << "db user: " << GlobalConfig::g_db_port;
    // db initialization goes here   ==g_db_access
    // service initialization goes here   ==g_service_access
    // 生成随机数种子，random
     srand((int)time(0)); 
  }

  void call(hjy_respose& _return, const hjy_request& req) {
    // Your implementation goes here
    switch (req.api) {
    case HJY_LOGIN: {
        LOG(INFO) << req.logid << "get a request:" << req.api;
        ServiceHandle* service_handle = new ServiceHandle();
        service_handle->LoginByNameAndPw(req, _return);
        delete service_handle;
        break;
        }
    case HJY_REGISTER: {
        LOG(INFO) << req.logid << "get a request:" << req.api;
        ServiceHandle* service_handle = new ServiceHandle();
        service_handle->Register(req, _return);
        delete service_handle;
        break;
        }
	case HJY_SHOW_MAIN_COUR: {
		LOG(INFO) << req.logid << "get a request:" << req.api;
        ServiceHandle* service_handle = new ServiceHandle();
        service_handle->ShowMainCour(req, _return);
        delete service_handle;
        break;
	}
	case HJY_PUB_MAIN_COUR: {
		LOG(INFO) << req.logid << "get a request:" << req.api;
        ServiceHandle* service_handle = new ServiceHandle();
        service_handle->PubMainCour(req, _return);
        delete service_handle;
        break;
	}
    default: {
        LOG(ERROR) << "invalid request type: " << req.api;
        break;
        }
    }
    printf("call\n");
   }

};

int main(int argc, char **argv) {
  int port = 9091;
  shared_ptr<HjyServiceHandler> handler(new HjyServiceHandler());
  shared_ptr<TProcessor> processor(new HjyServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
