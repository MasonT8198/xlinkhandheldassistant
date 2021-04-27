#pragma once

/* Copyright (c) 2020 [Rick de Bondt] - IPCapWrapper.h
 *
 * This file contains an interface for pcapwrapper
 *
 **/


/**
 * Interface for pcapwrapper.
 */
class IPCapWrapper
{
public:
    virtual int Activate() = 0;
    virtual void BreakLoop() = 0;
    virtual void Close() = 0;
    virtual pcap_t* Create(const char* source, char* errbuf) = 0;
    virtual int Dispatch(int cnt, pcap_handler callback, unsigned char* user) = 0;
    virtual char* GetError() = 0;
    virtual bool IsActivated() = 0;
    virtual pcap_t* OpenOffline(const char* fname, char *errbuf) = 0;
    virtual int NextEx(pcap_pkthdr** header, const unsigned char **pkt_data) = 0;
    virtual int SendPacket(std::string_view buffer) = 0;
    virtual int SetSnapLen(int snaplen) = 0;
    virtual int SetTimeOut(int timeout) = 0;
};
