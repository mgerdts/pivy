/* $OpenBSD: authfd.h,v 1.41 2017/06/28 01:09:22 djm Exp $ */

/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 * Functions to interface with the SSH_AUTHENTICATION_FD socket.
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 */

#ifndef AUTHFD_H
#define AUTHFD_H

#define SSH_AUTHSOCKET_ENV_NAME "SSH_AUTH_SOCK"

/* List of identities returned by ssh_fetch_identitylist() */
struct ssh_identitylist {
	size_t nkeys;
	struct sshkey **keys;
	char **comments;
};

struct ssh_x509chain {
	size_t ncerts;
	u_char **certs;
	size_t *certlen;
};

int	ssh_get_authentication_socket(int *fdp);

int	ssh_fetch_identitylist(int sock, struct ssh_identitylist **idlp);
void	ssh_free_identitylist(struct ssh_identitylist *idl);

int	ssh_request_reply(int sock, struct sshbuf *request, struct sshbuf *reply);

int	ssh_agent_sign(int sock, const struct sshkey *key,
	    u_char **sigp, size_t *lenp,
	    const u_char *data, size_t datalen, const char *alg, u_int compat);

void	ssh_free_x509chain(struct ssh_x509chain *chain);
int	ssh_agent_get_x509(int sock, const struct sshkey *key,
    struct ssh_x509chain **pchain);

/* Messages for the authentication agent connection. */
#define SSH_AGENTC_REQUEST_RSA_IDENTITIES	1
#define SSH_AGENT_RSA_IDENTITIES_ANSWER		2
#define SSH_AGENTC_RSA_CHALLENGE		3
#define SSH_AGENT_RSA_RESPONSE			4
#define SSH_AGENT_FAILURE			5
#define SSH_AGENT_SUCCESS			6
#define SSH_AGENTC_ADD_RSA_IDENTITY		7
#define SSH_AGENTC_REMOVE_RSA_IDENTITY		8
#define SSH_AGENTC_REMOVE_ALL_RSA_IDENTITIES	9

/* private OpenSSH extensions for SSH2 */
#define SSH2_AGENTC_REQUEST_IDENTITIES		11
#define SSH2_AGENT_IDENTITIES_ANSWER		12
#define SSH2_AGENTC_SIGN_REQUEST		13
#define SSH2_AGENT_SIGN_RESPONSE		14
#define SSH2_AGENTC_ADD_IDENTITY		17
#define SSH2_AGENTC_REMOVE_IDENTITY		18
#define SSH2_AGENTC_REMOVE_ALL_IDENTITIES	19

/* smartcard */
#define SSH_AGENTC_ADD_SMARTCARD_KEY		20
#define SSH_AGENTC_REMOVE_SMARTCARD_KEY		21

/* lock/unlock the agent */
#define SSH_AGENTC_LOCK				22
#define SSH_AGENTC_UNLOCK			23

/* add key with constraints */
#define SSH_AGENTC_ADD_RSA_ID_CONSTRAINED	24
#define SSH2_AGENTC_ADD_ID_CONSTRAINED		25
#define SSH_AGENTC_ADD_SMARTCARD_KEY_CONSTRAINED 26
#define	SSH2_AGENTC_EXTENSION			27

#define	SSH2_AGENT_EXT_FAILURE			28

#define SSH2_AGENTC_REQUEST_X509		250
#define SSH2_AGENT_X509_RESPONSE		251
#define SSH2_AGENTC_REQUEST_ECDH		252
#define SSH2_AGENT_ECDH_RESPONSE		253

#define	SSH_AGENT_CONSTRAIN_LIFETIME		1
#define	SSH_AGENT_CONSTRAIN_CONFIRM		2

/* extended failure messages */
#define SSH2_AGENT_FAILURE			30

/* additional error code for ssh.com's ssh-agent2 */
#define SSH_COM_AGENT2_FAILURE			102

#define	SSH_AGENT_OLD_SIGNATURE			0x01
#define	SSH_AGENT_RSA_SHA2_256			0x02
#define	SSH_AGENT_RSA_SHA2_512			0x04

#endif				/* AUTHFD_H */
