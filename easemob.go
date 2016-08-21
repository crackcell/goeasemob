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
#include <stdio.h>
#include <stdlib.h>
#include <gonlpir.h>
#cgo linux CFLAGS: -DOS_LINUX
#cgo linux LDFLAGS: -lNLPIR
*/

import "C"

//===================================================================
// Public APIs
//===================================================================

type EasemobClient struct {
	username string
	password string
}

//===================================================================
// Private
//===================================================================
