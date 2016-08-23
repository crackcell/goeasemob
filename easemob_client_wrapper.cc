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

void* easemob_client_new() {
    easemob_client *p = (easemob_client*)malloc(sizeof(easemob_client));
    p->client =  new EasemobClient;
    return p;
}

void easemob_client_free() {
    if (!p) {
        return;
    }
    delete p->client;
    free(p);
}

int easemob_client_init(easemob_client_t *p, const char *workpath, const char *appkey) {
    if (!p || !p->client || !workpath || !appkey) {
        return 1;
    }

    return p->client->Init(workpath, appkey);
}

int easemob_client_login(easemob_client_t *p, const char *username, const char *password) {
    if (!p || !p->client) {
        return 1;
    }
    
    return p->client->Login(username, password);
}

void easemob_client_logout(easemob_client_t *p) {
    if (!p || !p->client) {
        return;
    }
    p->client->Logout();
}

int easemob_client_sendmessage(easemob_client_t *p, const char *receiver, const char *message) {
    if (!p || !p->client) {
        return 1;
    }
    return p->client->SendMessage(receiver, message);
}

void easemob_client_set_message_receive_callback(easemob_client *p, receive_message_callback_func func) {
    if (!p || !p->client) {
        return;
    }
}

/* vim: set expandtab shiftwidth=2 tabstop=2: */
