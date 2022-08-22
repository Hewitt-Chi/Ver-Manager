#pragma once


#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


class CYCSimpleTCPClient : public CYCSimpleTCPConnection
{
    DECLARE_DYNAMIC(CYCSimpleTCPClient)

public:
    CYCSimpleTCPClient();
    virtual ~CYCSimpleTCPClient();


protected:
    OVERRIDE_CYCSimpleTCPConnection_OnCreateSocket();
    OVERRIDE_CYCSimpleTCPConnection_OnConnectSocket();
    OVERRIDE_CYCSimpleTCPConnection_OnDisconnectSocket();
    OVERRIDE_CYCSimpleTCPConnection_OnDestroySocket();

};