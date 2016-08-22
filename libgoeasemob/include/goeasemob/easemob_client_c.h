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

typedef void (*receive_message_callback_func)(const char* messages);

void easemob_client_new();
void easemob_client_free();

int easemob_client_init(const char *workpath, const char *appkey);
int easemob_client_login(const char *username, const char *password);
void easemob_client_logout();
int easemob_client_sendmessage(const char *receiver, const char *message);
void easemob_client_set_message_receive_callback(receive_message_callback_func func);

#ifdef __cplusplus
}
#endif

#endif /* _EASEMOB_CLIENT_C_H_ */

/* vim: set expandtab shiftwidth=2 tabstop=2: */
