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
 * @file easemob.go
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Sun Aug 21 13:56:22 2016
 *
 **/

package goeasemob

/*
#cgo linux CFLAGS: -DOS_LINUX -I./libgoeasemob/output/include
#cgo linux LDFLAGS: -L./libgoeasemob/output/lib -leasemob -lgoeasemob -lstdc++

#include <stdio.h>
#include <stdlib.h>
#include <goeasemob/easemob_client_c.h>
*/
import "C"
import "unsafe"

//===================================================================
// Public APIs
//===================================================================

type EasemobClient interface {
	Init(workpath, appkey string)
	Login(username, pasword string)
	Logout()
	SendMessage(message string)
	SetReceiveMessageCallback()
}

// GetEasemobClient Create a new easemob client instance
func GetEasemobClient() EasemobClient {
	return instance
}

//===================================================================
// Private
//===================================================================

type cEasemobClient C.struct_easemob_client

type easemobClient struct {
	rawClient *cEasemobClient
	username  string
	password  string
}

// Global static instance
var instance = &easemobClient{}

func (p *easemobClient) Init(workpath, appkey string) {
	workpathCStr := C.CString(workpath)
	defer C.free(unsafe.Pointer(workpathCStr))

	appkeyCStr := C.CString(appkey)
	defer C.free(unsafe.Pointer(appkeyCStr))

	client := C.easemob_client_new()
}

func (p *easemobClient) Login(username, password string) {
	p.username = username
	p.password = password
}

func (p *easemobClient) Logout() {

}

func (p *easemobClient) SendMessage(message string) {

}

func (p *easemobClient) SetReceiveMessageCallback() {

}
