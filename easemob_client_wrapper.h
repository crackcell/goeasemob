/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2016, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _GOEASEMOB_WRAPPER_H_
#define _GOEASEMOB_WRAPPER_H_

/**
 * 
 *
 * @file goeasemob_wrapper.h
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Tue Aug 23 19:13:38 2016
 *
 **/

#include "easemob_client.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*receive_message_callback_func)(const char* messages);

typedef easemob_client {
    EasemobClient *client;
} easemob_client_t;

easemob_client_t* easemob_client_new();
void easemob_client_free(easemob_client *p);

int easemob_client_init(easemob_client *p, const char *workpath, const char *appkey);
int easemob_client_login(easemob_client *p, const char *username, const char *password);
void easemob_client_logout(easemob_client *p);
int easemob_client_sendmessage(easemob_client *p, const char *receiver, const char *message);
void easemob_client_set_message_receive_callback(easemob_client *p, receive_message_callback_func func);

#ifdef __cplusplus
}
#endif

#endif /* _GOEASEMOB_WRAPPER_H_ */

/* vim: set expandtab shiftwidth=2 tabstop=2: */
