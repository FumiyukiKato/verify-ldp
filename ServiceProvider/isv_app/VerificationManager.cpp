#include "VerificationManager.h"
#include "../GeneralSettings.h"

#include  <iomanip>

using namespace util;
using namespace std;

VerificationManager* VerificationManager::instance = NULL;

VerificationManager::VerificationManager() {
    this->nm = NetworkManagerServer::getInstance(Settings::rh_port);
    this->ws = WebService::getInstance();
    this->ws->init();
    this->sp = new ServiceProvider(this->ws);
}


VerificationManager::~VerificationManager() {}


VerificationManager* VerificationManager::getInstance() {
    if (instance == NULL) {
        instance = new VerificationManager();
    }

    return instance;
}


int VerificationManager::init() {
    if (this->sp) {
        delete this->sp;
        this->sp = new ServiceProvider(this->ws);
    }

    this->nm->Init();
    this->nm->connectCallbackHandler([this](string v, int type) {
        return this->incomingHandler(v, type);
    });
}


void VerificationManager::start() {
    this->nm->startService();
    Log("Remote attestation done");
}


string VerificationManager::handleMSG0(Messages::MessageMsg0 msg) {
    Log("MSG0 received");

    if (msg.status() != TYPE_TERMINATE) {
        uint32_t extended_epid_group_id = msg.epid();
        int ret = this->sp->sp_ra_proc_msg0_req(extended_epid_group_id);

        if (ret == 0) {
            msg.set_status(TYPE_OK);
            return nm->serialize(msg);
        }
    } else {
        Log("Termination received!");
    }

    return "";
}


string VerificationManager::handleMSG1(Messages::MessageMSG1 msg1) {
    Log("MSG1 received");

    Messages::MessageMSG2 msg2;
    msg2.set_type(RA_MSG2);

    int ret = this->sp->sp_ra_proc_msg1_req(msg1, &msg2);

    if (ret != 0) {
        Log("Error, processing MSG1 failed");
    } else {
        Log("MSG1 processed correctly and MSG2 created");
        return nm->serialize(msg2);
    }

    return "";
}


string VerificationManager::handleMSG3(Messages::MessageMSG3 msg) {
    Log("MSG3 received");

    Messages::AttestationMessage att_msg;
    att_msg.set_type(RA_ATT_RESULT);

    int ret = this->sp->sp_ra_proc_msg3_req(msg, &att_msg);

    if (ret == -1) {
        Log("Error, processing MSG3 failed");
    } else {
        Log("MSG3 processed correctly and attestation result created");
        return nm->serialize(att_msg);
    }

    return "";
}


string VerificationManager::handleAppAttOk(Messages::InitialMessage msg) {
    Log("APP attestation result received");
    Log("Sending Private Data");

    Messages::SecretMessage sec_msg;
    sec_msg.set_type(RANDOM_RESPONSE);

    int ret = this->sp->proc_private_data(msg, &sec_msg);
    if (ret == -1) {
        Log("Error, failed to prepare private data");
    } else {
        Log("private data is properly encrypted");
        return nm->serialize(sec_msg);
    }

    return "";
}

string VerificationManager::handleRROk(Messages::InitialMessage msg) {
    Log("Randomized Response is OK");

    return "";
}


string VerificationManager::handleInitRequest(Messages::InitialMessage init_msg) {
    Log("Accept initial request and request Remote Attestation");

    Messages::InitialMessage msg;
    msg.set_type(RA_VERIFICATION);

    return nm->serialize(msg);
}

string VerificationManager::createInitMsg(int type, string msg) {
    Messages::InitialMessage init_msg;
    init_msg.set_type(type);
    init_msg.set_size(msg.size());

    return nm->serialize(init_msg);
}


vector<string> VerificationManager::incomingHandler(string v, int type) {
    vector<string> res;

    string s;
    bool ret;

    switch (type) {
    case INIT_REQUEST: {
        Messages::InitialMessage init_msg;
        ret = init_msg.ParseFromString(v);
        if (ret && (init_msg.type() == INIT_REQUEST)) {
            s = this->handleInitRequest(init_msg);
            res.push_back(to_string(RA_VERIFICATION));
        }
    }
    break;
    case RA_MSG0: {
        Messages::MessageMsg0 msg0;
        ret = msg0.ParseFromString(v);
        if (ret && (msg0.type() == RA_MSG0)) {
            s = this->handleMSG0(msg0);
            res.push_back(to_string(RA_MSG0));
        }
    }
    break;
    case RA_MSG1: {
        Messages::MessageMSG1 msg1;
        ret = msg1.ParseFromString(v);
        if (ret && (msg1.type() == RA_MSG1)) {
            s = this->handleMSG1(msg1);
            res.push_back(to_string(RA_MSG2));
        }
    }
    break;
    case RA_MSG3: {
        Messages::MessageMSG3 msg3;
        ret = msg3.ParseFromString(v);
        if (ret && (msg3.type() == RA_MSG3)) {
            s = this->handleMSG3(msg3);
            res.push_back(to_string(RA_ATT_RESULT));
        }
    }
    break;
    case RA_APP_ATT_OK: {
        Messages::InitialMessage ok_msg;
        ret = ok_msg.ParseFromString(v);
        if (ret) {
            if (ok_msg.type() == RA_APP_ATT_OK) {
                s = this->handleAppAttOk(ok_msg);
                res.push_back(to_string(RANDOM_RESPONSE));
            }
        }
    }
    break;
    case RANDOM_RESPONSE_OK: {
        Messages::InitialMessage ok_msg;
        ret = ok_msg.ParseFromString(v);
        if (ret) {
            if (ok_msg.type() == RANDOM_RESPONSE_OK) {
                this->handleRROk(ok_msg);
            }
        }
    }
    break;
    default:
        Log("Unknown type: %d", type, log::error);
        break;
    }

    res.push_back(s);

    return res;
}




















