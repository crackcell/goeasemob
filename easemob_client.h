/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2016, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _EASEMOB_CLIENT_H_
#define _EASEMOB_CLIENT_H_

/**
 * 
 *
 * @file easemob_client.h
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Sun Aug 21 20:44:24 2016
 *
 **/

#include <string>
#include <vector>

#include <emclient.h>
#include <emchatmanager_listener.h>
#include <emcallback.h>

typedef void (*ReceiveCallback)(const std::vector<std::string> messages);

class EasemobClient : public easemob::EMChatManagerListener {
protected:
    ReceiveCallback recv_callback_;

    bool is_init_;
    bool is_login_;
    std::string login_user_;

    easemob::EMClient *client_;

public:
    EasemobClient();
    virtual ~EasemobClient();

    virtual int Init(const std::string &work_path, const std::string &appkey);
    virtual void SetReceiveCallback(ReceiveCallback callback);

    virtual int Login(const std::string &username, const std::string &password);
    virtual int Logout();
    virtual int SendMessage(const std::string &to, const std::string message);

    // EMChatManagerListener calback
    virtual void onReceiveMessages(const easemob::EMMessageList &messages);
};

#endif /* _EASEMOB_CLIENT_H_ */

/* vim: set expandtab shiftwidth=2 tabstop=2: */
