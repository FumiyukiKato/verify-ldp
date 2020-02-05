# verify-ldp
This repository is forked from this briliant remote attestation sample code https://github.com/svartkanin/linux-sgx-remoteattestation.


You register Intel Attestation Service and get nesessary information to commuticate with IAS.

You have to set following env variables.

```c++
static string server_crt    = std::getenv("SERVER_CRT"); // certificate for the HTTPS connection between the SP and the App
static string server_key    = std::getenv("SERVER_KEY"); // private key for the HTTPS connection
static string spid          = std::getenv("RA_SPID"); // SPID provided by Intel after registration for the IAS service
static const char *ias_crt  = std::getenv("CA"); // location of a trusted Attestation Report Signing CA Certificate
static string primary_key   = std::getenv("AS_PRIMARY_KEY"); // IAS api key
static string secondary_key = std::getenv("AS_SECONDARY_KEY");
```

This supports IAS v3 API and v2.8 sdk.
