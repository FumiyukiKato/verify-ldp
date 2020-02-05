#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H

#include <string>

using namespace std;

namespace Settings {
    static int rh_port          = 22222;
    static string rh_host       = "localhost";

    static string server_crt    = std::getenv("SERVER_CRT"); // certificate for the HTTPS connection between the SP and the App
    static string server_key    = std::getenv("SERVER_KEY"); // private key for the HTTPS connection

    static string spid          = std::getenv("RA_SPID"); // SPID provided by Intel after registration for the IAS service
    static const char *ias_crt  = std::getenv("CA"); // location of a trusted Attestation Report Signing CA Certificate
    static string ias_url       = "https://api.trustedservices.intel.com/sgx/dev"; // development, for production can use "https://api.trustedservices.intel.com/sgx";
    static string api_version   = "/attestation/v3/";

    static string primary_key   = std::getenv("AS_PRIMARY_KEY");
    static string secondary_key = std::getenv("AS_SECONDARY_KEY");

    static string client_private_data_path = "/home/fumiyuki/workspace/verify-ldp/private.dat";
    static string client_privacy_path      = "/home/fumiyuki/workspace/verify-ldp/privacy.dat";
    static string encalve_measurement_path = "/home/fumiyuki/workspace/verify-ldp/mrenclave.dat";
    static string signer_measurement_path = "/home/fumiyuki/workspace/verify-ldp/mrsigner.dat";
}

#endif
