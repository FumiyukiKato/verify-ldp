#!/usr/bin/zsh

export RA_SPID=EBF7AE35A2AB286FE81D853BC0968B25

SCRIPT_DIR=$(\cd $(dirname $0); pwd)
export SERVER_KEY="${SCRIPT_DIR}/server.key"
export SERVER_CRT="${SCRIPT_DIR}/server.crt"
export CA="${SCRIPT_DIR}/Intel_SGX_Attestation_RootCA.pem"
