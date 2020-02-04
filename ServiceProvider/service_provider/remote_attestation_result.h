#ifndef _REMOTE_ATTESTATION_RESULT_H_
#define _REMOTE_ATTESTATION_RESULT_H_

#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define SAMPLE_MAC_SIZE             16  /* Message Authentication Code*/
/* - 16 bytes*/
typedef uint8_t                     sample_mac_t[SAMPLE_MAC_SIZE];

#ifndef SAMPLE_FEBITSIZE
#define SAMPLE_FEBITSIZE        256
#endif

#define SAMPLE_NISTP256_KEY_SIZE    (SAMPLE_FEBITSIZE/ 8 /sizeof(uint32_t))

typedef struct sample_ec_sign256_t {
    uint32_t x[SAMPLE_NISTP256_KEY_SIZE];
    uint32_t y[SAMPLE_NISTP256_KEY_SIZE];
} sample_ec_sign256_t;

#pragma pack(push,1)

#define SAMPLE_SP_TAG_SIZE          16

typedef struct sp_aes_gcm_data_t {
    uint32_t        payload_size;       /*  0: Size of the payload which is*/
    /*     encrypted*/
    uint8_t         reserved[12];       /*  4: Reserved bits*/
    uint8_t         payload_tag[SAMPLE_SP_TAG_SIZE];
    /* 16: AES-GMAC of the plain text,*/
    /*     payload, and the sizes*/
    uint8_t         payload[];          /* 32: Ciphertext of the payload*/
    /*     followed by the plain text*/
} sp_aes_gcm_data_t;


#define ISVSVN_SIZE 2
#define PSDA_SVN_SIZE 4
#define GID_SIZE 4
#define PSVN_SIZE 18

/* @TODO: Modify at production to use the values specified by an Production*/
/* attestation server API*/
typedef struct ias_platform_info_blob_t {
    uint8_t sample_epid_group_status;
    uint16_t sample_tcb_evaluation_status;
    uint16_t pse_evaluation_status;
    uint8_t latest_equivalent_tcb_psvn[PSVN_SIZE];
    uint8_t latest_pse_isvsvn[ISVSVN_SIZE];
    uint8_t latest_psda_svn[PSDA_SVN_SIZE];
    uint8_t performance_rekey_gid[GID_SIZE];
    sample_ec_sign256_t signature;
} ias_platform_info_blob_t;


typedef struct sample_ra_att_result_msg_t {
    ias_platform_info_blob_t    platform_info_blob;
    sample_mac_t                mac;    /* mac_smk(attestation_status)*/
    sp_aes_gcm_data_t           secret;
} sample_ra_att_result_msg_t;

typedef struct sp_private_data_t {
    uint8_t data;
} sp_private_data_t;

typedef struct sp_open_data_t {
    double privacy_parameter;
} sp_open_data_t;

typedef struct private_data_msg_t {
    sp_open_data_t     open_data;
    sp_private_data_t  private_data;
    sp_aes_gcm_data_t  secret;
} private_data_msg_t;

#pragma pack(pop)

#ifdef  __cplusplus
}
#endif

#endif
