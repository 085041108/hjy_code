/**
*@file     service.h
*@author   wjy
*@date      2016.09.11
*
**/

#ifndef  SERVICE_HANDLE_H
#define  SERVICE_HANDLE_H

#include "../gen-cpp/HjyService.h"

//BEGIN_NAMESPACE_SERVICE


class ServiceHandle {
public:
    virtual ~ServiceHandle();
    virtual int Init();
    // need params: string name, string password
    virtual int LoginByNameAndPw(const hjy_request& req, hjy_respose& _return);
    virtual int Register(const hjy_request& req, hjy_respose& _return);
    virtual int ShowMainCour(const hjy_request& req, hjy_respose& _return);
    virtual int PubMainCour(const hjy_request& req, hjy_respose& _return);

};

#endif
