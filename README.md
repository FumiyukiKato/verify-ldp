# verify-ldp
This repository is based on this briliant remote attestation sample code https://github.com/svartkanin/linux-sgx-remoteattestation.

## description

Overview, Client(Service Provider) sends their private data to Server(ISV) on TLS session.

Client verify Server's runtime and program integirity using [remote attestation](https://software.intel.com/en-us/articles/code-sample-intel-software-guard-extensions-remote-attestation-end-to-end-example).

Client send encrypted private data to Server, and in SGX of Server side, data is perturbed with Randomized Response.

**That is more important model I think.**

**And branch: `server-is-sp` is mode where Client is ISV with TEE and Server is SP without TEE.** 

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
