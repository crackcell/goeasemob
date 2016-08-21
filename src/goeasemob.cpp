/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2016, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

/**
 * 
 *
 * @file goeasemob.cpp
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Sun Aug 21 14:12:58 2016
 *
 **/

#include <stdio.h>
#include <emclient.h>

using namespace easemob;

void goeasemob_init(const char *client_id) {
    easemob::EMChatConfigsPtr configPtr = easemob::EMChatConfigsPtr(new easemob::EMChatConfigs(resourcePath, workPath, client_id));
    chatClient = easemob::EMClient::create(configPtr);
    easemob::EMErrorPtr result = chatClient->login("test01", "test02");
if(result->mErrorCode == EMError::NO_ERROR) { 
    cout << "login success" << endl; 
} else { 
    cout << result->mDescription << endl; 
}
}

/* vim: set expandtab shiftwidth=2 tabstop=2: */
