#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H

#include <string>

using namespace std;

namespace Settings {
    static int rh_port = 22222;
    static string rh_host = "localhost";

    static string server_crt = std::getenv("SERVER_CRT"); //certificate for the HTTPS connection between the SP and the App
    static string server_key = std::getenv("SERVER_KEY"); //private key for the HTTPS connection

    static string spid = std::getenv("RA_SPID"); //SPID provided by Intel after registration for the IAS service
    static const char *ias_crt = std::getenv("CA"); //location of the certificate send to Intel when registring for the IAS
    static string ias_url = "https://test-as.sgx.trustedservices.intel.com:443/attestation/sgx/v3/";
    // static string ias_url = "https://api.trustedservices.intel.com/sgx/dev/";
}

#endif
