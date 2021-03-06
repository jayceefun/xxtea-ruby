/**********************************************************\
|                                                          |
| ruby_xxtea.c                                             |
|                                                          |
| XXTEA encryption algorithm library for Ruby.             |
|                                                          |
| Encryption Algorithm Authors:                            |
|      David J. Wheeler                                    |
|      Roger M. Needham                                    |
|                                                          |
| Code Authors: Chen fei <cf850118@163.com>                |
|               Ma Bingyao <mabingyao@gmail.com>           |
| LastModified: Feb 11, 2016                               |
|                                                          |
\**********************************************************/

#include <ruby.h>
#include "xxtea.h"

VALUE rb_encrypt(VALUE mod, VALUE data, VALUE key) {
	void * result;
	VALUE retval;
	size_t data_len, out_len;

	if (data == Qnil) return rb_str_new(0,0);

	Check_Type(data, T_STRING);
	Check_Type(key, T_STRING);

	data_len = RSTRING_LEN(data);

	if (data_len == 0) return data;

	result = xxtea_encrypt(RSTRING_PTR(data), data_len, RSTRING_PTR(key), &out_len);

	if (result == NULL) return rb_str_new(0,0);

	retval = rb_str_new((const char *)result, out_len);

	free(result);

	return retval;
}

VALUE rb_decrypt(VALUE mod, VALUE data, VALUE key) {
	void * result;
	VALUE retval;
	size_t data_len, out_len;

	if (data == Qnil) return rb_str_new(0,0);

	Check_Type(data, T_STRING);
	Check_Type(key, T_STRING);

	data_len = RSTRING_LEN(data);

	if (data_len == 0) return data;

	result = xxtea_decrypt(RSTRING_PTR(data), data_len, RSTRING_PTR(key), &out_len);

	if (result == NULL) return rb_str_new(0,0);

	retval = rb_str_new((const char *)result, out_len);

	free(result);

	return retval;
}

void Init_xxtea() {
    VALUE XXTEA = rb_define_module("XXTEA");
    rb_define_singleton_method(XXTEA, "encrypt", rb_encrypt, 2);
    rb_define_singleton_method(XXTEA, "decrypt", rb_decrypt, 2);
}
