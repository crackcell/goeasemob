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

typedef void (*receive_message_callback_func)(const char* messages);

void easemob_client_new();
void easemob_client_free();

int easemob_client_init(const char *workpath, const char *appkey);
int easemob_client_login(const char *username, const char *password);
void easemob_client_logout();
int easemob_client_sendmessage(const char *receiver, const char *message);
void easemob_client_set_message_receive_callback(receive_message_callback_func func);

#endif /* _GOEASEMOB_WRAPPER_H_ */

/* vim: set expandtab shiftwidth=2 tabstop=2: */
