/*
 * �t�@�C����	: member.h
 * �@�\			: ����Ǘ����s��
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  
 */

#ifndef MEMBER_H
#define MEMBER_H

/* #define�}�N�� */
/* �o�b�t�@�T�C�Y */
/* WriteMemberFile */
#define WRITEMEMBERFILE_BUF_SIZE		100			/* �t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */

/* InputRegistMember */
#define INPUTREGISTMEMBER_BUF_SIZE		128			/* ��������͗p�o�b�t�@�T�C�Y */
	
/* GetMemberID */
#define GETMEMBERID_STR_BUF_SIZE		20			/* �����񑀍�p�o�b�t�@�T�C�Y */
#define GETMEMBERID_DATE_BUF_SIZE		10			/* �{���̓��t������i�[�p�o�b�t�@�T�C�Y */

/* DisplayRegistMember */
#define DISPLAYREGISTMEMBER_BUF_SIZE	16			/* ���t�t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */
	
/* DisplayMember */
#define DISPLAYMEMBER_BUF_SIZE			16			/* ���t�t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */

/* InputUpdateMember */
#define INPUTUPDATEMEMBER_BUF_SIZE		16			/* ���t�t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */

/* ������t�@�C�� */
#define MEMBER_FILE_NAME	"memberMST.dat"			/* ������t�@�C���� */

/* ������t�@�C���F���ږ��i�S�p��5�����ȓ��j */
#define MEMBER_ID_NAME		"���ID"				/* ���ID */
#define MEMBER_NAME_NAME	"���O"					/* ���O */
#define MEMBER_ADDR_NAME	"�Z��"					/* �Z�� */
#define MEMBER_TEL_NAME		"�d�b�ԍ�"				/* �d�b�ԍ� */
#define MEMBER_BIRTH_NAME	"���N����"				/* ���N���� */

/* ������t�@�C���F������̊e�����i�\���̃����o�[�̑傫���j */
#define MEMBER_ID_SIZE		12						/* ���ID */
#define MEMBER_NAME_SIZE	16						/* ���O */
#define MEMBER_ADDR_SIZE	60						/* �Z�� */
#define MEMBER_TEL_SIZE		12						/* �d�b�ԍ� */
#define MEMBER_BIRTH_SIZE	8						/* ���N���� */

/* ������t�@�C���F�����񃌃R�[�h���̐擪�ʒu */
#define MEMBER_ID_POS		0										/* ���ID */
#define MEMBER_NAME_POS		MEMBER_ID_POS + MEMBER_ID_SIZE			/* ���O */
#define MEMBER_ADDR_POS		MEMBER_NAME_POS + MEMBER_NAME_SIZE		/* �Z�� */
#define MEMBER_TEL_POS		MEMBER_ADDR_POS + MEMBER_ADDR_SIZE		/* �d�b�ԍ� */
#define MEMBER_BIRTH_POS	MEMBER_TEL_POS + MEMBER_TEL_SIZE		/* ���N���� */

/* ������t�@�C���F�����񃌃R�[�h�̃T�C�Y */
#define MEMBER_SIZE			MEMBER_BIRTH_POS + MEMBER_BIRTH_SIZE

/* struct�^�O��` */
/* ������ */
typedef struct member {
	char id[MEMBER_ID_SIZE+1];						/* ���ID */
	char name[MEMBER_NAME_SIZE+1];					/* ���O */
	char addr[MEMBER_ADDR_SIZE+1];					/* �Z�� */
	char tel[MEMBER_TEL_SIZE+1];					/* �d�b�ԍ� */
	char birth[MEMBER_BIRTH_SIZE+1];				/* ���N���� */
	struct member *next;							/* ���ȎQ�ƃ|�C���^ */
}MEMBER;

/* �֐��v���g�^�C�v�錾 */
extern int ReadMemberFile(MEMBER **member);
extern void FreeMemberList(void);
extern int WriteMemberFile(void);
extern int SearchMember(const char *id, MEMBER **m);
extern void ClearMemberBuffer(MEMBER *m);
extern int InputRegistMember(MEMBER *m);
extern void DisplayRegistMember(const MEMBER *m);
extern int RegistMember(const MEMBER *m);
extern void DisplayMember(const MEMBER *m);
extern int InputUpdateMember(MEMBER *m, MEMBER *mBuf);
extern int DeleteMember(const char *id);

#endif		/* end MEMBER_H */

