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
 * @file easemob_test.go
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Tue Aug 23 00:15:19 2016
 *
 **/

package easemob

import (
	"fmt"
	"testing"
)

func TestAll(t *testing.T) {
	c := easemob.NewEasemobClient()
	c.Init("./", "renrenche#testapp")
	c.Login("test1", "test")
}
