# verify-ldp
This repository is based on this brilliant remote attestation sample code https://github.com/svartkanin/linux-sgx-remoteattestation.
So, you should check some dependencies, but the repository maybe does not support SDK and API of latest version.

## description

Overview, Client(Service Provider or ISV) sends their private data to Server(Service Provider or ISV) on TLS session.

Client verify Server's runtime and program integirity using [remote attestation](https://software.intel.com/en-us/articles/code-sample-intel-software-guard-extensions-remote-attestation-end-to-end-example).

**branch: `master` and `server-is-sp` is mode where Client is ISV with TEE and Server is SP without TEE.** 

Client send encrypted private data in SGX to Server, data is perturbed with Randomized Response in TEE at client side.

**And branch: `client-is-sp` is mode where Server is ISV with TEE and Client is SP without TEE.** 

Client send private data to Server through secure channel with SGX at server side, data is perturbed with Randomized Response in SGX at server side.

## execution
Supporting IAS v3 API and v2.8 sgxsdk
I use my fork sdk https://github.com/FumiyukiKato/linux-sgx

You have to set up your processor with Intel SGX and sgxsdk and register Intel Attestation Service and get nesessary information to commuticate with IAS.


Set following env variables.

```c++
static string server_crt    = std::getenv("SERVER_CRT"); // certificate for the HTTPS connection between the SP and the App
static string server_key    = std::getenv("SERVER_KEY"); // private key for the HTTPS connection
static string spid          = std::getenv("RA_SPID"); // SPID provided by Intel after registration for the IAS service
static const char *ias_crt  = std::getenv("CA"); // location of a trusted Attestation Report Signing CA Certificate
static string primary_key   = std::getenv("AS_PRIMARY_KEY"); // IAS api key
static string secondary_key = std::getenv("AS_SECONDARY_KEY");
```

You have to set mrenclave value of `sgx_report_t` and mrsigner value because they should be verified.

But I dont know how to get them without executing actually at once.

```c++
static string encalve_measurement_path = "/home/fumiyuki/workspace/verify-ldp/mrenclave.dat";
static string signer_measurement_path = "/home/fumiyuki/workspace/verify-ldp/mrsigner.dat";
```

bulid
```
./make
```

server
```
./run-server
```

client
```
./run-client
```
