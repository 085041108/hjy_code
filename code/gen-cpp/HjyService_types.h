/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef HjyService_TYPES_H
#define HjyService_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>




class hjy_request;

class hjy_respose;

typedef struct _hjy_request__isset {
  _hjy_request__isset() : api(false), logid(false), req_string(false) {}
  bool api :1;
  bool logid :1;
  bool req_string :1;
} _hjy_request__isset;

class hjy_request {
 public:

  static const char* ascii_fingerprint; // = "A260D3573D95B3BD751F6453CCF5CDF7";
  static const uint8_t binary_fingerprint[16]; // = {0xA2,0x60,0xD3,0x57,0x3D,0x95,0xB3,0xBD,0x75,0x1F,0x64,0x53,0xCC,0xF5,0xCD,0xF7};

  hjy_request(const hjy_request&);
  hjy_request& operator=(const hjy_request&);
  hjy_request() : api(0), logid(0), req_string() {
  }

  virtual ~hjy_request() throw();
  int32_t api;
  int64_t logid;
  std::string req_string;

  _hjy_request__isset __isset;

  void __set_api(const int32_t val);

  void __set_logid(const int64_t val);

  void __set_req_string(const std::string& val);

  bool operator == (const hjy_request & rhs) const
  {
    if (!(api == rhs.api))
      return false;
    if (!(logid == rhs.logid))
      return false;
    if (!(req_string == rhs.req_string))
      return false;
    return true;
  }
  bool operator != (const hjy_request &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const hjy_request & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const hjy_request& obj);
};

void swap(hjy_request &a, hjy_request &b);

typedef struct _hjy_respose__isset {
  _hjy_respose__isset() : ret(false), res_string(false) {}
  bool ret :1;
  bool res_string :1;
} _hjy_respose__isset;

class hjy_respose {
 public:

  static const char* ascii_fingerprint; // = "15896F1A4438B1ECBB80CEA66AD0C4C5";
  static const uint8_t binary_fingerprint[16]; // = {0x15,0x89,0x6F,0x1A,0x44,0x38,0xB1,0xEC,0xBB,0x80,0xCE,0xA6,0x6A,0xD0,0xC4,0xC5};

  hjy_respose(const hjy_respose&);
  hjy_respose& operator=(const hjy_respose&);
  hjy_respose() : ret(0), res_string() {
  }

  virtual ~hjy_respose() throw();
  int16_t ret;
  std::string res_string;

  _hjy_respose__isset __isset;

  void __set_ret(const int16_t val);

  void __set_res_string(const std::string& val);

  bool operator == (const hjy_respose & rhs) const
  {
    if (!(ret == rhs.ret))
      return false;
    if (!(res_string == rhs.res_string))
      return false;
    return true;
  }
  bool operator != (const hjy_respose &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const hjy_respose & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const hjy_respose& obj);
};

void swap(hjy_respose &a, hjy_respose &b);



#endif
