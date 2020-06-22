/*
 * �t�@�C����	: member.c
 * �@�\			: ����Ǘ����s��
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  2012/02/14 V02L1
 */

 /* �w�b�_�[�̎�荞�� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "menu.h"
#include "member.h"

/* static�ϐ��錾 */
static MEMBER *root = NULL;		/* �����񃊃X�g�̐擪�m�[�h�Q�Ɨp */

/* static�֐��錾 */
static void CreateMemberList(MEMBER **member);
static int GetMemberID(char *id);

/*
 * �֐���			: int ReadMemberFile(MEMBER **member)
 * �@�\				: ����������ID���Ƀ��X�g�\���ɓǂݍ���
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: MEMBER **member:�ǂݍ��񂾉�����̐擪�m�[�h�̃A�h���X
 * �߂�l			: int	:TRUE
 * ���L����			: �Ȃ�
 */
int ReadMemberFile(MEMBER **member)
{
	int retVal = TRUE;
	MEMBER *newone;								/* ������̒ǉ��m�[�h�Q�Ɨp */
	MEMBER *target;								/* �^�[�Q�b�g�m�[�h�p */
	FILE* fp;									/* �t�@�C���|�C���^ */
	char buf[MEMBER_SIZE + REC_DELIMITER_SIZE];	/* �t�@�C���Ǎ��̈�i1���R�[�h�T�C�Y���]�T����������j */
	errno_t error;

	/* ������t�@�C����ǂݍ��� */
	error = fopen_s(&fp, MEMBER_FILE_NAME, "r");
	if (error != 0) {
		printf("\n������t�@�C��������܂���B�������I�����܂��B\n");
		exit(EXIT_FAILURE);
	}

	/* �t�@�C���ǂݍ��݂̂��߂̑O���� */
	CreateMemberList(&target);
	*member = root;
	memset(buf, '\0', sizeof(buf));								/* �t�@�C���ǂݍ��ݗ̈���N���A */

	/* �t�@�C����EOF�܂œǂݍ��� */
	while (fgets(buf, sizeof(buf), fp) != NULL) {				/* �t�@�C���I���܂œǂݍ��� */

		/* �V���ȃm�[�h��ǉ����f�[�^���i�[���� */
		if ((newone = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {	/* �m�[�h���쐬 */
			printf("���I�������̎擾�Ɏ��s���܂����B\n");
			exit(EXIT_FAILURE);
		}

		/* ��������m�[�h�Ɋi�[���� */
		strncpy_s(newone->id, MEMBER_ID_SIZE + 1, &buf[MEMBER_ID_POS], _TRUNCATE);
		strncpy_s(newone->name, MEMBER_NAME_SIZE + 1, &buf[MEMBER_NAME_POS], _TRUNCATE);
		strncpy_s(newone->addr, MEMBER_ADDR_SIZE + 1, &buf[MEMBER_ADDR_POS], _TRUNCATE);
		strncpy_s(newone->tel, MEMBER_TEL_SIZE + 1, &buf[MEMBER_TEL_POS], _TRUNCATE);
		strncpy_s(newone->birth, MEMBER_BIRTH_SIZE + 1, &buf[MEMBER_BIRTH_POS], _TRUNCATE);

		/* �����̋󔒂��폜���� */
		TrimSpace(newone->id);
		TrimSpace(newone->name);
		TrimSpace(newone->addr);
		TrimSpace(newone->tel);
		TrimSpace(newone->birth);

		/* ID�ŏ����ɂȂ�悤�Ƀm�[�h��ǉ����� */
		target = root;											/* �^�[�Q�b�g��擪�ɐݒ� */
		while (TRUE) {
			/* ���̃m�[�h������Ȃ�΁AID���`�F�b�N���� */
			if (target->next != NULL) {
				/* �ǉ��m�[�h��ID���������Ȃ�΁A�^�[�Q�b�g�̌��Ƀm�[�h��ǉ����ďI������ */
				if (strncmp(newone->id, target->next->id, MEMBER_ID_SIZE) < 0) {
					newone->next = target->next;
					target->next = newone;
					break;
				}
				else {
					target = target->next;						/* �^�[�Q�b�g���X�V���Ď��̃m�[�h�� */
				}
			}
			else {
				/* �V�����m�[�h�����X�g�̖����ɒǉ����ďI������ */
				newone->next = NULL;
				target->next = newone;
				break;
			}
		}
	}
	fclose(fp);
	return retVal;
}

/*
 * �֐���			: static void CreateMemberList(MEMBER **member)
 * �@�\				: �����񃊃X�g������������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: MEMBER **member	:�_�~�[�m�[�h�̃A�h���X
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
static void CreateMemberList(MEMBER **member)
{
	/* �_�~�[�m�[�h���쐬���� */
	FreeMemberList();
	if ((root = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}
	root->next = NULL;
	*member = root;
}

/*
 * �֐���			: void FreeMemberList(void)
 * �@�\				: �����񃊃X�g������������������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void FreeMemberList(void)
{
	MEMBER *temp;

	while (root != NULL) {
		temp = root;
		root = root->next;
		free(temp);
	}
}

/*
 * �֐���			: int WriteMemberFile(void)
 * �@�\				: �����񃊃X�g���t�@�C���ɏ�������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i�������ݐ���j���TRUE��Ԃ�
 * ���L����			: ����R�[�h�Ń\�[�g���Ȃ����荞��
 */
int WriteMemberFile(void)
{
	int retVal = TRUE;
	FILE* fp;								/* �t�@�C���|�C���^ */
	MEMBER *target;							/* �^�[�Q�b�g�m�[�h�p */
	char form[WRITEMEMBERFILE_BUF_SIZE];	/* �t�H�[�}�b�g�p������ */
	errno_t error;

	/* �t�@�C�����I�[�v������ */
	error = fopen_s(&fp, MEMBER_FILE_NAME, "w");
	if (error != 0) {
		printf("\n������t�@�C���ɏ������݂ł��܂���B�������I�����܂��B\n");
		exit(EXIT_FAILURE);
	}

	/* fprintf�̃t�H�[�}�b�g��ݒ肷�� */
	sprintf_s(form, WRITEMEMBERFILE_BUF_SIZE, "%%-%ds%%-%ds%%-%ds%%-%ds%%-%ds\n",
		MEMBER_ID_SIZE,
		MEMBER_NAME_SIZE,
		MEMBER_ADDR_SIZE,
		MEMBER_TEL_SIZE,
		MEMBER_BIRTH_SIZE
	);

	/* �����񃊃X�g���t�@�C���ɏ������� */
	target = root;
	while (target->next != NULL) {
		/* ���X�g�̓��e���������� */
		target = target->next;
		fprintf(fp, form,
			target->id,
			target->name,
			target->addr,
			target->tel,
			target->birth
		);
	}
	fclose(fp);
	return retVal;
}

/*
 * �֐���			: int SearchMember(const char *id, MEMBER **m)
 * �@�\				: �yD-1111�z�w�肵��ID�̉�������擾����
 * ���̓p�����[�^	: const char *id	:����������ID
 * �o�̓p�����[�^	: MEMBER **m		:�������ꂽ������m�[�h�ւ̃|�C���^
 * �߂�l			: int	:TRUE�i��������擾�j/FALSE�i�w�肵�����ID���Ȃ��j
 * ���L����			: �Ȃ�
 */
int SearchMember(const char *id, MEMBER **m)
{
	int retVal = FALSE;
	MEMBER *target;				/* �����^�[�Q�b�g�m�[�h�p */

	target = root;
	while (target->next != NULL) {
		target = target->next;
		if (strncmp(target->id, id, MEMBER_ID_SIZE) == 0) {
			*m = target;		/* �q�b�g�����f�[�^�̃A�h���X��߂�l�ɐݒ� */
			retVal = TRUE;
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: void ClearMemberBuffer(MEMBER *m)
 * �@�\				: �yD-1122�z������o�b�t�@���N���A����
 * ���̓p�����[�^	: MEMBER *m	:������ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void ClearMemberBuffer(MEMBER *m)
{
	m->id[0] = '\0';
	m->name[0] = '\0';
	m->addr[0] = '\0';
	m->tel[0] = '\0';
	m->birth[0] = '\0';
	m->next = NULL;
}

/*
 * �֐���			: int InputRegistMember(MEMBER *m)
 * �@�\				: �yD-1122�z�V�K�ɓo�^������������͂���
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: MEMBER *m	:���͂���������ւ̃|�C���^
 * �߂�l			: int	:TRUE�i�V�K���ID�擾�j/FALSE�i�V�K���ID�擾�ł��Ȃ��j
 * ���L����			: �Ȃ�
 */
int InputRegistMember(MEMBER *m)
{
	int retVal;
	char buf[INPUTREGISTMEMBER_BUF_SIZE];				/* ������p�o�b�t�@ */
	char id[MEMBER_ID_SIZE + STRING_TERMINATOR_SIZE];		/* ���ID�p������ */

	printf("%-12s> ", MEMBER_NAME_NAME);
	buf[0] = '\0';
	while (strlen(buf) == 0) {
		GetStr(buf, MEMBER_NAME_SIZE);
	}
	strncpy_s(m->name, MEMBER_NAME_SIZE + 1, buf, _TRUNCATE);

	printf("%-12s> ", MEMBER_ADDR_NAME);
	buf[0] = '\0';
	while (strlen(buf) == 0) {
		GetStr(buf, MEMBER_ADDR_SIZE);
	}
	strncpy_s(m->addr, MEMBER_ADDR_SIZE + 1, buf, _TRUNCATE);

	printf("%-12s> ", MEMBER_TEL_NAME);
	buf[0] = '\0';
	while (strlen(buf) == 0) {
		GetStr(buf, MEMBER_TEL_SIZE);
	}
	strncpy_s(m->tel, MEMBER_TEL_SIZE + 1, buf, _TRUNCATE);

	InputYMD(buf);
	strncpy_s(m->birth, MEMBER_BIRTH_SIZE + 1, buf, _TRUNCATE);



	/* ���ID��V�K�ݒ肷�� */
	if (GetMemberID(id) == FALSE) {					/* ID�̍ő�l�𒴂����ꍇ */
		printf("���ID�̎擾�Ɏ��s���܂����B\n");
		retVal = FALSE;
	}
	else {
		/* ID���擾�ł����ꍇ */
		strncpy_s(m->id, MEMBER_ID_SIZE + 1, id, _TRUNCATE);
		retVal = TRUE;
	}
	return retVal;
}

/*
 * �֐���			: static int GetMemberID(char *id)
 * �@�\				: �yD-1122�z�V�K�̉��ID���擾����
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: char *id	:�V�K�Ɏ擾�������ID
 * �߂�l			: int	:TRUE�i�V�K���ID���擾�j/FALSE�i�V�K���ID���擾�ł��Ȃ��j
 * ���L����			: "99"+���t�{2���̐����@�v12��
 */
static int GetMemberID(char *id)
{
	int retVal = FALSE;
	MEMBER *target;							/* �^�[�Q�b�g�m�[�h�p */
	char w[GETMEMBERID_STR_BUF_SIZE];		/* �����񑀍�p */
	char today[GETMEMBERID_DATE_BUF_SIZE];	/* �{���̓��t */
	int newID;								/* �V�KID�i����10���̐����j */
	int listID;								/* �����񃊃X�g����ID�i����10���̐����j */

	/* 12���̉��ID���쐬����iINT�^�ł�10���܂ł������Ȃ��̂Ő擪��'2'���폜����j */
	GetToday(0, 0, 0, today); 				/* �����̓��t���擾 */
	strncpy_s(w, GETMEMBERID_STR_BUF_SIZE, today + 1, 7);		/* 2012�N�̐擪��2���폜 */
	sprintf_s(w, GETMEMBERID_STR_BUF_SIZE, "%08s%02d", w, 1);	/* ���t+"01"��10�����쐬 */
	newID = atoi(w);
	/* �����񃊃X�g���������A�V����ID���擾���� */
	target = root;
	if (target != NULL) {
		/* ���X�g���I������܂ŌJ��Ԃ� */
		while (target->next != NULL) {
			target = target->next;

			/* ���X�g�̉��ID�̉���10�P�^���擾����iINT�^�ł�10���܂ŗL���j */
			strncpy_s(w, GETMEMBERID_STR_BUF_SIZE, target->id + 2, 10);
			listID = atoi(w);
			/* ID���r���� */
			if (newID == listID) {
				newID = listID + 1;
			}
			else if (newID > listID) {
				/* DO NOTHING */
			}
			else {
				break;
			}
		}


		/* ID�̍ő�l���`�F�b�N���� */
		if ((newID % 1000) == 0) {				/* 999�𒴂��� */
			retVal = FALSE;
		}
		else {
			sprintf_s(id, MEMBER_ID_SIZE + 1, "992%09d", newID);	/* ������ɕϊ� */
			retVal = TRUE;
		}
	}
	else {
		retVal = FALSE;
	}
	return retVal;
}


/*
 * �֐���			: void DisplayRegistMember(const MEMBER *m)
 * �@�\				: �yD-1123�z�o�^����������\������
 * ���̓p�����[�^	: const MEMBER *m	:������ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void DisplayRegistMember(const MEMBER *m)
{
	char date[DISPLAYREGISTMEMBER_BUF_SIZE];					/* ���t�t�H�[�}�b�g�p */

	printf("\n*****�V�K������m�F*****\n");
	printf("%-10s:%s\n", MEMBER_ID_NAME, m->id);
	printf("%-10s:%s\n", MEMBER_NAME_NAME, m->name);
	printf("%-10s:%s\n", MEMBER_ADDR_NAME, m->addr);
	ConvFormatDate(date, m->birth);
	printf("%-10s:%s\n", MEMBER_TEL_NAME, date);
}

/*
 * �֐���			: int RegistMember(MEMBER *m)
 * �@�\				: �yD-1123�z������������񃊃X�g�ɓo�^����
 * ���̓p�����[�^	: MEMBER *m	:������ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i����������X�g�ɓo�^�j���TRUE��Ԃ�
 * ���L����			: �Ȃ�
 */
int RegistMember(const MEMBER *m)
{
	int retVal = FALSE;
	MEMBER *newone;				/* ������̒ǉ��m�[�h�Q�Ɨp */
	MEMBER *target;				/* �^�[�Q�b�g�m�[�h�p */

	/* �V���ȃm�[�h��ǉ����f�[�^���i�[ */
	if ((newone = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {		/* �m�[�h���쐬 */
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}

	strncpy_s(newone->id, MEMBER_ID_SIZE + 1, m->id, _TRUNCATE);
	strncpy_s(newone->name, MEMBER_NAME_SIZE + 1, m->name, _TRUNCATE);
	strncpy_s(newone->addr, MEMBER_ADDR_SIZE + 1, m->addr, _TRUNCATE);
	strncpy_s(newone->tel, MEMBER_TEL_SIZE + 1, m->tel, _TRUNCATE);
	strncpy_s(newone->birth, MEMBER_BIRTH_SIZE + 1, m->birth, _TRUNCATE);

	/* ID�ŏ����ɂȂ�悤�Ƀm�[�h��ǉ����� */
	target = root;												/* �^�[�Q�b�g��擪�ɐݒ� */
	while (TRUE) {
		/* ���̃m�[�h������Ȃ�΁AID���`�F�b�N���� */
		if (target->next != NULL) {
			/* �ǉ��m�[�h��ID���������Ȃ�΁A�^�[�Q�b�g�̌��Ƀm�[�h��ǉ����ďI������ */
			if (strncmp(newone->id, target->next->id, MEMBER_ID_SIZE) < 0) {
				newone->next = target->next;
				target->next = newone;
				break;
			}
			else {
				target = target->next;							/* �^�[�Q�b�g���X�V���Ď��̃m�[�h�� */
			}
		}
		else {
			/* �V�����m�[�h�����X�g�̖����ɒǉ����ďI������ */
			newone->next = NULL;
			target->next = newone;
			break;
		}
	}
	return TRUE;
}

/*
 * �֐���			: void DisplayMember(const MEMBER *m)
 * �@�\				: �yD-1124�z�������\������
 * ���̓p�����[�^	: MUMBER *m	:������ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void DisplayMember(const MEMBER *m)
{
	char date[DISPLAYREGISTMEMBER_BUF_SIZE];					/* ���t�t�H�[�}�b�g�p */

	printf("\n*****������m�F*****\n");
	printf("%-10s:%s\n", MEMBER_ID_NAME, m->id);
	printf("%-10s:%s\n", MEMBER_NAME_NAME, m->name);
	printf("%-10s:%s\n", MEMBER_ADDR_NAME, m->addr);
	ConvFormatDate(date, m->birth);
	printf("%-10s:%s\n", MEMBER_TEL_NAME, date);
}

/*
 * �֐���			: int InputUpdateMember(MEMBER *m, MEMBER *mBuf)
 * �@�\				: �yD-1125�z������ύX���͉��
 * ���̓p�����[�^	: MEMBER *m	:�ύX���������m�[�h�ւ̃|�C���^
 * �o�̓p�����[�^	: MEMBER *mBuf	:�ύX����������m�[�h�ւ̃|�C���^
 * �߂�l			: int	:TRUE�i��������擾�j/FALSE�i�����񂪂Ȃ��j
 * ���L����			: �����̉�������Q�l�ɐV���ȉ��������͂���
 */
int InputUpdateMember(MEMBER *m, MEMBER *mBuf)
{
	int retVal = TRUE;
	char buf[MEMBER_NAME_SIZE + STRING_TERMINATOR_SIZE];	/* ������p�o�b�t�@ */


	if (m != NULL) {
		printf("�ύX���ڂ͓��͂��Ă��������B\n");
		printf("�����͍��ڂ͕ύX���܂���B\n");
		printf("%s:%s\n", MEMBER_ID_NAME, m->id);

		/* ���ID���R�s�[���� */
		strncpy_s(mBuf->id, MEMBER_ID_SIZE + 1, m->id, _TRUNCATE);

		/* ���O���X�V���� */
		printf("%s:%s�@���@", MEMBER_NAME_NAME, m->name);
		GetStr(buf, MEMBER_NAME_SIZE);
		if (strlen(buf) != 0) {
			strncpy_s(mBuf->name, MEMBER_NAME_SIZE + 1, buf, _TRUNCATE);
		}
		else {
			strncpy_s(mBuf->name, MEMBER_NAME_SIZE + 1, m->name, _TRUNCATE);
		}

		/* �Z�����X�V���� */
		printf("%s:%s�@���@", MEMBER_ADDR_NAME, m->addr);
		GetStr(buf, MEMBER_ADDR_SIZE);
		if (strlen(buf) != 0) {
			strncpy_s(mBuf->addr, MEMBER_ADDR_SIZE + 1, buf, _TRUNCATE);
		}
		else {
			strncpy_s(mBuf->addr, MEMBER_ADDR_SIZE + 1, m->addr, _TRUNCATE);
		}

		/* �d�b�ԍ����X�V���� */
		printf("%s:%s�@���@", MEMBER_TEL_NAME, m->tel);
		GetStr(buf, MEMBER_TEL_SIZE);
		if (strlen(buf) != 0) {
			strncpy_s(mBuf->tel, MEMBER_TEL_SIZE + 1, buf, _TRUNCATE);
		}
		else {
			strncpy_s(mBuf->tel, MEMBER_TEL_SIZE + 1, m->tel, _TRUNCATE);
		}


	}
	else {
		retVal = FALSE;
	}
	return retVal;
}

/*
 * �֐���			: int DeleteMember(const char *id)
 * �@�\				: �yD-1127�z������폜�m�F���
 * ���̓p�����[�^	: const char *id	:���ID
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:1�i�폜�j/EXIT_NUM�i�폜���Ȃ��j
 * ���L����			: �Ȃ�
 */
int DeleteMember(const char *id)
{
	int retVal = EXIT_NUM;
	MEMBER *target;					/* �^�[�Q�b�g�m�[�h�p */
	MEMBER *del;

	printf("\n*****������폜�m�F*****");
	if (GetYesNo("�폜���Ă���낵���ł���?") != FALSE) {
		/* ���X�g����^�[�Q�b�g�m�[�h���폜���� */
		target = root;
		while (target->next != NULL) {
			if (strncmp(target->next->id, id, MEMBER_ID_SIZE) == 0) {
				del = target->next;
				target->next = target->next->next;
				free(del);
				break;
			}
			target = target->next;
		}
		WriteMemberFile();						/* �����񃊃X�g�̃t�@�C�������� */
		printf("\n��������폜���܂����B\n");
		retVal = 1;
	}
	return retVal;
}
