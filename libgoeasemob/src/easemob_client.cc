/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2016, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the Apache Licence
 *
 **************************************************************/

/**
 * 
 *
 * @file easemob_client.cc
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Sun Aug 21 20:53:57 2016
 *
 **/

#include <goeasemob/easemob_client.h>

#include <emclient.h>
#include <emchatmanager_interface.h>
#include <message/emmessage.h>
#include <message/emtextmessagebody.h>

using namespace std;
using namespace easemob;

EasemobClient::EasemobClient() : is_init_(false), is_login_(false) {}

EasemobClient::~EasemobClient() {
    client_->getChatManager().removeListener(this);
}

int EasemobClient::Init(const string &work_path, const string &appkey) {
    EMChatConfigsPtr config = EMChatConfigsPtr(new EMChatConfigs(work_path, work_path, appkey));
    config->setEnableConsoleLog(false);
    client_ = EMClient::create(config);
    client_->getChatManager().addListener(this);
    is_init_ = true;
    return 0;
}

void EasemobClient::SetReceiveCallback(ReceiveCallback callback) {
    this->recv_callback_ = callback;
}

int EasemobClient::Login(const string &username, const string &password) {
    if (!is_init_) {
        return 0;
    }
    EMErrorPtr result = client_->login(username, password);
    if (result->mErrorCode != EMError::EM_NO_ERROR) {
        cout << result->mDescription << endl;
    }
    is_login_ = true;
    login_user_ = username;
    return 0;
}

int EasemobClient::Logout() {
    if (!is_login_) {
        return 1;
    }
    client_->logout();
    is_login_ = false;
    return 0;
}

int EasemobClient::SendMessage(const string &to, const string message) {
    if (!is_init_ || !is_login_) {
        return 1;
    }
    EMTextMessageBodyPtr body = EMTextMessageBodyPtr(new EMTextMessageBody(message));
    EMMessagePtr msg = EMMessage::createSendMessage(login_user_, to, body);
    client_->getChatManager().sendMessage(msg);
    return 1;
}

void EasemobClient::onReceiveMessages(const EMMessageList &messages) {
    list<string> messageList;

    if (messages.size() > 0) {
        for(auto m : messages) {
            if (m->bodies().size() > 0 && m->bodies()[0]->type() == EMMessageBody::TEXT) {
                string msg = static_cast<EMTextMessageBody*>(m->bodies()[0].get())->text();
                messageList.push_back(msg);
            }
        }
    }

    recv_callback_(messageList);
}

/* vim: set expandtab shiftwidth=2 tabstop=2: */
