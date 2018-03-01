#include <stdio.h>
#include <sgx_urts.h>
#include "enclave_u.h"

static sgx_enclave_id_t enclave_id;

static int load_save_launch_token (const char *path, sgx_launch_token_t *launch_token, int is_save)
{
	FILE *fp = fopen(path, is_save ? "wb" : "rb");
	if (fp == NULL)
		return 1;
	size_t size;
	if (is_save)
		size = fwrite(launch_token, sizeof(sgx_launch_token_t), 1, fp);
	else
		size = fread(launch_token, sizeof(sgx_launch_token_t), 1, fp);
	fclose(fp);
	return size != sizeof(launch_token);
}

static int do_init ()
{
	sgx_status_t retval;
	sgx_launch_token_t launch_token;
	int launch_token_updated;

	if (load_save_launch_token("enclave.token", &launch_token, 0))
		memset(&launch_token, 0, sizeof(sgx_launch_token_t));

	retval = sgx_create_enclave("enclave.signed.so", SGX_DEBUG_FLAG, &launch_token, &launch_token_updated, &enclave_id, NULL);
	if (retval != SGX_SUCCESS) {
		printf("SGX error code: 0x%x\n", retval);
		return 1;
	}

	if (launch_token_updated)
		load_save_launch_token("enclave.token", &launch_token, 1);
}

static void do_compute ()
{
	sgx_status_t retval;
	int sum;

	retval = add(enclave_id, &sum, 8, 15);
	if (retval != SGX_SUCCESS)
		printf("SGX error code: 0x%x\n", retval);
	else
		printf("Succeed: %d + %d = %d!\n", 8, 15, sum);
}

static void do_fini ()
{
	sgx_status_t retval = sgx_destroy_enclave(enclave_id);
	if (retval != SGX_SUCCESS)
		printf("SGX error code: 0x%x\n", retval);
}

int main (int argc, char const *argv[])
{
	if (do_init())
		return 1;
	do_compute();
	do_fini();
	return 0;
}
