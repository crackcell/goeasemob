/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2016, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the Apache licence
 *
 **************************************************************/

/**
 * 
 *
 * @file goeasemob_wrapper.cc
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Tue Aug 23 00:05:12 2016
 *
 **/

#include "easemob_client_wrapper.h"
#include "easemob_client.h"

#include <stdlib.h>

EasemobClient *p;

void easemob_client_new() {
    if (p) {
        return;
    }
    p = new EasemobClient;
}

void easemob_client_free() {
    if (!p) {
        return;
    }
    delete p;
}

int easemob_client_init(const char *workpath, const char *appkey) {
    if (!p || !workpath || !appkey) {
        return 1;
    }

    return p->Init(workpath, appkey);
}

int easemob_client_login(const char *username, const char *password) {
    if (!p) {
        return 1;
    }
    
    return p->Login(username, password);
}

void easemob_client_logout() {
    p->Logout();
}

int easemob_client_sendmessage(const char *receiver, const char *message) {
    if (!p) {
        return 1;
    }
    return p->SendMessage(receiver, message);
}

void easemob_client_set_message_receive_callback(receive_message_callback_func func) {
    if (!p) {
        return;
    }
}

/* vim: set expandtab shiftwidth=2 tabstop=2: */
