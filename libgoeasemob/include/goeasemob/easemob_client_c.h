/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2016, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the Apache licence
 *
 **************************************************************/

#ifndef _EASEMOB_CLIENT_C_H_
#define _EASEMOB_CLIENT_C_H_

/**
 * 
 *
 * @file easemob_client_c.h
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Mon Aug 22 22:33:52 2016
 *
 **/

#ifdef __cplusplus
extern "C" {
#endif

#include <goeasemob/easemob_client.h>

typedef struct easemob_client {
    EasemobClient *client;
} easemob_client_t;

typedef void (*receive_message_callback_func)(const char** messages);

int easemob_client_new();
int easemob_client_free(easemob_client_t *p);

int easemob_client_init(const char *work_path, const char *appkey);
int easemob_client_login(const char *username, const char *password);
int easemob_client_logout();
int easemob_client_sendmessage(const char *receiver, const char *message);
int easemob_client_set_message_receive_callback(receive_message_callback_func func);

#ifdef __cplusplus
}
#endif

#endif /* _EASEMOB_CLIENT_C_H_ */

/* vim: set expandtab shiftwidth=2 tabstop=2: */
