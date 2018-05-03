	#include "../gen-cpp/serDemo.h"    
    //------------------------------------------------------------------------------  
    #include <thrift/transport/TSocket.h>    
    #include <thrift/transport/TBufferTransports.h>    
    #include <thrift/protocol/TBinaryProtocol.h>    
        
    using namespace apache::thrift;    
    using namespace apache::thrift::protocol;    
    using namespace apache::thrift::transport;    
        
    using boost::shared_ptr;    
        
    int main(int argc, char **argv) {    
        boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));    
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));    
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));    
        serDemoClient client(protocol);
        transport->open();    
        
        // ----------------------------我们的代码写在这里------------------------------  
        message msg;  
        msg.seqId = 1;  
        msg.content = "client message";      
        client.put(msg);  
        //--------------------------------------------------------------------------  
      
        transport->close();    
        
        return 0;    
    }  